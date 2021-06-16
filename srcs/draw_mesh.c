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

void draw_line(t_point p0, t_point p1, t_fdf *f)
{ 
	int dx = abs(p1.x-p0.x), sx = p0.x<p1.x ? 1 : -1;
	int dy = abs(p1.y-p0.y), sy = p0.y<p1.y ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
 
	while(1)
	{
    	draw_pixel(f, p0.x,p0.y, 16777215);
    	if (p0.x==p1.x && p0.y==p1.y) break;
    	e2 = err;
    	if (e2 >-dx) { err -= dy; p0.x += sx; }
    	if (e2 < dy) { err += dx; p0.y += sy; }
  }
}

void	rotate_x(t_point *p)
{
	t_point old;

	old.y = p->y;
	old.z = p->z;
	p->y = old.y * cos(0.523599) + old.z * sin(0.523599);
	p->z = -old.y*sin(0.523599) + old.z * cos(0.523599);
}

void	rotate_y(t_point *p) 
{
	t_point old;

	old.x = p->x;
	old.z = p->z;
	p->x = old.x*cos(0.523599) + old.z * sin(0.523599);
	p->z = -old.x*sin(0.523599) + old.z * cos(523599);
}

void	rotate_z(t_point *p)
{
	t_point old;

	old.x = p->x;
	old.y = p->y;
	p->x = old.x*cos(0.523599) - old.y*sin(0.523599);
	p->y = old.x*sin(0.523599) + old.y*cos(0.523599);
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
	// p.x += (f->m->width * f->c->scale)/2.5;
	// p.y += (f->m->height * f->c->scale)/2.5;

    return (p);
}
void    build_ridge(t_point one, t_point two, t_fdf *f)
{
    t_point p[2];

    p[0] = project(one, f);
    p[1] = project(two, f);
	iso(&p[0]);
	iso(&p[1]);
    draw_line(p[0], p[1], f);
}

int draw_mesh(t_fdf *f)
{
    int i;

    i = 0;
	//printf("%d, %d \n", f->width/2, f->height/2);
	//draw_line(0, 0, f->width, f->height, f);

    while (i < f->m->size)
    {
        if (f->m->vert[i].x + 1 < f->m->width)
            build_ridge(f->m->vert[i], f->m->vert[i + 1], f);
        if (f->m->vert[i].y + 1 < f->m->height)
            build_ridge(f->m->vert[i], f->m->vert[i + f->m->width], f);
        i++;
    } 
    return (0); 
}