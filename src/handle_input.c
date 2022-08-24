/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:26:04 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:30:24 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

bool	is_map_char(t_data *data, int i)
{
	if (data->file_content[i] != '\0' && (data->file_content[i] == '1'
			|| data->file_content[i] == '0' || data->file_content[i] == 'N'
			|| data->file_content[i] == 'S' || data->file_content[i] == 'E'
			|| data->file_content[i] == 'W' || (data->file_content[i] == '\n'
				&& data->file_content[i + 1] != '\0')
			|| data->file_content[i] == ' '))
		return (true);
	return (false);
}

int	import_file(t_data *data, int fd_map)
{
	char	c[2];
	int		chars_read;
	char	*file_content;
	char	*tmp_str;

	chars_read = read(fd_map, &c, 1);
	c[1] = '\0';
	file_content = ft_strjoin("", c);
	while (chars_read == 1)
	{
		chars_read = read(fd_map, &c, 1);
		c[1] = '\0';
		tmp_str = ft_strjoin(file_content, c);
		free(file_content);
		file_content = tmp_str;
	}
	data->file_content = file_content;
	return (0);
}

int	create_map_str(t_data *data)
{
	int	i;

	i = 0;
	data->map->map_str = ft_strdup
		(&data->file_content[data->map_start_in_file]);
	return (EXIT_SUCCESS);
}

int	check_input(t_data *data)
{
	if (data->argc != 2)
		return (set_error(data, NUM_ARG));
	data->map->map_path = data->argv[1];
	if (data->map->map_path == NULL)
		return (set_error(data, NO_PATH));
	return (EXIT_SUCCESS);
}

int	handle_input(t_data *data)
{
	int	fd_map;

	fd_map = 0;
	if (check_input(data) != 0)
		return (data->error);
	fd_map = open(data->map->map_path, fd_map);
	if (fd_map < 0)
		return (set_error(data, INVALID_FILE_PATH));
	import_file(data, fd_map);
	if (set_map_dimensions(data) != 0)
		return (set_error(data, INVALID_MAP));
	create_empty_map(data);
	create_map_str(data);
	set_map_content(data);
	if (set_map_metadata_textures(data) != 0)
		return (set_error(data, INVALID_TEXTURES));
	if (check_textures(data) != 0)
		return (set_error(data, INVALID_TEXTURES));
	if (set_map_metadata_color(data) != 0)
		return (set_error(data, INVALID_COLORS));
	if (check_map(data) != 0)
		return (data->error);
	return (EXIT_SUCCESS);
}
