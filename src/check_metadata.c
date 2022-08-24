/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_metadata.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:27:35 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:35:01 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	check_color_error(t_data *data, int j, int count)
{
	if (data->file_content[j] == ' ')
		return (EXIT_FAILURE);
	else if (data->file_content[j] == ','
		&& data->file_content[j + 1] == '\n')
		return (EXIT_FAILURE);
	else if ((data->file_content[j] == ','
			|| data->file_content[j] == '\n') && count > 3)
		return (EXIT_FAILURE);
	else if (((data->file_content[j] == ','
				&& data->file_content[j + 1] != ',')
			|| data->file_content[j] == '\n'))
		return (42);
	else
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	check_color(t_data *data, int i)
{
	int	j;
	int	count;

	if (data->file_content[i + 2] == ',')
		return (1);
	j = i + 2;
	count = 0;
	while (data->file_content[j] == ' ')
		j++;
	while (data->file_content[j] != '\n' && data->file_content[j] != '\0')
	{
		if (ft_isdigit(data->file_content[j]) == 1 && count < 3)
			count++;
		else if (check_color_error(data, j, count) == 42)
			count = 0;
		else if (check_color_error(data, j, count) != EXIT_SUCCESS)
			return (EXIT_FAILURE);
		j++;
	}
	return (EXIT_SUCCESS);
}

int	check_textures(t_data *data)
{
	if (ft_strncmp(&data->map->south_path
			[ft_strlen(data->map->south_path) - 4], ".png", 4) != 0)
		return (1);
	else if (ft_strncmp(&data->map->north_path
			[ft_strlen(data->map->north_path) - 4], ".png", 4) != 0)
		return (2);
	else if (ft_strncmp(&data->map->east_path
			[ft_strlen(data->map->east_path) - 4], ".png", 4) != 0)
		return (3);
	else if (ft_strncmp(&data->map->west_path
			[ft_strlen(data->map->west_path) - 4], ".png", 4) != 0)
		return (4);
	if (ft_strchr(data->map->south_path, ' ') != NULL)
		return (5);
	if (ft_strchr(data->map->north_path, ' ') != NULL)
		return (6);
	if (ft_strchr(data->map->west_path, ' ') != NULL)
		return (7);
	if (ft_strchr(data->map->east_path, ' ') != NULL)
		return (8);
	return (EXIT_SUCCESS);
}
