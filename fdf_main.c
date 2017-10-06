#include "fdf.h"

void	numswap(t_xy *xy)
{
	float	tmp;

	tmp = xy->x1;
	xy->x1 = xy->x2;
	xy->x2 = tmp;
	tmp = xy->y1;
	xy->y1 = xy->y2;
	xy->y2 = tmp;
}

void	slope_calc(t_xy *xy)
{
	xy->dx = xy->x2 - xy->x1;
	xy->dy = xy->y2 - xy->y1;
	xy->slope = fabsf(xy->dy) > fabsf(xy->dx) ? xy->dx / xy->dy :
			xy->dy / xy->dx;
	if (xy->dx < 0 && xy->dy < 0 && xy->slope >= 0)
		numswap(xy);
	if (xy->slope < 0)
	{
		if (fabsf(xy->dy) <= fabsf(xy->dx) && xy->dx < 0)
			numswap(xy);
		if (fabsf(xy->dy) > fabsf(xy->dx) && xy->dy < 0)
			numswap(xy);
	}
}

void	negative_steep(t_xy *xy, t_env *env)
{
	while (xy->x1 >= xy->x2 && xy->y1 <= xy->y2)
	{
		if (xy->x1 >= 0 && xy->y1 >= 0 && xy->x1 < WIN_X && xy->y1 < WIN_Y &&
				(int)(xy->x1) + ((int)(xy->y1) * WIN_X) < WIN_X * WIN_Y - 1)
			env->data[(int)xy->x1 + ((int)xy->y1 * WIN_X)] = env->color;
		xy->x1 += fabsf(xy->dy) > fabsf(xy->dx) ? xy->slope : 1;
		xy->y1 += fabsf(xy->dy) > fabsf(xy->dx) ? 1 : xy->slope;
	}
}

void	negative_grad(t_xy *xy, t_env *env)
{
	while (xy->x1 <= xy->x2 && xy->y1 >= xy->y2)
	{
		if (xy->x1 >= 0 && xy->y1 >= 0 && xy->x1 < WIN_X && xy->y1 < WIN_Y &&
				(int)(xy->x1) + ((int)(xy->y1) * WIN_X) < WIN_X * WIN_Y - 1)
			env->data[(int)xy->x1 + ((int)xy->y1 * WIN_X)] = env->color;
		xy->x1 += fabsf(xy->dy) > fabsf(xy->dx) ? xy->slope : 1;
		xy->y1 += fabsf(xy->dy) > fabsf(xy->dx) ? 1 : xy->slope;
	}
}

void	positive_slope(t_xy *xy, t_env *env)
{
	while (xy->x1 <= xy->x2 && xy->y1 <= xy->y2)
	{
		if (xy->x1 >= 0 && xy->y1 >= 0 && xy->x1 < WIN_X && xy->y1 < WIN_Y &&
				(int)(xy->x1) + ((int)(xy->y1) * WIN_X) < WIN_X * WIN_Y - 1)
			env->data[(int)xy->x1 + ((int)xy->y1 * WIN_X)] = env->color;
		xy->x1 += fabsf(xy->dy) > fabsf(xy->dx) ? xy->slope : 1;
		xy->y1 += fabsf(xy->dy) > fabsf(xy->dx) ? 1 : xy->slope;
	}
}

void	line_draw(t_env *env, int x, int y)
{
	t_xy	xy;

	if (x < (env->map_x) - 1)
	{
		xy.x1 = (env->point[x + (env->map_x * y)]->image->x);
		xy.x2 = (env->point[x + 1 + (env->map_x * y)]->image->x);
		xy.y1 = (env->point[x + (env->map_x * y)]->image->y);
		xy.y2 = (env->point[x + 1 + (env->map_x * y)]->image->y);
		slope_calc(&xy);
		if (xy.slope < 0 && fabsf(xy.dy) > fabsf(xy.dx))
			negative_steep(&xy, env);
		else if (xy.slope < 0 && fabsf(xy.dy) <= fabsf(xy.dx))
			negative_grad(&xy, env);
		else if (xy.slope >= 0)
			positive_slope(&xy, env);
	}
	if (y < (env->map_y) - 1)
	{
		xy.x1 = (env->point[x + (env->map_x * y)]->image->x);
		xy.x2 = (env->point[x + (env->map_x * (y + 1))]->image->x);
		xy.y1 = (env->point[x + (env->map_x * y)]->image->y);
		xy.y2 = (env->point[x + (env->map_x * (y + 1))]->image->y);
		slope_calc(&xy);
		if (xy.slope < 0 && fabsf(xy.dy) > fabsf(xy.dx))
			negative_steep(&xy, env);
		else if (xy.slope < 0 && fabsf(xy.dy) <= fabsf(xy.dx))
			negative_grad(&xy, env);
		else if (xy.slope >= 0)
			positive_slope(&xy, env);
	}
}

void	draw_image(t_env *env)
{
	int x = -1;
	int y = -1;

	mlx_clear_window(env->mlx, env->win);
	ft_bzero(env->data, WIN_X * WIN_Y * (env->bpp / 8));
	while (++y < env->map_y)
	{
		x = -1;
		while (++x < env->map_x)
			line_draw(env, x, y);
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}

void	align_map(t_env *env)
{
	t_data	**pts;
	int		i;
	float	dot[3];

	pts = env->point;
	i = -1;
	while (++i < env->max_pt)
	{
		dot[0] = (pts[i]->map->x * env->scale * WIN_Y / env->map_y);
		dot[1] = (pts[i]->map->y * env->scale * WIN_Y / env->map_y);
		dot[2] = (pts[i]->map->z * env->scale * env->zmult);
		pts[i]->image->x = ((dot[0] * cos(env->ay) * cos(env->az)) - (dot[1] *
				cos(env->ay) * sin(env->az)) + (dot[2] * sin(env->ay))) +
				env->xoffset + (WIN_X / 2);
		pts[i]->image->y = ((dot[0] * (sin(env->ax) * sin(env->ay) *
				cos(env->az) - cos(env->ax) * sin(env->az))) + (dot[1] *
				(sin(env->ax) * sin(env->ay) * sin(env->az) + cos(env->ax) *
				cos(env->az))) - (dot[2] * cos(env->ay) * sin(env->ax))) +
				env->yoffset + (WIN_Y / 2);
	}
}

void	draw(t_env *env)
{
	align_map(env);
	draw_image(env);
	mlx_string_put (env->mlx, env->win, 25, 10, 0xffffff,
			"Arrow Keys: Move Wireframe");
	mlx_string_put (env->mlx, env->win, 25, 28, 0xffffff,
			"WASD: Rotate About X and Y Axes");
	mlx_string_put (env->mlx, env->win, 25, 46, 0xffffff,
			"Q/E: Rotate About Z-Axis");
	mlx_string_put (env->mlx, env->win, 25, 64, 0xffffff,
			"X: Set All Angles to Zero");
	mlx_string_put (env->mlx, env->win, 25, 82, 0xffffff,
			"Z/C: Change Zoom (0 Resets Zoom)");
	mlx_string_put (env->mlx, env->win, 25, 100, 0xffffff,
			"F/G: Change Height of Nonzero Z values");
	mlx_string_put (env->mlx, env->win, 25, 118, 0xffffff,
			"Space: Change Color");
	mlx_string_put (env->mlx, env->win, 25, 136, 0xffffff, "R: Reset");
	mlx_string_put (env->mlx, env->win, 25, 154, 0xffffff, "Esc: Exit");
}

void	alloc_points(t_env *env, t_data ***out)
{
	t_data	**tmp;
	int		i;

	tmp = ft_memalloc(sizeof(t_data*) * env->max_pt);
	i = -1;
	while (++i < env->max_pt)
	{
		tmp[i] = ft_memalloc(sizeof(t_data));
		tmp[i]->map = ft_memalloc(sizeof(t_xyz));
		tmp[i]->image = ft_memalloc(sizeof(t_xyz));
	}
	*out = tmp;
}

void	map_points(t_env *env, int **map)
{
	t_data	**pt_map;
	int		i;
	int		j;

	alloc_points(env, &pt_map);
	i = -1;
	j = -1;
	while (++i < env->max_pt)
	{
		if (!(i % env->map_x))
			++j;
		pt_map[i]->map->x = (float)(((i % env->map_x) + 1)) - (float)(env->map_x / 2);
		pt_map[i]->map->y = (float)(j + 1) - (float)(env->map_y / 2);
		pt_map[i]->map->z = (float)map[j][i % env->map_x];
	}
	env->point = pt_map;
}

void	line_to_map(int *in, char *line, int x)
{
	int i;

	i = 0;
	while (i < x)
	{
		in[i++] = ft_atoi(line);
		while (*line && *line != ' ')
			line++;
		while (*line == ' ')
			line++;
	}
}

void	exit_func(int err, char *print)
{
	ft_putendl(print);
	exit(err);
}

void	free_map(int ***map, int y)
{
	int i;

	i = -1;
	while (++i < y)
		free((*map)[i]);
	free(*map);
}

void	read_map(int fd, t_env *env)
{
	char	*line;
	int		**map;
	int		b;

	line = NULL;
	map = NULL;
	while ((b = get_next_line(fd, &line)) != 0)
	{
		if (b < 0)
			exit_func(1, "Read Error");
		if ((env->map_x && (int)ft_count_words(line, ' ') != env->map_x))
			exit_func(2, "Invalid Map");
		else if (!env->map_x)
			env->map_x = (int)ft_count_words(line, ' ');
		env->map_y++;
		map = (int**)ft_realloc(map, sizeof(int*) * env->map_y);
		map[env->map_y - 1] = (int*)ft_memalloc(sizeof(int) * env->map_x);
		line_to_map(map[env->map_y - 1], line, env->map_x);
	}
	env->max_pt = env->map_x * env->map_y;
	map_points(env, map);
	free_map(&map, env->map_y);
}

void	mlx_init_var(t_env *env)
{
	env->win_x = WIN_X;
	env->bpp = 32;
	env->e = 1;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_X, WIN_Y, "FdF");
	env->img = mlx_new_image(env->mlx, WIN_X, WIN_Y);
	env->data = (int*)mlx_get_data_addr(env->img, &(env->bpp), &(env->win_x), &(env->e));
}

void	init_var(t_env *env)
{
	env->xoffset = 0;
	env->yoffset = 0;
	env->scale = 0.5;
	env->ax = 0.43;
	env->ay = 0.31;
	env->az = 0;
	env->zmult = 10;
	if (!(env->color))
	{
		srand(time(NULL));
		env->color = g_color[rand() % 256];
	}
}

void	zero_var(t_env *env)
{
	env->ax = 0;
	env->ay = 0;
	env->az = 0;
}

void	key_angle_trans(int keycode, t_env *env)
{
	if (keycode == KEY_UP)
		env->yoffset -= 3;
	if (keycode == KEY_DN)
		env->yoffset += 3;
	if (keycode == KEY_LF)
		env->xoffset -= 3;
	if (keycode == KEY_RT)
		env->xoffset += 3;
	if (keycode == KEY_D)
		env->ay += 0.01;
	if (keycode == KEY_A)
		env->ay -= 0.01;
	if (keycode == KEY_S)
		env->ax -= 0.01;
	if (keycode == KEY_W)
		env->ax += 0.01;
	if (keycode == KEY_Q)
		env->az += 0.01;
	if (keycode == KEY_E)
		env->az -= 0.01;
}

int		press_key(int keycode, t_env *env)
{
	key_angle_trans(keycode, env);
	if (keycode == KEY_Z)
		env->scale *= 0.9;
	if (keycode == KEY_C)
		env->scale *= 1.1;
	if (keycode == KEY_R)
		init_var(env);
	if (keycode == KEY_0)
		env->scale = 0.5;
	if (keycode == KEY_F)
		env->zmult -= 0.5;
	if (keycode == KEY_G)
		env->zmult += 0.5;
	if (keycode == KEY_X)
		zero_var(env);
	if (keycode == KEY_SP)
	{
		env->color = g_color[rand() % 256];
	}
	draw(env);
	return (0);
}

void	good_exit(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->max_pt)
	{
		free(env->point[i]->map);
		free(env->point[i]->image);
		free(env->point[i]);
	}
	free(env->point);
	free(env);
	exit(0);
}

int		release_key(int keycode, t_env *env)
{
	if (keycode == KEY_ESC)
		good_exit(env);
	return (0);
}

int		main(int ac, char **av)
{
	int fd;
	t_env *env;

	if (ac != 2)
		exit_func(0, "Improper usage: Execute with One Map");
	if ((fd = open(av[1], O_RDONLY)) < 1)
		exit_func(4, "Open Error");
	env = ft_memalloc(sizeof(t_env));
	mlx_init_var(env);
	env->color = 0;
	init_var(env);
	read_map(fd, env);
	close(fd);
	draw(env);
	mlx_hook(env->win, 2, 0, press_key, env);
	mlx_hook(env->win, 3, 0, release_key, env);
	mlx_loop(env->mlx);
	return (0);
}
