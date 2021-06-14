#include "../include/FdF.h"
#include <stdio.h>

void    draw_pixel(t_fdf *f, int x, int y, int color)
{
	int i;

	if (x >= 0 && x < f->width && y >= 0 && y < f->height)
	{

		i = (y/4 * f->size_line + x/4 * (f->bpp / 8));;
		// printf("%d  %d\n", x, y);
		ft_memcpy(f->data + i, &color, sizeof(unsigned int));
		// f->data[i] = color;
		// f->data[++i] = color >> 8;
		// f->data[++i] = color >> 16;
	}
}

void draw_line(int x0, int y0, int x1, int y1, t_fdf *f)
{ 
	int dx = abs(x1-x0), sx = x0<x1 ? 1 : -1;
	int dy = abs(y1-y0), sy = y0<y1 ? 1 : -1; 
	int err = (dx>dy ? dx : -dy)/2, e2;
 
	while(1){
    	draw_pixel(f, x0,y0, 16777215);
    	if (x0==x1 && y0==y1) break;
    	e2 = err;
    	if (e2 >-dx) { err -= dy; x0 += sx; }
    	if (e2 < dy) { err += dx; y0 += sy; }
  }
}
	// t_point	delta;
	// t_point	sign;
	// t_point	cur;
	// int		error[2];

	// delta.x = FT_ABS(s.x - f.x);
	// delta.y = FT_ABS(s.y - f.y);
	// sign.x = f.x < s.x ? 1 : -1;
	// sign.y = f.y < s.y ? 1 : -1;
	// error[0] = delta.x - delta.y;
	// cur = f;
	// while (cur.x != s.x || cur.y != s.y)
	// {
	// 	put_pixel(fdf, cur.x, cur.y, get_color(cur, f, s, delta));
	// 	if ((error[1] = error[0] * 2) > -delta.y)
	// 	{
	// 		error[0] -= delta.y;
	// 		cur.x += sign.x;
	// 	}
	// 	if (error[1] < delta.x)
	// 	{
	// 		error[0] += delta.x;
	// 		cur.y += sign.y;


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
	//printf("%d, %d \n", f->width/2, f->height/2);
	draw_line(0, 0, f->width, f->height, f);
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