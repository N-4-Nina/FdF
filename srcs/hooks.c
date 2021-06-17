#include "../include/FdF.h"

int	keyrelease(int keycode, void *param)
{
	t_fdf	*f;

	f = (t_fdf*)param;
	return (keycode);
}

int	keypress(int keycode, void *param)
{
	t_fdf	*f;

	f = (t_fdf*)param;
	if (keycode == 120 || keycode == 121 || keycode == 122)
		f->c->rotMode = keycode - 120;
	else if (keycode == 116)
		f->c->rotMode = 3;
	if (keycode == LTURN)
	{
		if (f->c->rotMode < 4)
        	f->c->rot[f->c->rotMode] -= 0.0174533;
		else
		{
			f->c->rot[0] -= 0.0174533;
			f->c->rot[1] -= 0.0174533;
			f->c->rot[2] -= 0.0174533;
		}
	}
    if (keycode == RTURN)
    {
        if (f->c->rotMode < 4)
        	f->c->rot[f->c->rotMode] += 0.0174533;
		else
		{
			f->c->rot[0] += 0.0174533;
			f->c->rot[1] += 0.0174533;
			f->c->rot[2] += 0.0174533;
		}
	}
	if (keycode == ESCAPE)
		free_and_exit(f);
	return (keycode);
}
