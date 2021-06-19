#include "../include/FdF.h"

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
