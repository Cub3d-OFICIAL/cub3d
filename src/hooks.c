/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:51:07 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/05/27 18:08:40 by mpinna-l         ###   ########.fr       */
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
		info->map_data.player_posx += 1;
		info->flags.move_right = 1;
		ft_printf("Pressed\n");
	}
	if (keycode == L_KEY)
	{
		info->map_data.player_posx -= 1;
		info->flags.move_left = 1;
		ft_printf("Pressed\n");
	}
	if (keycode == U_KEY)
	{
		info->map_data.player_posx -= 1;
		info->flags.move_forward = 1;
		ft_printf("Pressed\n");
	}
	if (keycode == D_KEY)
	{
		info->map_data.player_posx += 1;
		info->flags.move_backward = 1;
		ft_printf("Pressed\n");
	}
	return (0);
}

int	key_event_release(int keycode, t_setup *info)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(info->mlx, info->mlx_win);
		exit(EXIT_FAILURE);
	}
	if (keycode == R_KEY)
	{
		info->flags.move_right = 0;
		ft_printf("Released\n");
	}
	if (keycode == L_KEY)
	{
		info->flags.move_left = 0;
		ft_printf("Released\n");
	}
	if (keycode == U_KEY)
	{
		info->flags.move_forward = 0;
		ft_printf("Released\n");
	}
	if (keycode == D_KEY)
	{
		info->flags.move_backward = 0;
		ft_printf("Released\n");
	}
	return (0);
}

int	close_win(t_setup *info)
{
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit(1);
}
