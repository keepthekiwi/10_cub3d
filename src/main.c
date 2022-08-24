/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:12:14 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:58:56 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	get_player_position(t_data *data, t_var cordinate)
{
	int	dimension[2];

	dimension[0] = 0;
	while (dimension[0] < data->map->map_width)
	{
		dimension[1] = 0;
		while (dimension[1] < data->map->map_height)
		{
			if (data->map->map_content[dimension[0]][dimension[1]] == 'N'
				|| data->map->map_content[dimension[0]][dimension[1]] == 'W'
				|| data->map->map_content[dimension[0]][dimension[1]] == 'S'
				|| data->map->map_content[dimension[0]][dimension[1]] == 'E')
			{
				if (cordinate == X)
					return (dimension[0]);
				else if (cordinate == Y)
					return (dimension[1]);
			}
				dimension[1]++;
		}
		dimension[0]++;
	}
	return (-1);
}

static void	set_dir_ew(t_data *data, char c)
{
	if (c == 'E')
	{
		data->player->dir.x = 0;
		data->player->dir.y = 1;
		data->player->plane.x = PLANE;
		data->player->plane.y = 0;
	}
	if (c == 'W')
	{
		data->player->dir.x = 0;
		data->player->dir.y = -1;
		data->player->plane.x = -PLANE;
		data->player->plane.y = 0;
	}
}

static void	set_dir_ns(t_data *data, char c)
{
	if (c == 'N')
	{
		data->player->dir.x = 1;
		data->player->dir.y = 0;
		data->player->plane.x = 0;
		data->player->plane.y = -PLANE;
	}
	if (c == 'S')
	{
		data->player->dir.x = -1;
		data->player->dir.y = 0;
		data->player->plane.x = 0;
		data->player->plane.y = PLANE;
	}
}

static void	set_player_pos_dir(t_data *data)
{
	int	x;
	int	y;

	x = get_player_position(data, X);
	y = get_player_position(data, Y);
	data->player = malloc(sizeof(t_player));
	data->player->pos.x = y + 0.5;
	data->player->pos.y = x + 0.5;
	set_dir_ns(data, data->map->map_content[x][y]);
	set_dir_ew(data, data->map->map_content[x][y]);
	data->map->map_content[x][y] = '0';
}

int	main(int argc, char *argv[])
{
	t_data	data;
	t_map	map;

	ft_bzero(&data, sizeof(t_data));
	ft_bzero(&map, sizeof(t_map));
	data.map = &map;
	init_cub3d(&data, argc, argv);
	if (handle_input(&data) != 0)
		return (print_error(&data));
	set_player_pos_dir(&data);
	if (load_png_textures(&data) != EXIT_SUCCESS)
		return (print_error(&data));
	if (create_world(&data, 0) != EXIT_SUCCESS)
		return (print_error(&data));
	return (0);
}

// void mlx_terminate(mlx_t* mlx);
//void mlx_close_hook(mlx_t* mlx, mlx_closefunc func, void* param);

//doplle free - nico - erledig
//nord ost west süd blickrichtung noch machen - steve
// speilespoition löschen - steve
// maps durchschecken - nico
// errors vom razcaster abfangen - nico - erledigt
//exit funktion fall programm beendet wird - nico
// oben unen richtig seitlih um 3 falsch gespannt. deswegen segfault.
// wenn untershciedliche blickrichtungen x un y anpassen