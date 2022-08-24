/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:31:10 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 13:53:20 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

#include "../inc/cub3d.h"

void	movement_wsad(t_data *data, int a, int b, bool ws)
{
	t_vect	vector;

	if (ws)
	{
		vector.x = data->player->pos.x + a
			*(data->player->dir.x * MOVESPEED);
		vector.y = data->player->pos.y + b
			*(data->player->dir.y * MOVESPEED);
	}
	else
	{
		vector.x = data->player->pos.x + a
			*(data->player->dir.y * MOVESPEED);
		vector.y = data->player->pos.y + b
			*(data->player->dir.x * MOVESPEED);
	}
	if (data->map->map_content[(int)vector.y][(int)vector.x] == '0'
		|| data->map->map_content[(int)vector.y][(int)vector.x] == 'N'
		|| data->map->map_content[(int)vector.y][(int)vector.x] == 'W'
		|| data->map->map_content[(int)vector.y][(int)vector.x] == 'S'
		|| data->map->map_content[(int)vector.y][(int)vector.x] == 'O')
	{
		data->player->pos.x = vector.x ;
		data->player->pos.y = vector.y;
	}
}

void	rotation_left_right(t_data *data)
/* left 1, right -1 */
{
	mlx_t	*mlx;

	mlx = data->mlx;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT)
		|| mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	{
		if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
			rotation(data, 1);
		else
			rotation(data, -1);
	}
}

void	rotation(t_data *data, int dir)
{
	float	old_dir_x;
	float	old_plane_x;

	old_dir_x = data->player->dir.x;
	old_plane_x = data->player->plane.x;
	data->player->dir.x = data->player->dir.x * cos(dir * ROTSPEED)
		- data->player->dir.y * sin(dir * ROTSPEED);
	data->player->dir.y = old_dir_x * sin(dir * ROTSPEED)
		+ data->player->dir.y * cos(dir * ROTSPEED);
	data->player->plane.x = data->player->plane.x
		* cos(ROTSPEED) - data->player->plane.y * sin(dir * ROTSPEED);
	data->player->plane.y = old_plane_x * sin(dir * ROTSPEED)
		+ data->player->plane.y * cos(dir * ROTSPEED);
}

void	rotation_mouse(t_data *data)
{
	int			x;
	int			y;
	static int	old_x;

	mlx_get_mouse_pos(data->mlx, &x, &y);
	if (x <= WIDTH && x >= 0)
	{
		if (x < old_x)
			rotation(data, 1);
		else if (x > old_x)
			rotation(data, -1);
	}
	old_x = x;
}
