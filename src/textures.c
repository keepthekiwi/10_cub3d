/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:10:06 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:10:23 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

uint32_t	get_text(t_data *data);

int	get_rgb_a(t_data *data, int c, int a)
{
	if (c == -1)
		return (data->map->celing_color[0] << 24
			| data->map->celing_color[1] << 16
			| data->map->celing_color[2] << 8 | a);
	else if (c == 1)
		return (data->map->floor_color[0] << 24
			| data->map->floor_color[1] << 16
			| data->map->floor_color[2] << 8 | a);
	else
		return (255 << 24 | 0 << 16 | 0 << 8 | a);
}

int	load_png_textures(t_data *data)
{
	data->texture[0] = mlx_load_png(data->map->east_path);
	data->texture[1] = mlx_load_png(data->map->west_path);
	data->texture[2] = mlx_load_png(data->map->north_path);
	data->texture[3] = mlx_load_png(data->map->south_path);
	if (!(data->texture[0]) || !(data->texture[1])
		|| !(data->texture[2]) || !(data->texture[3]))
		return (set_error(data, INVALID_TEXTURES));
	return (EXIT_SUCCESS);
}

int	find_texture_x(t_data *data, mlx_texture_t *texture, t_ray *ray)
{
	int	tex_x;

	tex_x = (int)(where_hit_wall_x(data, ray) * (double) texture->width);
	if ((ray->side == 0 && ray->dir.x > 0)
		|| (ray->side == 1 && ray->dir.y < 0))
		tex_x = texture->width - tex_x - 1;
	return (tex_x);
}

void	insert_textures(t_data *data, int x, int draw_start, int draw_end)
{
	mlx_texture_t	*texture;
	double			step;
	double			texture_pos;

	texture = data->texture[data->ray.side];
	data->tex_x = find_texture_x(data, texture, &data->ray);
	step = (1.0 * texture->height) / (draw_end - draw_start);
	texture_pos = (draw_start - HEIGHT / 2 + (draw_end - draw_start)
			/ 2) * step;
	while (draw_start < draw_end)
	{
		data->tex_y = (int)(texture_pos) & (texture->height - 1);
		texture_pos += step;
		if (draw_start >= 0 && draw_start <= HEIGHT)
		{
			if (((draw_start * data->img->width + x) * 4)
				< (data->img->height * data->img->width * 4))
				ft_memcpy((char *) &data->img->pixels[
					(draw_start * data->img->width + x)
					* 4], (char *) &texture->pixels[(data->tex_y
						* texture->height + data->tex_x) * 4], 4);
		}
		draw_start++;
	}
}

void	draw_vertical_line(int ray_pos, int wallStart,
			int wallEnd, t_data *data)
{
	int	i;

	i = 0;
	insert_textures(data, ray_pos, wallStart, wallEnd);
	while (i < HEIGHT)
	{
		if (i < wallStart)
			mlx_put_pixel(data->img, ray_pos, i, get_rgb_a(data, -1, 180));
		if (i > wallEnd)
			mlx_put_pixel(data->img, ray_pos, i, get_rgb_a(data, 1, 180));
		i++;
	}
}
