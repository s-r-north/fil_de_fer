#include "fdf.h"

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
		pt_map[i]->map->x = (float)(((i % env->map_x) + 1)) -
				(float)(env->map_x / 2);
		pt_map[i]->map->y = (float)(j + 1) - (float)(env->map_y / 2);
		pt_map[i]->map->z = (float)map[j][i % env->map_x];
	}
	env->point = pt_map;
}

void	line_to_map(int *in, char *line, int x)
{
	int		i;

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

void	free_map(int ***map, int y)
{
	int		i;

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
