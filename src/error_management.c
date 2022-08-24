/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:26:51 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:27:01 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	set_error(t_data *data, int error_num)
{
	data->error = error_num;
	return (error_num);
}

int	print_error(t_data *data)
{
	if (data->error == NO_ERROR)
		printf("cube3d: no error");
	else if (data->error == NUM_ARG)
		printf("cube3d: input handling: false number of arguments\n");
	else if (data->error == NO_PATH)
		printf("cube3d: input handling: please specify a map path\n");
	else if (data->error == INVALID_FILE_PATH)
		printf("cube3d: input handling: Not a valid filepath\n");
	else if (data->error == INVALID_MAP_WALLS)
		printf("cube3d: invalid map: walls\n");
	else if (data->error == INVALID_MAP_CHARACTERS)
		printf("cube3d: invalid map: spawnpoint quantity\n");
	else if (data->error == INVALID_MAP)
		printf("cube3d: invalid map\n");
	else if (data->error == INVALID_COLORS)
		printf("cube3d: invalid metadata: color(s)\n");
	else if (data->error == INVALID_TEXTURES)
		printf("cube3d: invalid metadata: texture(s)\n");
	else if (data->error == INVALID_ORDER)
		printf("cube3d: invalid file content: content order\n");
	else if (data->error == CREATE_WORLD)
		printf("cube3d: world building error\n");
	return (EXIT_FAILURE);
}
