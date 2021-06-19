#include "../include/FdF.h"

int	scale_up(int x, int y, t_fdf *f)
{
	t_point	val;

	if (f->c->scale <= INT_MAX)
	{
		f->c->scale += 1;
		val.x = (x - f->width / 2) / 50;
		val.y = (y - f->height / 2) / 50;
		f->c->offset.x -= val.x;
		f->c->offset.y -= val.y;
	}
	return (1);
}

int	scale_down(t_fdf *f)
{
	if (f->c->scale >= 0)
		f->c->scale -= 1;
	return (1);
}

int	left_arrow(t_fdf *f)
{
	if (f->c->rotMode < 3)
		f->c->rot[f->c->rotMode] -= 0.0174533;
	else
	{
		f->c->rot[0] -= 0.0174533;
		f->c->rot[1] -= 0.0174533;
		f->c->rot[2] -= 0.0174533;
	}
	return (1);
}

int	right_arrow(t_fdf *f)
{
	if (f->c->rotMode < 3)
		f->c->rot[f->c->rotMode] += 0.0174533;
	else
	{
		f->c->rot[0] += 0.0174533;
		f->c->rot[1] += 0.0174533;
		f->c->rot[2] += 0.0174533;
	}
	return (1);
}
