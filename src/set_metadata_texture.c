/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_metadata_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:11:04 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:11:20 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	set_individual_texture(t_data *data, t_var cardinal_point, int i)
{
	i += 2;
	while (data->file_content[i] == ' ')
		i++;
	if (cardinal_point == SOUTH)
		data->map->south_path = ft_strchrdup(&data->file_content[i], '\n');
	else if (cardinal_point == NORTH)
		data->map->north_path = ft_strchrdup(&data->file_content[i], '\n');
	else if (cardinal_point == WEST)
		data->map->west_path = ft_strchrdup(&data->file_content[i], '\n');
	else if (cardinal_point == EAST)
		data->map->east_path = ft_strchrdup(&data->file_content[i], '\n');
	return (EXIT_SUCCESS);
}

int	handle_individual_textures(t_data *data, int i)
{
	if ((data->file_content[i - 1] == '\n' || i == 0)
		&& ft_strncmp(&data->file_content[i], "NO ", 3) == 0)
		set_individual_texture(data, NORTH, i);
	else if ((data->file_content[i - 1] == '\n' || i == 0)
		&& ft_strncmp(&data->file_content[i], "SO ", 3) == 0)
		set_individual_texture(data, SOUTH, i);
	else if ((data->file_content[i - 1] == '\n' || i == 0)
		&& ft_strncmp(&data->file_content[i], "WE ", 3) == 0)
		set_individual_texture(data, WEST, i);
	else if ((data->file_content[i - 1] == '\n' || i == 0)
		&& ft_strncmp(&data->file_content[i], "EA ", 3) == 0)
		set_individual_texture(data, EAST, i);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_map_metadata_textures(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (data->file_content[i] != '\0')
	{
		if (handle_individual_textures(data, i) == EXIT_SUCCESS)
			count++;
		i++;
	}
	if (data->map->north_path == NULL || data->map->south_path == NULL
		|| data->map->east_path == NULL || data->map->west_path == NULL)
		return (1);
	else if (count != 4)
		return (2);
	return (EXIT_SUCCESS);
}
