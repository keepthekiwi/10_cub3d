/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaas <nhaas@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 14:06:57 by nhaas             #+#    #+#             */
/*   Updated: 2022/08/16 14:40:07 by nhaas            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>

# include "../libft/libft.h"
# include "../MLX42/include/MLX42/MLX42.h"

# define WIDTH 1920
# define HEIGHT 1080

# define PLANE 1.62
# define MOVESPEED 0.055
# define ROTSPEED 0.055

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define PURPLE		"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define RESET		"\033[0m"
# define GREEN_BG	"\e[42m"

typedef enum s_error_type
{
	NO_ERROR,
	NUM_ARG,
	NO_PATH,
	INVALID_FILE_PATH,
	INVALID_MAP_WALLS,
	INVALID_MAP_CHARACTERS,
	INVALID_MAP,
	INVALID_COLORS,
	INVALID_TEXTURES,
	INVALID_ORDER,
	CREATE_WORLD
}	t_error_type;

typedef enum s_var
{
	SOUTH,
	NORTH,
	WEST,
	EAST,
	X,
	Y
}	t_var;

typedef struct s_map {
	char	*map_path;
	char	*map_str;
	int		map_height;
	int		map_width;
	char	**map_content;
	char	*north_path;
	char	*south_path;
	char	*east_path;
	char	*west_path;
	int		celing_color[3];
	int		floor_color[3];
}	t_map;

typedef struct s_vect
{
	float	x;
	float	y;
}				t_vect;

typedef struct s_intvect
{
	int		x;
	int		y;
}				t_intvect;

typedef struct s_player
{
	t_vect		pos;
	t_vect		dir;
	t_vect		plane;
}				t_player;

typedef struct s_ray
{
	float		camera;
	t_vect		dir;
	t_vect		side_dist;
	t_vect		delta_dist;
	t_intvect	pos;
	t_vect		step;
	int			hit;
	int			side;
	float		wall_dist;
}				t_ray;

typedef struct s_data {
	int				argc;
	char			**argv;
	int				error;
	t_ray			ray;
	t_map			*map;
	char			*file_content;
	int				map_start_in_file;
	t_player		*player;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*texture[4];
	int				tex_x;
	int				tex_y;

}	t_data;

int		handle_input(t_data *data);
int		check_map(t_data *data);
int		set_map_metadata_color(t_data *data);
int		set_map_metadata_textures(t_data *data);
int		check_textures(t_data *data);
int		check_color(t_data *data, int i);
int		set_map_content(t_data *data);
int		create_empty_map(t_data *data);
int		set_map_dimensions(t_data *data);
int		calculate_map_start(t_data *data);
bool	is_line_map_start(t_data *data, int i);
bool	is_map_char(t_data *data, int i);
int		set_error(t_data *data, int error_num);
int		print_error(t_data *data);
int		print_map(t_data *data);
int		print_metadata(t_data *data);
int		exit_game(t_data *data);
void	raycaster(t_data *data);
void	init_rays(t_data *data, int ray_pos);
void	perform_dda(t_data *data);
int		create_world(t_data *data, int i);
void	my_keyhook(void *param);
void	movement_wsad(t_data *data, int a, int b, bool ws);
void	rotation_left_right(t_data *data);
void	rotation(t_data *data, int dir);
void	rotation_mouse(t_data *data);
int		load_png_textures(t_data *data);
double	where_hit_wall_x(t_data *data, t_ray *ray);
void	insert_textures(t_data *data, int x, int draw_start, int draw_end);
int		find_texture_x(t_data *data, mlx_texture_t *texture, t_ray *ray);
int		get_rgb_a(t_data *data, int c, int a);
void	draw_vertical_line(int ray_pos, int wallStart,
			int wallEnd, t_data *data);
void	reset_ray(t_ray *ray);
void	calc_dist(t_data *data);
void	draw_vertical_line(int ray_pos, int wallStart,
			int wallEnd, t_data *data);
void	movement_wsad(t_data *data, int a, int b, bool ws);
void	rotation_left_right(t_data *data);
int		init_cub3d(t_data *data, int argc, char *argv[]);
int		check_charakter_quantity(t_data *data);

#endif