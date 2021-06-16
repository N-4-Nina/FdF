#include "../include/FdF.h"
#include <stdio.h>
int	keyrelease(int keycode, void *param)
{
	t_fdf	*f;

	f = (t_fdf*)param;
	f->key[keycode] = 0;
	return (keycode);
}

int	keypress(int keycode, void *param)
{
	t_fdf	*f;

	f = (t_fdf*)param;
	printf("%d hi\n", keycode);
	if (keycode == LTURN)
        f->c->rot[0] -= 0.0174533;
    if (keycode == RTURN)
        f->c->rot[0] += 0.0174533;
	// if (keycode == ESCAPE)
	// 	free_and_exit(f);
	return (keycode);
}
