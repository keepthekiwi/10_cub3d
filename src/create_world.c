/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_world.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:31:19 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/12 16:39:07 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

#include "../inc/cub3d.h"

void	hook(void *param)
{	
	t_data	*data;
	mlx_t	*mlx;

	data = (t_data *) param;
	mlx = data->mlx;
	my_keyhook(data);
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	{
		mlx_close_window(mlx);
		exit(EXIT_SUCCESS);
	}
	rotation_left_right(data);
	rotation_mouse(data);
	raycaster(data);
}

int	create_world(t_data *data, int i)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "Bunker3d", false);
	if (!(data->mlx))
		return (1);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	if (!data->mlx)
		return (set_error(data, CREATE_WORLD));
	mlx_loop_hook(data->mlx, &hook, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	while (i <= 3)
		mlx_delete_texture(data->texture[i]);
	return (0);
}

void	my_keyhook(void *param)
/* https://github.com/codam-coding-college/MLX42/wiki/Hooks */
{
	t_data	*data;

	data = (t_data *) param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		movement_wsad(data, 1, 1, true);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		movement_wsad(data, -1, -1, true);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		movement_wsad(data, -1, 1, false);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		movement_wsad(data, 1, -1, false);
}
