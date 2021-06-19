#include "../include/FdF.h"

void	iso(t_point *p)
{
	t_point	old;

	old.x = p->x;
	old.y = p->y;
	p->x = (old.x - old.y) * COS_ISO;
	p->y = -(p->z) + (old.x + old.y) * SIN_ISO;
}

t_point	project(t_point p, t_fdf *f)
{
	p.x *= f->c->scale;
	p.y *= f->c->scale;
	p.z *= f->c->scale / 4;
	p.x -= f->m->width * f->c->scale / 2;
	p.y -= f->m->height * f->c->scale / 2;
	return (p);
}
