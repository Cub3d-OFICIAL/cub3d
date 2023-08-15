/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/12 18:17:21 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/08/12 18:17:23 by mpinna-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3

// int get_pixel_color(t_texture texture, int x, int y)
// {
// 	int		color;
// 	char	*pixel_addr = texture.texture_img.addr +
// 		(y * texture.texture_img.line_len + x * (texture.texture_img.bpp / 8));

// 	if (texture.texture_img.endian == 1)
// 		color = (pixel_addr[0] << 16) | (pixel_addr[1] << 8) | pixel_addr[2];
// 	else
// 		color = pixel_addr[0] | (pixel_addr[1] << 8) | (pixel_addr[2] << 16);
// 	return color;
// }

int get_pixel_color(t_texture texture, int x, int y)
{
    int bpp = texture.texture_img.bpp / 8;
    int pixel_index = (y * texture.width + x) * bpp;

    unsigned char r = ((unsigned char *)texture.texture_img.addr)[pixel_index];
    unsigned char g = ((unsigned char *)texture.texture_img.addr)[pixel_index + 1];
    unsigned char b = ((unsigned char *)texture.texture_img.addr)[pixel_index + 2];

    return (r << 16) | (g << 8) | b;
}

void	texture_images(t_setup *set, t_texture *texture, char *path)
{
	texture->height = 0;
	texture->width = 0;
	texture->texture_img.img = mlx_xpm_file_to_image(set->mlx, path,
			&texture->width, &texture->height);
	texture->texture_img.addr = mlx_get_data_addr(texture->texture_img.img,
			&texture->texture_img.bpp, &texture->texture_img.line_len,
			&texture->texture_img.endian);
}

void	init_texture(t_setup *set)
{
	texture_images(set, &set->texture[NORTH], set->map_data.n_path);
	texture_images(set, &set->texture[SOUTH], set->map_data.s_path);
	texture_images(set, &set->texture[EAST], set->map_data.e_path);
	texture_images(set, &set->texture[WEST], set->map_data.w_path);
	set->map_data.color_picker = get_pixel_color(set->texture[NORTH], 40, 40);
}

void	clean_textures(t_setup *set)
{
	mlx_destroy_image(set->mlx, set->texture[NORTH].texture_img.img);
	mlx_destroy_image(set->mlx, set->texture[SOUTH].texture_img.img);
	mlx_destroy_image(set->mlx, set->texture[EAST].texture_img.img);
	mlx_destroy_image(set->mlx, set->texture[WEST].texture_img.img);
}
