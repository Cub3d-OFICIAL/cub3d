/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:17:20 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/07/07 16:17:22 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_wall(int x, int y, t_setup *set)
{
	int		coordinate_y;
	char	**map;

	map = set->map_data.map;
	coordinate_y = floor(set->player.posy / TILE_SIZE);
	if (map[coordinate_y][x] == '1' || map[coordinate_y][x] == ' ')
		return (1);
	if (map[y][x] == '1' || map[y][x] == ' ')
		return (1);
	return (0);
}

void	check_states(t_setup *set)
{
	set->player.turn_direction = 0;
	if (set->states[0] || set->states[1])
	{
		if (set->states[0] && !set->states[1])
		{
			set->player.turn_direction = 1;
			set->player.rot_speed *= 1;
		}
		else if (!set->states[0] && set->states[1])
		{
			set->player.turn_direction = -1;
			set->player.rot_speed *= -1;
		}
	}
	set->player.walk_direction = 0;
	if (set->states[2] || set->states[3])
	{
		if (set->states[2] && !set->states[3])
		{
			set->player.walk_direction = 1;
			set->player.mov_speed *= 1;
		}
		else if (!set->states[2] && set->states[3])
		{
			set->player.walk_direction = -1;
			set->player.mov_speed *= -1;
		}
	}
}

void	move_player(t_setup *set)
{
	float	move_step;
	float	new_posx;
	float	new_posy;
	int		posx_on_map;
	int		posy_on_map;
	
	check_states(set);
	double oldDirX = set->player.dir_x;
	set->player.dir_x = set->player.dir_x* cos(set->player.rot_speed) - set->player.dir_y * sin(set->player.rot_speed);
	set->player.dir_y = oldDirX * sin(set->player.rot_speed) + set->player.dir_y * cos(set->player.rot_speed);
	double oldPlaneX = set->player.plane_x;
	set->player.plane_x = set->player.plane_x * cos(set->player.rot_speed) - set->player.plane_y * sin(set->player.rot_speed);
	set->player.plane_y = oldPlaneX * sin(set->player.rot_speed) + set->player.plane_y * cos(set->player.rot_speed);

	if(set->map_data.map[(int)(set->player.plane_x + set->player.dir_x * set->player.mov_speed)][(int)set->player.plane_y] == '1')
		set->player.plane_x += set->player.dir_x * set->player.mov_speed;
	if(set->map_data.map[(int)set->player.plane_x][(int)(set->player.plane_y + set->player.dir_y  * set->player.mov_speed)] == '1')
		set->player.plane_y += set->player.dir_y * set->player.mov_speed;
	move_step = set->player.walk_direction * set->player.move_speed;
	set->player.rotation_angle += set->player.turn_direction
		* set->player.rotation_speed;
	new_posx = set->player.posx + (cos(set->player.rotation_angle) * move_step);
	new_posy = set->player.posy + (sin(set->player.rotation_angle) * move_step);
	posx_on_map = floor(new_posx / TILE_SIZE);
	posy_on_map = floor(new_posy / TILE_SIZE);
	if (!is_wall(posx_on_map, posy_on_map, set))
	{
		set->player.posx = new_posx;
		set->player.posy = new_posy;
	}
}
