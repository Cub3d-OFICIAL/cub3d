/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:44:43 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/19 17:12:45 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_celling(t_setup *set)
{
	t_data	f_img;
	t_data	c_img;

	f_img = square_img(WIDTH, HEIGHT / 2, set->map_data.f_color, set->mlx);
	c_img = square_img(WIDTH, HEIGHT / 2, set->map_data.c_color, set->mlx);
	mlx_put_image_to_window(set->mlx, set->mlx_win, f_img.img, 0, 0);
	mlx_put_image_to_window(set->mlx, set->mlx_win, c_img.img, 0, HEIGHT / 2);
	mlx_destroy_image(set->mlx, f_img.img);
	mlx_destroy_image(set->mlx, c_img.img);
}

void	render_minimap(t_setup *set)
{
	t_data	minimap;
	int		i;
	int		j;
	int		x;
	int		y;

	minimap.img = mlx_new_image(set->mlx, set->map_data.col_nbr * 17, set->map_data.row_nbr * 17);
	minimap.addr = mlx_get_data_addr(minimap.img, &minimap.bpp, &minimap.line_len, &minimap.endian);
	i = -1;
	while (++i < set->map_data.row_nbr)
	{
		j = -1;
		while (++j < set->map_data.col_nbr)
		{
			y = -1;
		   	while (++y < 16)
			{
				x = -1;
				while(++x < 16)
				{
					if (set->map_data.map[i][j] == '1' || set->map_data.map[i][j] == ' ')
						my_mlx_pixel_put(&minimap, x + (j * 17), y + (i * 17), 0);
					else
						my_mlx_pixel_put(&minimap, x + (j * 17), y + (i * 17), 16777215);
				}
			}
		}
	}
	mlx_put_image_to_window(set->mlx, set->mlx_win, minimap.img, 0, 0);
	mlx_destroy_image(set->mlx, minimap.img);
}

void	start_game(t_setup *game_setup)
{
	game_setup->mlx = mlx_init();
	game_setup->mlx_win = mlx_new_window(game_setup->mlx, WIDTH, HEIGHT, CUB);
	draw_floor_celling(game_setup);
	render_minimap(game_setup);
	
	// Printing Map info
	printf("|- GAME INFO -|\n\n");
	print_str_array(game_setup->map_data.map);
	printf("Fields Filled %i\n", game_setup->map_data.fields_filled);
	printf("Celling Color %i\n", game_setup->map_data.c_color);
	printf("Floor Color %i\n", game_setup->map_data.f_color);
	printf("rows %i\n", game_setup->map_data.row_nbr);
	printf("cols %i\n", game_setup->map_data.col_nbr);
	printf("Orientation %c\n", game_setup->map_data.orientation);
	printf("Player posx %i\n", game_setup->map_data.player_posx);
	printf("Player posy %i\n", game_setup->map_data.player_posy);
	
	mlx_key_hook(game_setup->mlx_win, key_event, game_setup);
	mlx_hook(game_setup->mlx_win, 17, 0, close_win, game_setup);
	mlx_loop(game_setup->mlx);
}

int	main(int argc, char **argv)
{
	t_setup	game_setup;

	if (check_argc(argc))
		return (print_error(ARG_ERROR, 1));
	if (check_map(argv[1], EXT, &game_setup.map_data))
		return (print_error(EXT_ERROR, 1));
	start_game(&game_setup);
	clean_map(&game_setup.map_data);
	return (0);
}

t_data	square_img(int width, int height, int color, void *mlx)
{
	t_data	sqr;
	int		x;
	int		y;

	x = -1;
	sqr.img = mlx_new_image(mlx, width, height);
	sqr.addr = mlx_get_data_addr(sqr.img, &sqr.bpp, &sqr.line_len, &sqr.endian);
	while (++x < width)
	{
		y = -1;
		while (++y < height)
			my_mlx_pixel_put(&sqr, x, y, color);
	}	
	return (sqr);
}
