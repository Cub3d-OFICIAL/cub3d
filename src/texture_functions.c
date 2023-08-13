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

void	init_texture(t_setup *set)
{
	int	i;

	i = -1;
	set->texture.buffer = malloc(set->map_data.win_height * sizeof(int *));
	while (i++ < set->map_data.win_height)
		set->texture.buffer[i] = malloc(set->map_data.win_width * sizeof(int));
	i = -1;
	set->texture.textures = malloc(4 * sizeof(int *));
	while (i++ < 4)
		set->texture.textures[i] = malloc(T_HEIGHT * T_WIDTH * sizeof(int));
}

void	clean_textures(t_setup *set)
{
	int	i;

	i = -1;
	while (i++ < set->map_data.win_height)
		free(set->texture.buffer[i]);
	free(set->texture.buffer);
	i = -1;
	while (i++ < 4)
		free(set->texture.textures[i]);
	free(set->texture.textures);
}
