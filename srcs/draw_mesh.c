#include "../include/FdF.h"

void	draw_pixel(t_fdf *f, int x, int y, int color)
{
	int	i;

	if (x >= 0 && x < f->width && y >= 0 && y < f->height)
	{
		i = (y * f->size_line + x * (f->bpp / 8));
		f->data[i] = color;
		f->data[++i] = color >> 8;
		f->data[++i] = color >> 16;
	}
}

void	init_linedraw(t_linedraw *l, t_vert v0, t_vert v1)
{
	l->d.x = abs(v1.p.x - v0.p.x);
	l->s.x = -1;
	if (v0.p.x < v1.p.x)
		l->s.x = 1;
	l->d.y = abs(v1.p.y - v0.p.y);
	l->s.y = -1;
	if (v0.p.y < v1.p.y)
		l->s.y = 1;
	l->current = v0;
	l->er[0] = -l->d.y / 2;
	if (l->d.x > l->d.y)
		l->er[0] = l->d.x / 2;
}

void	draw_line(t_vert v0, t_vert v1, t_fdf *f)
{
	t_linedraw	l;

	init_linedraw(&l, v0, v1);
	while (1)
	{
		l.current.color = get_color(l.current, v1, l.current, l.d);
		draw_pixel(f, l.current.p.x, l.current.p.y, l.current.color);
		if (l.current.p.x == v1.p.x && l.current.p.y == v1.p.y)
			break ;
		l.er[1] = l.er[0];
		if (l.er[1] > -l.d.x)
		{
			l.er[0] -= l.d.y;
			l.current.p.x += l.s.x;
		}
		if (l.er[1] < l.d.y)
		{
			l.er[0] += l.d.x;
			l.current.p.y += l.s.y;
		}
	}
}

void	build_ridge(t_vert one, t_vert two, t_fdf *f)
{
	t_vert	v[2];

	v[0] = one;
	v[1] = two;
	v[0].p = project(one.p, f);
	v[1].p = project(two.p, f);
	rotate_x(&v[0], f->c);
	rotate_y(&v[0], f->c);
	rotate_z(&v[0], f->c);
	rotate_x(&v[1], f->c);
	rotate_y(&v[1], f->c);
	rotate_z(&v[1], f->c);
	if (f->c->iso)
	{
		iso(&v[0].p);
		iso(&v[1].p);
	}
	v[0].p.x += f->width / 2 + f->c->offset.x;
	v[0].p.y += (f->height + f->m->height * f->c->scale) / 2.5 + f->c->offset.y;
	v[1].p.x += f->width / 2 + f->c->offset.x;
	v[1].p.y += (f->height + f->m->height * f->c->scale) / 2.5 + f->c->offset.y;
	draw_line(v[0], v[1], f);
}

int	draw_mesh(t_fdf *f)
{
	int	i;

	i = 0;
	while (i < f->m->size)
	{
		if (f->m->vert[i].p.x + 1 < f->m->width)
			build_ridge(f->m->vert[i], f->m->vert[i + 1], f);
		if (f->m->vert[i].p.y + 1 < f->m->height)
			build_ridge(f->m->vert[i], f->m->vert[i + f->m->width], f);
		i++;
	}
	return (0);
}
