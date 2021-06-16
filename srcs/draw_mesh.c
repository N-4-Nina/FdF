#include "../include/FdF.h"
#include <stdio.h>

void    draw_pixel(t_fdf *f, int x, int y, int color)
{
	int i;

	if (x >= 0 && x < f->width && y >= 0 && y < f->height)
	{

		i = (y * f->size_line + x * (f->bpp / 8));
		// printf("%d  %d\n", x, y);
		// ft_memcpy(f->data + i, &color, sizeof(unsigned int));
		f->data[i] = color;
		f->data[++i] = color >> 8;
		f->data[++i] = color >> 16;
	}
}

void draw_line(t_vert v0, t_vert v1, t_fdf *f)
{
	t_point d;
	t_point s;
	t_vert current;

	d.x = abs(v1.p.x-v0.p.x);
	s.x = v0.p.x<v1.p.x ? 1 : -1;
	d.y = abs(v1.p.y-v0.p.y);
	s.y = v0.p.y<v1.p.y ? 1 : -1;
	current = v0;
	int err = (d.x>d.y ? d.x : -d.y)/2, e2;
 
	while(1)
	{
		current.color = get_color(current, v1, current, d);
		//printf("%d\n", color);
    	draw_pixel(f, current.p.x, current.p.y, current.color);
    	if (current.p.x==v1.p.x && current.p.y==v1.p.y)
			break;
    	e2 = err;
    	if (e2 >-d.x) { err -= d.y; current.p.x += s.x; }
    	if (e2 < d.y) { err += d.x; current.p.y += s.y; }
  }
}

void	rotate_x(t_vert *v, t_cam *c)
{
	t_point old;

	old.y = v->p.y;
	old.z = v->p.z;
	v->p.y = old.y * cos(c->rot[0]) + old.z * sin(c->rot[0]);
	v->p.z = -old.y*sin(c->rot[0]) + old.z * cos(c->rot[0]);
}

void	rotate_y(t_vert *v, t_cam *c) 
{
	t_point old;

	old.x = v->p.x;
	old.z = v->p.z;
	v->p.x = old.x*cos(c->rot[1]) + old.z * sin(c->rot[1]);
	v->p.z = -old.x*sin(c->rot[1]) + old.z * cos(c->rot[1]);
}

void	rotate_z(t_vert *v, t_cam *c)
{
	t_point old;

	old.x = v->p.x;
	old.y = v->p.y;
	v->p.x = old.x*cos(c->rot[2]) - old.y*sin(c->rot[2]);
	v->p.y = old.x*sin(c->rot[2]) + old.y*cos(c->rot[2]);
}

void	iso(t_point *p)
{
	t_point	old;

	old.x = p->x;
	old.y = p->y;

	p->x = (old.x - old.y) * cos(0.523599);
	p->y = -(p->z) + (old.x + old.y) * sin(0.523599);
}

t_point    project(t_point p, t_fdf *f)
{
    p.x *= f->c->scale;
	p.y *= f->c->scale;
	p.z *= f->c->scale / 4;
	p.x -= f->m->width * f->c->scale / 2;
	p.y -= f->m->height *f->c->scale / 2;
	// p.x += (f->m->width * f->c->scale)/2.5;
	// p.y += (f->m->height * f->c->scale)/2.5;

    return (p);
}
void    build_ridge(t_vert one, t_vert two, t_fdf *f)
{
    t_vert v[2];

	v[0] = one;
	v[1] = two;
    v[0].p = project(one.p, f);
    v[1].p = project(two.p, f);
	iso(&v[0].p);
	iso(&v[1].p);
	v[0].p.x+= f->width/2;
	v[0].p.y+= (f->height +f->m->height * f->c->scale) / 2.5;
	v[1].p.x+= f->width/2;
	v[1].p.y+= (f->height +f->m->height * f->c->scale) / 2.5;

	rotate_x(&v[0], f->c);
	rotate_y(&v[0], f->c);
	rotate_z(&v[0], f->c);
	rotate_x(&v[1], f->c);
	rotate_y(&v[1], f->c);
	rotate_z(&v[1], f->c);
    draw_line(v[0], v[1], f);
}

int draw_mesh(t_fdf *f)
{
    int i;

    i = 0;
	//printf("%d, %d \n", f->width/2, f->height/2);
	//draw_line(0, 0, f->width, f->height, f);
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