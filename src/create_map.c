/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:27:20 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:27:29 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	is_line_map_start(t_data *data, int i)
{
	int		j;
	bool	flag;

	j = i;
	while (data->file_content[j] != '\n' && data->file_content[j] != '\0')
	{
		if (data->file_content[j] == '1')
			flag = true;
		if (data->file_content[j] != ' ' && data->file_content[j] != '1')
			return (false);
		j++;
	}
	if (flag == false)
		return (false);
	return (true);
}

int	calculate_map_start(t_data *data)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 5;
	while (data->file_content[i] != '\0')
	{
		if (data->file_content[i] == '\n' && data->file_content[i + 1] != '\n')
		{
			i++;
			if (is_line_map_start(data, i) == true)
			{
				data->map_start_in_file = i;
				return (i);
			}
		}
		i++;
	}
	return (i);
}

int	set_map_dimensions(t_data *data)
{
	int	i;
	int	dimensions[2];

	dimensions[0] = 0;
	dimensions[1] = 0;
	i = calculate_map_start(data);
	while (is_map_char(data, i) == true)
	{
		if (data->file_content[i] == '\n')
		{
			if (dimensions[0] > data->map->map_width)
				data->map->map_width = dimensions[0];
			data->map->map_height++;
			dimensions[0] = 0;
			dimensions[1]++;
		}
		dimensions[0]++;
		i++;
	}
	if (dimensions[0] > data->map->map_width)
		data->map->map_width = dimensions[0];
	data->map->map_height = dimensions[1];
	if (data->map->map_height < 3 || data->map->map_width < 3)
		return (1);
	return (EXIT_SUCCESS);
}

int	create_empty_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	data->map->map_content = (char **)ft_calloc
		(data->map->map_width + 1, sizeof(char *));
	while (i < data->map->map_width + 1)
	{
		data->map->map_content[i] = (char *)ft_calloc
			(data->map->map_height + 1, sizeof(char));
		j = 0;
		while (j <= data->map->map_height + 2)
		{
			data->map->map_content[i][j] = '\0';
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	set_map_content(t_data *data)
{
	int	i;
	int	x;
	int	y;

	y = 0;
	i = 0;
	while (y <= data->map->map_height)
	{
		x = 0;
		while (x < data->map->map_width)
		{
			data->map->map_content[x][y] = data->map->map_str[i];
				i++;
			if (data->map->map_str[i - 1] == '\n')
				break ;
			x++;
		}
		data->map->map_content[x][y] = '\0';
		y++;
	}
	data->map->map_content[0][y] = '\0';
	return (EXIT_SUCCESS);
}
