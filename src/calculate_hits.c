/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_hits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 18:44:30 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/07/29 18:44:34 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_horizontal_hits(float *intercept, float *step, int id, t_setup *set)
{
	float	next_toach[2];
	int		x_to_check;
	int		y_to_check;

	next_toach[0] = intercept[0];
	next_toach[1] = intercept[1];
	while (next_toach[0] >= 0 && next_toach[0] <= set->map_data.win_width
		&& next_toach[1] >= 0 && next_toach[1] <= set->map_data.win_height)
	{
		x_to_check = (int)floor(next_toach[0] / TILE_SIZE);
		y_to_check = (int)floor(next_toach[1] / TILE_SIZE);
		if (set->rays[id].isRayFacingUp && y_to_check )
			y_to_check -= 1;
		if (x_to_check < set->map_data.col_nbr &&  y_to_check < set->map_data.row_nbr && set->map_data.map[y_to_check][x_to_check] == '1')
		{
			set->rays[id].wallHitX[0] = next_toach[0];
			set->rays[id].wallHitY[0] = next_toach[1];
			break ;
		}
		else
		{
			next_toach[0] += step[0];
			next_toach[1] += step[1];
		}
	}
}

void	horizontal_hit(float rayAngle, int id, t_setup *set)
{
	float	intercept[2];
	float	step[2];
	float	tg;

	tg = tan(rayAngle);
	intercept[1] = floor(set->player.posy / TILE_SIZE) * TILE_SIZE;
	if (set->rays[id].isRayFacingDown)
		intercept[1] += TILE_SIZE;
	intercept[0] = set->player.posx + (intercept[1] - set->player.posy) / tg;
	step[1] = TILE_SIZE;
	if (set->rays[id].isRayFacingUp)
		step[1] *= -1;
	step[0] = TILE_SIZE / tg;
	if (set->rays[id].isRayFacingLeft && step[0] > 0)
		step[0] *= -1;
	if (set->rays[id].isRayFacingRight && step[0] < 0)
		step[0] *= -1;
	set_horizontal_hits(intercept, step, id, set);
}

void	set_vertical_hits(float *intercept, float *step, int id, t_setup *set)
{
	float	next_toach[2];
	int		x_to_check;
	int		y_to_check;

	next_toach[0] = intercept[0];
	next_toach[1] = intercept[1];
	while (next_toach[0] >= 0 && next_toach[0] < set->map_data.win_width
		&& next_toach[1] >= 0 && next_toach[1] < set->map_data.win_height)
	{
		x_to_check = (int)floor(next_toach[0] / TILE_SIZE);
		y_to_check = (int)floor(next_toach[1] / TILE_SIZE);
		if (set->rays[id].isRayFacingLeft && x_to_check)
			x_to_check -= 1;
		if (x_to_check < set->map_data.col_nbr &&  y_to_check < set->map_data.row_nbr && set->map_data.map[y_to_check][x_to_check] == '1')
		{
			set->rays[id].wallHitX[1] = next_toach[0];
			set->rays[id].wallHitY[1] = next_toach[1];
			break ;
		}
		else
		{
			next_toach[0] += step[0];
			next_toach[1] += step[1];
		}
	}
}

void	vertical_hit(float rayAngle, int id, t_setup *set)
{
	float	intercept[2];
	float	step[2];
	float	tg;

	tg = tan(rayAngle);
	intercept[0] = floor(set->player.posx / TILE_SIZE) * TILE_SIZE;
	if (set->rays[id].isRayFacingRight)
		intercept[0] += TILE_SIZE;
	intercept[1] = set->player.posy + (intercept[0] - set->player.posx) * tg;
	step[0] = TILE_SIZE;
	if (set->rays[id].isRayFacingLeft)
		step[0] *= -1;
	step[1] = TILE_SIZE * tg;
	if (set->rays[id].isRayFacingUp && step[1] > 0)
		step[1] *= -1;
	if (set->rays[id].isRayFacingDown && step[1] < 0)
		step[1] *= -1;
	set_vertical_hits(intercept, step, id, set);
}
