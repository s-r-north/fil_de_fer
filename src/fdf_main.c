/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorth <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/27 11:47:49 by snorth            #+#    #+#             */
/*   Updated: 2017/08/11 19:58:06 by snorth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_func(int err, char *print)
{
	ft_putendl(print);
	exit(err);
}

void	mlx_init_var(t_env *env)
{
	env->win_x = WIN_X;
	env->bpp = 32;
	env->e = 1;
	env->mlx = mlx_init();
	env->win = mlx_new_window(env->mlx, WIN_X, WIN_Y, "FdF");
	env->img = mlx_new_image(env->mlx, WIN_X, WIN_Y);
	env->data = (int*)mlx_get_data_addr(env->img, &(env->bpp), &(env->win_x),
			&(env->e));
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
		env->color = ((rand() % 256) << 16) | ((rand() % 256) << 8) |
				(rand() % 256);
	}
}

int		main(int ac, char **av)
{
	int		fd;
	t_env	*env;

	if (ac != 2)
		exit_func(0, "Usage: Execute with One Map");
	if (ft_strlen(av[1]) < 4 || ft_strcmp(av[1] + ft_strlen(av[1]) - 4, ".fdf"))
		exit_func(0, "Usage: File must be of type \".fdf\"");
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
