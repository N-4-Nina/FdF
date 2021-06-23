#include "../include/FdF.h"

void	set_extremes(int z, t_fdf *f)
{
	if (z > f->m->top)
	{
		f->m->top = z;
		f->m->zrange = z - abs(f->m->bottom);
	}
	else if (z < f->m->bottom)
	{
		f->m->bottom = z;
		f->m->zrange = f->m->zrange - abs(z);
	}
}

int	alloc_vertices(char **split, t_fdf *f)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	f->m->width = i;
	f->m->vert = malloc((sizeof(t_vert) + sizeof(t_point)) * i * f->m->height);
	if (!f->m->vert)
		return (-1);
	return (0);
}

int	parse_line(char *line, t_fdf *f)
{
	char		**split;
	int			i;
	int			z;
	static int	lineNb = 0;

	i = 0;
	split = ft_split(line, 32);
	if (!lineNb)
	{
		if (alloc_vertices(split, f))
			return (0);
	}
	else
		check_rectangle(split, f);
	while (i < f->m->width && split[i])
	{
		z = ft_atoi(split[i]);
		set_extremes(z, f);
		f->m->vert[i + (lineNb * f->m->width)].p = (t_point){i, lineNb, z};
		set_point_color(i + (lineNb * f->m->width), z, split[i], f);
		i++;
	}
	free_split(split);
	lineNb++;
	return (lineNb);
}

int	get_height(t_fdf *f)
{
	int		height;
	int		fd;
	int		empty;
	char	*line;

	height = 0;
	empty = 1;
	line = NULL;
	fd = open(f->filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		empty = 0;
		height++;
		free(line);
	}
	free(line);
	close(fd);
	if (empty)
		empty_map(f);
	return (height);
}

int	parse_file(t_fdf *f)
{
	char	*line;
	int		fd;
	int		i;

	line = NULL;
	i = 1;
	fd = open(f->filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	f->m->height = get_height(f);
	while (get_next_line(fd, &line))
	{
		if (!parse_line(line, f))
			return (abort_parse(line, fd, f));
		free(line);
		write(1, "parsed line ", 12);
		ft_putnbr_fd(i, 1);
		write(1, ".\n", 2);
		i++;
	}
	free(line);
	return (0);
}
