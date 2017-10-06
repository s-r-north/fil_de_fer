#include "fdf.h"

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
