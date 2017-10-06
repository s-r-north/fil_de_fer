#include "fdf.h"

void	draw_image(t_env *env)
{
	int		x;
	int		y;

	mlx_clear_window(env->mlx, env->win);
	ft_bzero(env->data, WIN_X * WIN_Y * (env->bpp / 8));
	y = -1;
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
	mlx_string_put(env->mlx, env->win, 25, 10, 0xffffff,
			"Arrow Keys: Move Wireframe");
	mlx_string_put(env->mlx, env->win, 25, 28, 0xffffff,
			"WASD: Rotate About X and Y Axes");
	mlx_string_put(env->mlx, env->win, 25, 46, 0xffffff,
			"Q/E: Rotate About Z-Axis");
	mlx_string_put(env->mlx, env->win, 25, 64, 0xffffff,
			"X: Set All Angles to Zero");
	mlx_string_put(env->mlx, env->win, 25, 82, 0xffffff,
			"Z/C: Change Zoom (0 Resets Zoom)");
	mlx_string_put(env->mlx, env->win, 25, 100, 0xffffff,
			"F/G: Change Height of Nonzero Z values");
	mlx_string_put(env->mlx, env->win, 25, 118, 0xffffff,
			"Space: Change Color");
	mlx_string_put(env->mlx, env->win, 25, 136, 0xffffff, "R: Reset");
	mlx_string_put(env->mlx, env->win, 25, 154, 0xffffff, "Esc: Exit");
}
