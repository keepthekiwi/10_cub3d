/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:33:39 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:34:37 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_block_for_wall_two(t_data *data, int x, int y)
{
	if (data->map->map_content[x][y + 1] == '\0'
		|| (y != data->map->map_height
		&& data->map->map_content[x][y + 1] == ' '))
		return (EXIT_FAILURE);
	if (data->map->map_content[x][y - 1] == '\0'
		|| (y != 0 && data->map->map_content[x][y - 1] == ' '))
		return (EXIT_FAILURE);
	if (data->map->map_content[x + 1][y + 1] == '\0'
		|| (y != 0 && data->map->map_content[x + 1][y + 1] == ' '))
		return (EXIT_FAILURE);
	if (data->map->map_content[x - 1][y + 1] == '\0'
		|| (y != 0 && data->map->map_content[x - 1][y + 1] == ' '))
		return (EXIT_FAILURE);
	if (data->map->map_content[x + 1][y - 1] == '\0'
		|| (y != 0 && data->map->map_content[x + 1][y - 1] == ' '))
		return (EXIT_FAILURE);
	if (data->map->map_content[x - 1][y - 1] == '\0'
		|| (y != 0 && data->map->map_content[x - 1][y - 1] == ' '))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_block_for_wall(t_data *data, int x, int y)
{
	if (data->map->map_content[x][y] == '1'
		|| data->map->map_content[x][y] == ' ')
		return (EXIT_SUCCESS);
	if ((y == 0 || y == data->map->map_height + 1)
		&& data->map->map_content[x][y] != ' '
		&& data->map->map_content[x][y] != '\0'
		&& data->map->map_content[x][y] != '1')
		return (EXIT_FAILURE);
	else if (y == 0 || y == data->map->map_height + 1)
		return (EXIT_FAILURE);
	if ((x == 0 || x == data->map->map_width)
		&& data->map->map_content[x][y] != ' '
		&& data->map->map_content[x][y] != '\0'
		&& data->map->map_content[x][y] != '1')
		return (EXIT_FAILURE);
	else if (x == 0 || x == data->map->map_width)
		return (EXIT_SUCCESS);
	if (data->map->map_content[x + 1][y] == '\0'
		|| (x != data->map->map_width
		&& data->map->map_content[x + 1][y] == ' '))
		return (EXIT_FAILURE);
	if (data->map->map_content[x - 1][y] == '\0'
		|| (x != 0 && data->map->map_content[x - 1][y] == ' '))
		return (EXIT_FAILURE);
	return (check_block_for_wall_two(data, x, y));
}

int	check_walls(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y <= data->map->map_height)
	{
		x = 0;
		while (x < data->map->map_width && data->map->map_content[x][y] != '\0')
		{
			if (check_block_for_wall(data, x, y) != EXIT_SUCCESS)
				return (1);
			x++;
		}
		y++;
	}
	return (0);
}

int	check_map_content(t_data *data)
{
	int	i;

	i = 0;
	while (data->map->map_str[i] != '\0')
	{
		if (data->map->map_str[i] != 'N' && data->map->map_str[i] != 'S'
			&& data->map->map_str[i] != 'E' && data->map->map_str[i] != 'W'
			&& data->map->map_str[i] != '0' && data->map->map_str[i] != '1'
			&& data->map->map_str[i] != ' ' && data->map->map_str[i] != '\0'
			&& data->map->map_str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}

int	check_map(t_data *data)
{
	if (check_map_content(data) != 0)
		return (set_error(data, INVALID_ORDER));
	if (check_walls(data) != 0)
		return (set_error(data, INVALID_MAP_WALLS));
	if (check_charakter_quantity(data) != 0)
		return (set_error(data, INVALID_MAP_CHARACTERS));
	return (0);
}
