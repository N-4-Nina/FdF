#include "../include/FdF.h"

void	empty_map(t_fdf *f)
{
	write(1, ".fdf file cannot be empty ! \n", 30);
	free(f->m);
	free(f->c);
	exit(-1);
}

int	abort_parse(char *line, int fd, t_fdf *f)
{
	int	i;

	i = 0;
	free(line);
	close(fd);
	if (f->m->vert)
		free(f->m->vert);
	return (-1);
}

int	free_and_exit(t_fdf *f)
{
	if (f->m->vert)
		free(f->m->vert);
	if (f->c)
		free(f->c);
	if (f->m)
		free(f->m);
	if (f->mlx && f->win)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx)
		free(f->mlx);
	exit(0);
}
