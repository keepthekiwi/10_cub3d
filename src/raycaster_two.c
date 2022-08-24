/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:10:38 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:10:40 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdio.h>

#include "../inc/cub3d.h"

void	set_dist(t_data *data)
{
	data->ray.pos.x = (int)data->player->pos.x;
	data->ray.pos.y = (int)data->player->pos.y;
	calc_dist(data);
	data->ray.pos.x = (int)data->player->pos.x;
	data->ray.pos.y = (int)data->player->pos.y;
}

void	set_ray_dist(t_ray *ray)
{
	if (ray->side <= 1)
		ray->wall_dist = ray->side_dist.x - ray->delta_dist.x;
	else
		ray->wall_dist = ray->side_dist.y - ray->delta_dist.y;
}

void	set_draw_val(t_ray *ray, int *height, int *wallStart, int *wallEnd)
{
	*height = (int)(HEIGHT * 0.7 / ray->wall_dist);
	*wallStart = -(*height) / 2 + HEIGHT / 2;
	*wallEnd = (*height) / 2 + HEIGHT / 2;
}

void	raycaster(t_data *data)
{
	int		ray_pos;
	int		height;
	int		wallstart;
	int		wallend;

	ray_pos = 0;
	while (ray_pos < WIDTH)
	{
		reset_ray(&data->ray);
		init_rays(data, ray_pos);
		set_dist(data);
		perform_dda(data);
		set_ray_dist(&data->ray);
		set_draw_val(&data->ray, &height, &wallstart, &wallend);
		draw_vertical_line(ray_pos, wallstart, wallend, data);
		ray_pos++;
	}
}

double	where_hit_wall_x(t_data *data, t_ray *ray)
{
	double	wall_x;

	if (ray->side <= 1)
		wall_x = data->player->pos.y + ray->wall_dist * ray->dir.y;
	else
		wall_x = data->player->pos.x + ray->wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	return (wall_x);
}
