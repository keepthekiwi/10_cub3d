/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 16:31:29 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 13:57:20 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

#include "../inc/cub3d.h"

uint32_t	get_text(t_data *data);

void	reset_ray(t_ray *ray)
{
	ray->camera = 0;
	ray->dir.x = 0;
	ray->dir.y = 0;
	ray->pos.x = 0;
	ray->pos.y = 0;
	ray->side_dist.x = 0;
	ray->side_dist.y = 0;
	ray->delta_dist.x = 0;
	ray->delta_dist.y = 0;
	ray->side = 0;
	ray->hit = 0;
	ray->wall_dist = 0;
}

void	init_rays(t_data *data, int ray_pos)
{
	data->ray.camera = 2 * ray_pos / (float) WIDTH - 1;
	data->ray.dir.x = data->player->dir.x
		+ data->player->plane.x * data->ray.camera;
	data->ray.dir.y = data->player->dir.y
		+ data->player->plane.y * data->ray.camera;
	if (data->ray.dir.x == 0)
		data->ray.delta_dist.x = INFINITY;
	else
		data->ray.delta_dist.x = fabs(1.0 / data->ray.dir.x);
	if (data->ray.dir.y == 0)
		data->ray.delta_dist.y = INFINITY;
	else
		data->ray.delta_dist.y = fabs(1.0 / data->ray.dir.y);
}

void	calc_dist(t_data *data)
{
	if (data->ray.dir.x < 0)
	{
		data->ray.step.x = -1;
		data->ray.side_dist.x = (data->player->pos.x
				- data->ray.pos.x) * data->ray.delta_dist.x;
	}
	else
	{
		data->ray.step.x = 1;
		data->ray.side_dist.x = (data->ray.pos.x + 1.0 - data->player->pos.x)
			* data->ray.delta_dist.x;
	}
	if (data->ray.dir.y < 0)
	{
		data->ray.step.y = -1;
		data->ray.side_dist.y = (data->player->pos.y
				- data->ray.pos.y) * data->ray.delta_dist.y;
	}
	else
	{
		data->ray.step.y = 1;
		data->ray.side_dist.y = (data->ray.pos.y + 1.0
				- data->player->pos.y) * data->ray.delta_dist.y;
	}
}

void	perform_dda(t_data *data)
{
	while (data->ray.hit == 0)
	{
		if (data->ray.side_dist.x < data->ray.side_dist.y)
		{
			data->ray.side_dist.x += data->ray.delta_dist.x;
			data->ray.pos.x += data->ray.step.x;
			data->ray.side = 0;
			if (data->ray.dir.x > 0)
				data->ray.side = 1;
		}
		else
		{
			data->ray.side_dist.y += data->ray.delta_dist.y;
			data->ray.pos.y += data->ray.step.y;
			data->ray.side = 2;
			if (data->ray.dir.y > 0)
				data->ray.side = 3;
		}
		if (data->map->map_content[data->ray.pos.y][data->ray.pos.x] == '1')
			data->ray.hit = 1;
	}
}
