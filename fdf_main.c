#include "libs/libft/libft.h"
#include "libs/minilibx_macos/mlx.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct	s_xy
{
	int			x;
	int			y;
}				t_xy;

typedef struct	s_xyz
{
	float		x;
	float		y;
	float		z;
}				t_xyz;

typedef struct	s_data
{
	t_xyz		*map;
	t_xyz		*grid;
	t_xyz		*image;
}				t_data;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	int			*img_data;
	int			win_w;
	int			win_h;
	int			map_x;
	int			map_y;
	int			max_pt;
	int			scale;
	int			bits_per_pixel;
	int			endian;
	int			xoffset;
	int			yoffset;
	float		ax;
	float		ay;
	float		az;
	int			**map;
	t_data		**point;
}				t_env;

// void	make_simple_grid(int x, int y, int size)
// {
//	 void *mlx_ptr;
//	 void *win_ptr;
//	 int offset = 100;
//	 int i = 0;
//	 int j;
//	 mlx_ptr = mlx_init();
//	 win_ptr = mlx_new_window(mlx_ptr, 1920, 1080, "Butt");
//	 while (i <= y)
//	 {
//		 j = 0;
//		 while (j <= x)
//		 {
//			 if (!(j - (2 * i) % size) || !(-i - (2 * j) % size))
//			 {
//				 // mlx_string_put(mlx_ptr, win_ptr, offset + j, i + offset - 25, 0x00c3ff, "check");
//				 mlx_pixel_put(mlx_ptr, win_ptr, j + offset, i + offset, 0xffffff);
//			 }
//			 j++;
//		 }
//		 i++;
//	 }
//	 mlx_loop(mlx_ptr);
// }

// void	draw(t_env *env)
// {
//
// }

// void	print_map(t_env *env)
// {
// 	int i = -1;
// 	while (++i < env->max_pt)
// 		printf("(%.3f, %.3f, %.3f)\n", env->point[i]->map->x, env->point[i]->map->y, env->point[i]->map->z);
// }

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
		tmp[i]->grid = ft_memalloc(sizeof(t_xyz));
		tmp[i]->image = ft_memalloc(sizeof(t_xyz));
	}
	*out = tmp;
}

void	map_points(t_env *env)
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
		pt_map[i]->map->x = (float)((i % env->map_x) + 1);
		pt_map[i]->map->y = (float)(j + 1);
		pt_map[i]->map->z = (float)env->map[j][i % env->map_x];
		//printf("point: %.3f\tnum[%d][%d]: %d\n", pt_map[i]->map->z, j, i % env->map_x, env->map[j][i]);
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

// void	print_arr(int **arr, int x, int y)
// {
// 	int i = 0;
// 	int j = 0;
//
// 	while (i < y)
// 	{
// 		j = 0;
// 		while (j < x)
// 			printf("%d ", arr[i][j++]);
// 		printf("\n");
// 		i++;
// 	}
// }

void	read_map(int fd, t_env *env)
{
	char	*line;
	int		b;
	int		i;

	line = NULL;
	i = 0;
	while ((b = get_next_line(fd, &line)) != 0)
	{
		if ((env->map_x && (int)ft_count_words(line, ' ') != env->map_x) || b == -1)
			return ;
		else if (!env->map_x)
			env->map_x = (int)ft_count_words(line, ' ');
		env->map_y++;
		env->map = (int**)ft_realloc(env->map, sizeof(int*) * env->map_y);
		env->map[env->map_y - 1] = (int*)ft_memalloc(sizeof(int) * env->map_x);
		line_to_map(env->map[env->map_y - 1], line, env->map_x);
	}
	env->max_pt = env->map_x * env->map_y;
	map_points(env);
}

int		main(int ac, char **av)
{
	int fd;
	t_env *env;

	if (ac != 2)
		return (1);
	if ((fd = open(av[1], O_RDONLY)) < 1)
		return (-1);
	env = ft_memalloc(sizeof(t_env));
	read_map(fd, env);
	// if (!env->map_x || !env->map_y)
	// 	return (-1);
	close(fd);
	print_map(env);
	// draw(env);
	return (0);
}
