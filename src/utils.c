/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:30:56 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/12 16:39:59 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	init_cub3d(t_data *data, int argc, char *argv[])
{
	data->argc = argc;
	data->argv = argv;
	data->error = 0;
	data->map->map_width = 0;
	data->map->map_height = 0;
	data->map->map_path = NULL;
	data->map->map_str = NULL;
	data->map->map_content = NULL;
	data->map->north_path = NULL;
	data->map->south_path = NULL;
	data->map->east_path = NULL;
	data->map->west_path = NULL;
	return (0);
}

int	check_charakter_quantity(t_data *data)
{
	int	x;
	int	y;
	int	count;

	x = 0;
	count = 0;
	while (x < data->map->map_width)
	{
		y = 0;
		while (y < data->map->map_height)
		{
			if (data->map->map_content[x][y] == 'N'
				|| data->map->map_content[x][y] == 'S'
				|| data->map->map_content[x][y] == 'E'
				|| data->map->map_content[x][y] == 'W')
				count++;
			y++;
		}
		x++;
	}
	if (count != 1)
		return (1);
	return (0);
}
