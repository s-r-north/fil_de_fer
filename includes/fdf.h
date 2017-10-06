/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:47:49 by snorth            #+#    #+#             */
/*   Updated: 2017/08/11 19:58:06 by snorth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libs/libft/libft.h"
# include "../libs/minilibx_macos/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <time.h>

# define WIN_X 1920
# define WIN_Y 1080

# define KEY_UP 126
# define KEY_DN 125
# define KEY_LF 123
# define KEY_RT 124
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14
# define KEY_F 3
# define KEY_G 5
# define KEY_0 29
# define KEY_R 15
# define KEY_X 7
# define KEY_Z 6
# define KEY_C 8
# define KEY_ESC 53
# define KEY_SP 49

typedef struct		s_xy
{
	float			x1;
	float			x2;
	float			y1;
	float			y2;
	float			dx;
	float			dy;
	float			slope;
}					t_xy;

typedef struct		s_xyz
{
	float			x;
	float			y;
	float			z;
}					t_xyz;

typedef struct		s_data
{
	t_xyz			*map;
	t_xyz			*image;
}					t_data;

typedef struct		s_env
{
	void			*mlx;
	void			*win;
	void			*img;
	int				*data;
	int				win_x;
	int				win_y;
	int				bpp;
	int				e;
	int				map_x;
	int				map_y;
	int				max_pt;
	int				xoffset;
	int				yoffset;
	float			scale;
	float			ax;
	float			ay;
	float			az;
	float			zmult;
	int				color;
	t_data			**point;
}					t_env;

void				numswap(t_xy *xy);
void				slope_calc(t_xy *xy, t_env *env, int xy1, int xy2);
void				negative_steep(t_xy *xy, t_env *env);
void				negative_grad(t_xy *xy, t_env *env);
void				positive_slope(t_xy *xy, t_env *env);
void				line_draw(t_env *env, int x, int y);
void				draw_image(t_env *env);
void				align_map(t_env *env);
void				draw(t_env *env);
void				alloc_points(t_env *env, t_data ***out);
void				map_points(t_env *env, int **map);
void				line_to_map(int *in, char *line, int x);
void				exit_func(int err, char *print);
void				read_map(int fd, t_env *env);
void				free_map(int ***map, int y);
void				mlx_init_var(t_env *env);
void				init_var(t_env *env);
void				zero_var(t_env *env);
void				key_angle_trans(int keycode, t_env *env);
int					press_key(int keycode, t_env *env);
int					release_key(int keycode, t_env *env);
void				good_exit(t_env *env);

#endif
