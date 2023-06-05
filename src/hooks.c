/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:51:07 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/05/21 15:54:50 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_event(int keycode, t_setup *info)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		exit(EXIT_FAILURE);
	}
	if (keycode == R_KEY)
	{
		info->map_data.player_posy += 1;
		info->has_changes = 1;
	}
	if (keycode == L_KEY)
	{
		info->map_data.player_posy -= 1;
		info->has_changes = 1;
	}
	if (keycode == U_KEY)
	{
		info->map_data.player_posx -= 1;
		info->has_changes = 1;
	}
	if (keycode == D_KEY)
	{
		info->map_data.player_posx += 1;
		info->has_changes = 1;
	}
	return (0);
}

int	close_win(t_setup *info)
{
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit(1);
}
