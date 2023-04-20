/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpinna-l <mpinna-l@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 15:57:19 by mpinna-l          #+#    #+#             */
/*   Updated: 2023/03/10 16:59:09 by mpinna-l         ###   ########.fr       */
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

void	clean_map(t_map_info *map_data)
{
	free(map_data->s_path);
	free(map_data->n_path);
	free(map_data->e_path);
	free(map_data->w_path);
	free_array(map_data->map);
}
