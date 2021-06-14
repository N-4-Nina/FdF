#include "../include/FdF.h"
#include <stdio.h>

void    draw_pixel(t_fdf *f, int x, int y, unsigned int color)
{
	int i;

	if (x >= 0 && x < f->width && y >= 0 && y < f->height)
	{

		i = (x * (f->bpp / 8)) + (y * f->size_line);
		printf("%d  %d\n", x, y);
		ft_memcpy(f->data + i, &color, sizeof(int));
		// f->data[i] = color;
		// f->data[++i] = color >> 8;
		// f->data[++i] = color >> 16;
	}
}

void draw_line(int x0, int y0, int x1, int y1, t_fdf *f)
{ 
    int delta[2];
    int sx;
    int sy;
    int err[2];
 
    delta[0] = abs(x1 - x0);
    delta[1] = abs(y1 - y0);
    sx = (x0<x1) ? 1 : -1;
    sy  = (y0<y1) ? 1 : -1;
    err[0] = (delta[0]>delta[1] ? delta[0] : -delta[1])/2;
    while(1)
    {
        draw_pixel(f,  x0, y0, 16777215);
        if (x0==x1 && y0==y1)
            break;
        err[1] = err[0];
        if (err[1] >-delta[0])
        {
            err[0] -= delta[1];
            x0 += sx;
        }
        if (err[1] < delta[1])
        {
            err[0] += delta[0];
            y0 += sy;
        }
  }
}

t_point    project(t_point p, t_fdf *f)
{
    p.x *= f->c->dist;
	p.y *= f->c->dist;
	//p.z *= f->c->dist / f->c->z_divisor;
	p.x -= (f->m->width * f->c->dist) / 2;
	p.y -= (f->m->height * f->c->dist) / 2;
    return (p);
}
void    build_ridge(t_point one, t_point two, t_fdf *f)
{
    t_point p[2];

    p[0] = project(one, f);
    p[1] = project(two, f);
    draw_line(p[0].x, p[0].y, p[1].x, p[1].y, f);
}

int draw_mesh(t_fdf *f)
{
    int i;

    i = 0;
	printf("%d, %d \n", f->width/2, f->height/2);
	draw_pixel(f, 1079, 0, 16755095);
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