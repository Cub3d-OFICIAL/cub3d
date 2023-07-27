/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dionisio <dionisio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:57:19 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/07/26 09:53:09 by dionisio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_array(char **str_array)
{
	int	i;

	if (!str_array)
		return ;
	i = 0;
	while (str_array[i])
		free(str_array[i++]);
	free(str_array);
}

int	rgb_color(int red, int green, int blue)
{
	return (red << 16 | green << 8 | blue);
}

void	clean_map(t_map_info *map_data)
{
	free(map_data->s_path);
	free(map_data->n_path);
	free(map_data->e_path);
	free(map_data->w_path);
	free_array(map_data->map);
}

void	play_music(void)
{
	static int	aux;

	if (1)
	{
		aux = system("killall xdg-open");
		aux = system("xdg-open ./sounds/backgroundSong.mp3 &");
		(void)aux;
	}
}
