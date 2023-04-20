/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:51:07 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/13 19:04:40 by mpinna-l         ###   ########.fr       */
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
		ft_printf("Rigth key\n");
	if (keycode == L_KEY)
		ft_printf("Left key\n");
	if (keycode == U_KEY)
		ft_printf("Up key\n");
	if (keycode == D_KEY)
		ft_printf("Down key\n");
	return (0);
}

int	close_win(t_setup *info)
{
	mlx_destroy_window(info->mlx, info->mlx_win);
	exit(1);
}
