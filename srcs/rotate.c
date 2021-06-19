#include "../include/FdF.h"

void	rotate_x(t_vert *v, t_cam *c)
{
	t_point	old;

	old.y = v->p.y;
	old.z = v->p.z;
	v->p.y = old.y * cos(c->rot[0]) + old.z * sin(c->rot[0]);
	v->p.z = -old.y * sin(c->rot[0]) + old.z * cos(c->rot[0]);
}

void	rotate_y(t_vert *v, t_cam *c)
{
	t_point	old;

	old.x = v->p.x;
	old.z = v->p.z;
	v->p.x = old.x * cos(c->rot[1]) + old.z * sin(c->rot[1]);
	v->p.z = -old.x * sin(c->rot[1]) + old.z * cos(c->rot[1]);
}

void	rotate_z(t_vert *v, t_cam *c)
{
	t_point	old;

	old.x = v->p.x;
	old.y = v->p.y;
	v->p.x = old.x * cos(c->rot[2]) - old.y * sin(c->rot[2]);
	v->p.y = old.x * sin(c->rot[2]) + old.y * cos(c->rot[2]);
}
