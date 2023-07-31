/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 16:43:15 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/07/15 19:17:59 by mpinna-l         ###   ########.fr       */
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

void	cast_all_rays(t_setup *set)
{
	float	fov;
	float	ray_angle;
	int		strip_id;
	int		ray_number;

	ray_number = set->map_data.win_width;
	fov = 30 * PI / 180;
	ray_angle = set->player.rotation_angle - (fov / 2);
	set->rays = malloc(sizeof(t_rays) * ray_number);
	ray_angle = normalize_angle(ray_angle);
	strip_id = -1;
	while (++strip_id < ray_number)
	{
		cast_ray(ray_angle, strip_id, set);
		ray_angle += fov / ray_number;
		ray_angle = normalize_angle(ray_angle);
	}
	render_walls(set);
	free(set->rays);
	set->rays = NULL;
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
