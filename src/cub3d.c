/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 13:44:43 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/05/27 16:35:35 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_celling(t_setup *set)
{
	t_data	f_img;
	t_data	c_img;

	f_img = square_img(set->map_data.win_width, set->map_data.win_height / 2, set->map_data.f_color, set->mlx);
	c_img = square_img(set->map_data.win_width, set->map_data.win_height / 2, set->map_data.c_color, set->mlx);
	mlx_put_image_to_window(set->mlx, set->mlx_win, f_img.img, 0, 0);
	mlx_put_image_to_window(set->mlx, set->mlx_win, c_img.img, 0, set->map_data.win_height / 2);
	mlx_destroy_image(set->mlx, f_img.img);
	mlx_destroy_image(set->mlx, c_img.img);
}
void draw_line(t_data* data, int x0, int y0, int x1, int y1);

void	render_player(t_setup *set) {
	t_data	player;
	int 	player_x;
	int		player_y;

	player_x = set->player.posx * MINIMAP_SCALE;
	player_y = set->player.posy * MINIMAP_SCALE;
	
	player = square_img(set->player.height * MINIMAP_SCALE, set->player.width * MINIMAP_SCALE, rgb_color(255, 0, 0), set->mlx);
	mlx_put_image_to_window(set->mlx, set->mlx_win, player.img, player_y, player_x);  
	mlx_destroy_image(set->mlx, player.img);
}

void	render_minimap(t_setup *set)
{
	t_data	tile_img;
	int		i;
	int		j;
	int		tile_x;
	int		tile_y;

	i = -1;
	while (++i < set->map_data.row_nbr)
	{
		j = -1;
		while (++j < set->map_data.col_nbr)
		{
			tile_x = j * TILE_SIZE;
			tile_y = i * TILE_SIZE;
			if (set->map_data.map[i][j] == '1' || set->map_data.map[i][j] == ' ')
				tile_img = square_img(TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, 0, set->mlx);
			else if (set->map_data.player_posy == j && set->map_data.player_posx == i)
				tile_img = square_img(TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, rgb_color(255, 255, 0), set->mlx);
			else
				tile_img = square_img(TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, rgb_color(255, 255, 255), set->mlx);
			mlx_put_image_to_window(set->mlx, set->mlx_win, tile_img.img, tile_x * MINIMAP_SCALE, tile_y * MINIMAP_SCALE);
			mlx_destroy_image(set->mlx, tile_img.img);
		}
	}
}

void move_player(t_setup *game_setup)
{
	float	move_step;
	float	newplayerX;
	float	newplayerY;

	move_step = game_setup->player.walk_direction * game_setup->player.move_speed;
	game_setup->player.rotation_angle += game_setup->player.turn_direction * game_setup->player.rotation_speed;

	newplayerX = game_setup->player.posx + (cos(game_setup->player.rotation_angle) * move_step);
	newplayerY = game_setup->player.posy + (sin(game_setup->player.rotation_angle) * move_step);

	game_setup->player.posx = newplayerX;
	game_setup->player.posy = newplayerY;

	printf("%f %f\n", newplayerX, newplayerY);
}

int render_next_frame(t_setup *game_setup)
{
	move_player(game_setup);
	render_minimap(game_setup);
	render_player(game_setup);

	return (0);
}

void	start_game(t_setup *game_setup)
{
	game_setup->mlx = mlx_init();
	game_setup->mlx_win = mlx_new_window(game_setup->mlx, game_setup->map_data.win_width, game_setup->map_data.win_height, CUB);
	game_setup->has_changes = 1;
	draw_floor_celling(game_setup);
	
	mlx_hook(game_setup->mlx_win, 2, 1L<<0, key_event, game_setup);
	mlx_hook(game_setup->mlx_win, 3, 2L<<0, key_event_release, game_setup);
	mlx_hook(game_setup->mlx_win, 17, 0, close_win, game_setup);
	mlx_loop_hook(game_setup->mlx, render_next_frame, game_setup);	
	
	mlx_loop(game_setup->mlx);
}

void	init_setup(t_setup *game_setup)
{
	game_setup->map_data.win_height = game_setup->map_data.row_nbr * TILE_SIZE;
	game_setup->map_data.win_width = game_setup->map_data.col_nbr * TILE_SIZE;
	game_setup->player.posx = (game_setup->map_data.player_posx * TILE_SIZE) + (TILE_SIZE/2);
	game_setup->player.posy = (game_setup->map_data.player_posy * TILE_SIZE) + (TILE_SIZE/2);
	game_setup->player.height = 10;
	game_setup->player.width = 10;
	game_setup->player.turn_direction = 0;
	game_setup->player.walk_direction = 0;
	game_setup->player.rotation_angle =  PI / 2;
	game_setup->player.move_speed = 100;
	game_setup->player.rotation_speed = 45 * (PI / 180);
}

int	main(int argc, char **argv)
{
	t_setup	game_setup;

	if (check_argc(argc))
		return (print_error(ARG_ERROR, 1));
	if (check_map(argv[1], EXT, &game_setup.map_data))
		return (print_error(EXT_ERROR, 1));
	init_setup(&game_setup);
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



	/* Printing Map info
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
	*/
