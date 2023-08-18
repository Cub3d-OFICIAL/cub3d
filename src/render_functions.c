/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:08:52 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/07/07 16:08:59 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	render_floor_celling(t_setup *set)
{
	int	x;
	int	y;

	set->frame.img = mlx_new_image(set->mlx,
			set->map_data.win_width, set->map_data.win_height);
	set->frame.addr = mlx_get_data_addr(set->frame.img, &set->frame.bpp,
			&set->frame.line_len, &set->frame.endian);
	x = -1;
	while (++x < set->map_data.win_width)
	{
		y = -1;
		while (++y < set->map_data.win_height / 2)
		{
			my_mlx_pixel_put(&set->frame, x, y, set->map_data.c_color);
			my_mlx_pixel_put(&set->frame, x,
				y + (set->map_data.win_height / 2), set->map_data.f_color);
		}
	}
}

void	render_player(t_setup *set)
{
	int	x;
	int	y;
	int	player_x;
	int	player_y;

	player_x = set->player.posx * TILE_SIZE * MINIMAP_SCALE;
	player_y = set->player.posy * TILE_SIZE * MINIMAP_SCALE;
	x = -1;
	while (++x < set->player.width)
	{
		y = -1;
		while (++y < set->player.height)
			my_mlx_pixel_put(&set->frame, x + player_x
				- (set->player.width / 2), y + player_y
				- (set->player.height / 2), rgb_color(255, 0, 0));
	}
}

void	set_color(int *color, int i, int j, t_setup *set)
{
	if (set->map_data.map[i][j] == '1' || set->map_data.map[i][j] == ' ')
		*color = 0;
	else if (set->map_data.player_posy == j && set->map_data.player_posx == i)
		*color = rgb_color(255, 255, 0);
	else
		*color = rgb_color(255, 255, 255);
}

void	render_minimap(t_setup *set)
{
	int		i;
	int		j;
	int		x;
	int		y;
	int		color;

	i = -1;
	while (++i < set->map_data.row_nbr)
	{
		j = -1;
		while (++j < set->map_data.col_nbr)
		{
			set_color(&color, i, j, set);
			x = -1;
			while (++x < TILE_SIZE * MINIMAP_SCALE)
			{
				y = -1;
				while (++y < TILE_SIZE * MINIMAP_SCALE)
					my_mlx_pixel_put(&set->frame,
						x + (j * TILE_SIZE * MINIMAP_SCALE),
						y + (i * TILE_SIZE * MINIMAP_SCALE), color);
			}
		}
	}
	render_player(set);
}

void	render_strip(int x, int draw_start, int draw_end, t_setup *set, int *tex)
{	
	int		line_height;
	float	rate;
	int		i;
	int		j;

	line_height = draw_end - draw_start;
	rate = line_height / (float) 64; //3,125
	// float tex_pos = (draw_start - set->map_data.win_height /2 + line_height / 2) * rate;
	i = 0;
	j = 0;
	while (draw_start <= draw_end)
	{
		j++;
		my_mlx_pixel_put(&set->frame, x, draw_start++, tex[i]);
		if (j >= rate)
		{
			j = 0;
			i += 1;
		}
		if (i >= 64)
			i = 63;
	}
	printf("%i\n", i);
}
