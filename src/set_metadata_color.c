/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_metadata_color.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:10:53 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:11:00 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	set_celing_color(t_data *data, int i)
{
	int		j;
	int		color;
	char	*tmp_str;

	color = 0;
	j = 0;
	tmp_str = NULL;
	while (data->file_content[i] != '\n'
		&& data->file_content[i] != '\0')
	{
		if (data->file_content[i + j] == ','
			|| data->file_content[i + j] == '\n')
		{
			tmp_str = ft_strndup(&data->file_content[i], j - 1);
			data->map->celing_color[color] = ft_atoi(tmp_str);
			free(tmp_str);
			color++;
			i += j + 1;
			j = 0;
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

int	set_floor_color(t_data *data, int i)
{
	int		j;
	int		color;
	char	*tmp_str;

	color = 0;
	j = 0;
	tmp_str = NULL;
	while (data->file_content[i] != '\n'
		&& data->file_content[i] != '\0')
	{
		if (data->file_content[i + j] == ','
			|| data->file_content[i + j] == '\n')
		{
			tmp_str = ft_strndup(&data->file_content[i], j - 1);
			data->map->floor_color[color] = ft_atoi(tmp_str);
			free(tmp_str);
			color++;
			i += j + 1;
			j = 0;
		}
		j++;
	}
	return (EXIT_SUCCESS);
}

int	handle_celing_color(t_data *data, int i, int found_flag)
{
	if (check_color(data, i) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	i++;
	while (data->file_content[i] == ' ')
		i++;
	set_celing_color(data, i);
	return (EXIT_SUCCESS);
}

int	handle_floor_color(t_data *data, int i, int found_flag)
{
	if (check_color(data, i) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	i++;
	while (data->file_content[i] == ' ')
		i++;
	set_floor_color(data, i);
	return (EXIT_SUCCESS);
}

int	set_map_metadata_color(t_data *data)
{
	char	*tmp_str;
	int		i;
	int		found_flag;
	int		error;

	i = 0;
	tmp_str = NULL;
	found_flag = 0;
	error = EXIT_SUCCESS;
	while (data->file_content[i] != '\0')
	{
		if ((data->file_content[i - 1] == '\n' || i == 0)
			&& ft_strncmp(&data->file_content[i], "C ", 2) == 0)
			error = handle_celing_color(data, i, found_flag++);
		else if ((data->file_content[i - 1] == '\n' || i == 0)
			&& ft_strncmp(&data->file_content[i], "F ", 2) == 0)
			error = handle_floor_color(data, i, found_flag++);
		if (error == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	if (found_flag != 2)
		return (1);
	return (EXIT_SUCCESS);
}
