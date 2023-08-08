/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dionisio <dionisio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:43:15 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/08/08 15:27:03 by dionisio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

float	hypotenuse(float x1, float y1, float x2, float y2)
{
	float	dx;
	float	dy;

	dx = x2 - x1;
	dy = y2 - y1;
	return (sqrt(dx * dx + dy * dy));
}

void	cast_ray(float rayAngle, int id, t_setup *set)
{
	float	horizontal_dist;
	float	vertical_dist;

	set->rays[id].isRayFacingDown = (rayAngle > 0
			&& rayAngle <= PI);
	set->rays[id].isRayFacingRight = (rayAngle < 0.5 * PI
			|| rayAngle >= 1.5 * PI);
	set->rays[id].isRayFacingUp = !set->rays[id].isRayFacingDown;
	set->rays[id].isRayFacingLeft = !set->rays[id].isRayFacingRight;
	horizontal_hit(rayAngle, id, set);
	vertical_hit(rayAngle, id, set);
	horizontal_dist = hypotenuse(set->player.posx, set->player.posy,
			set->rays[id].wallHitX[0], set->rays[id].wallHitY[0]);
	vertical_dist = hypotenuse(set->player.posx, set->player.posy,
			set->rays[id].wallHitX[1], set->rays[id].wallHitY[1]);
	set->rays[id].distance = vertical_dist;
	if (horizontal_dist < vertical_dist)
		set->rays[id].distance = horizontal_dist;
	dda_points(set, set->rays[id].distance, rayAngle);
}

void	strip(int x, int drawStart, int drawEnd, int color, t_setup *set)
{	
	while (drawStart <= drawEnd)
	{
		my_mlx_pixel_put(&set->frame, x, drawStart, color); 
		drawStart++;
	}
}

void	cast_all_rays(t_setup *set)
{
	int		x;
	float	width;
	float	cameraX;
	float	rayDirX;
	float 	rayDirY;

	width = set->map_data.win_width;
	x = -1;
	while (++x < set->map_data.win_width)
	{
		cameraX = 2 * x / width - 1;
		rayDirX = set->player.dir_x + set->player.plane_x * cameraX;
		rayDirY = set->player.dir_y + set->player.plane_y * cameraX;

		int mapX = set->player.posx;
		int mapY = set->player.posy;

      //length of ray from current position to next x or y-side
      float sideDistX;
      float sideDistY;

       //length of ray from one x or y-side to next x or y-side
    	float deltaDistX;
		if (rayDirX == 0)
			deltaDistX = 1e30;
		else
			deltaDistX = fabs(1 / rayDirX);
		float deltaDistY;
		if (rayDirY == 0)
			deltaDistY = 1e30;
		else
			deltaDistY = fabs(1 / rayDirY);

      float perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

	  if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (set->player.posx - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - set->player.posx) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (set->player.posy - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - set->player.posy) * deltaDistY;
	}
	 //perform DDA
	while (hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (sideDistX < sideDistY)
		{
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		}
		else
		{
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		//Check if ray has hit a wall
		if (set->map_data.map[mapY][mapX] > 0)
			hit = 1;
	}
	 //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)	
	if(side == 0)
		perpWallDist = (sideDistX - deltaDistX);
	else
		perpWallDist = (sideDistY - deltaDistY);

	
	//Calculate height of line to draw on screen
      int lineHeight = (int)(set->map_data.win_height / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + set->map_data.win_height / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + set->map_data.win_height / 2;
		if(drawEnd >= set->map_data.win_height)
			drawEnd = set->map_data.win_height - 1;

		 //choose wall color
      int color = WHITE;
      //give x and y sides different brightness
      if (side == 1) 
		color = color / 2;

      //draw the pixels of the stripe as a vertical line
      strip(x, drawStart, drawEnd, color, set);
		printf("%f\n", perpWallDist );
    
	}

}

void	dda_points(t_setup *set, float distance, float rayAngle)
{
	int		deltas[2];
	int		steps;
	int		i;
	float	x;
	float	y;

	x = set->player.posx;
	y = set->player.posy;
	deltas[0] = (x - (x + cos(rayAngle) * distance)) * -1;
	deltas[1] = (y - (y + sin(rayAngle) * distance)) * -1;
	if (abs(deltas[0]) > abs(deltas[1]))
		steps = abs(deltas[0]);
	else
		steps = abs(deltas[1]);
	i = -1;
	while (++i <= steps)
	{
		my_mlx_pixel_put(&set->frame, x * MINIMAP_SCALE,
			y * MINIMAP_SCALE, RED);
		x += deltas[0] / (float)steps;
		y += deltas[1] / (float)steps;
	}
}
