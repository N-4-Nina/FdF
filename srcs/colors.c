#include "../include/FdF.h"

double	get_ratio(int start, int end, int current)
{
	double	placement;
	double	distance;

	placement = current - start;
	distance = end - start;
	if (!distance)
		return (1.0);
	else
		return (placement / distance);
}

int	get_shade(int start, int end, double ratio)
{
	return ((int)((1 - ratio) * start) + ratio * end);
}

void	set_point_color(int index, int z, char *str, t_fdf *f)
{
	int	i;

	i = 0;
	while (str[i] >= 48 && str[i] <= 57)
		i++;
	if (str[i] && str[i] == ',')
		f->m->vert[index].color = hextoint(&str[i]);
	else
		f->m->vert[index].color = set_default_color(f->m->bottom, f->m->top, z);
}

int	set_default_color(int bottom, int top, int point)
{
	double	ratio;

	ratio = get_ratio(bottom, top, point);
	if (ratio < 0.1)
		return (COL_ONE);
	else if (ratio < 0.2)
		return (COL_TWO);
	else if (ratio < 0.3)
		return (COL_THR);
	else if (ratio < 0.4)
		return (COL_FOU);
	else if (ratio < 0.5)
		return (COL_FIV);
	else if (ratio < 0.6)
		return (COL_SIX);
	else if (ratio < 0.7)
		return (COL_SEV);
	else if (ratio < 0.8)
		return (COL_EIG);
	else if (ratio < 0.9)
		return (COL_NIN);
	else
		return (COL_TEN);
}

int	get_color(t_vert start, t_vert end, t_vert current, t_point delta)
{
	int		rgb[3];
	double	ratio;

	if (current.color == end.color)
		return (start.color);
	if (delta.x > delta.y)
		ratio = get_ratio(start.p.x, end.p.x, current.p.x);
	else
		ratio = get_ratio(start.p.y, end.p.y, current.p.y);
	rgb[0] = get_shade((start.color >> 16) & 0xFF, \
	(end.color >> 16) & 0xFF, ratio);
	rgb[1] = get_shade((start.color >> 8) & 0xFF, \
	(end.color >> 8) & 0xFF, ratio);
	rgb[2] = get_shade(start.color & 0xFF, end.color & 0xFF, ratio);
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
