#include "./libs/libft/libft.h"

void	read_some_stuff(int fd)
{
	char *line;
	char *tmp;
	int x;
	int y;

	line = ft_strnew(0);
	tmp = ft_strnew(4096);
	while (get_next_line(fd, &line))
	{
		if (x && ft_count_words(line, ' ') != x)
			exit(-1);
		if (!x)
			x = ft_count_words(line, ' ');
		tmp = ft_strncat(tmp, line, ft_strlen(line));
	}

}

int		main(int ac, char **av)
{
	int fd;

	if (ac != 2)
		return (0);
	fd = open(av[1], O_RDONLY);
	read_some_stuff(fd);
	close(fd);
	return (1);
}
