#include "../include/FdF.h"

int	mousemotion(int x, int y, void *param)
{
	t_fdf	*f;

	f = (t_fdf *)param;
	if (f->mousedown == 0)
		return (1);
	f->c->offset.x -= f->cursor.x - x;
	f->c->offset.y -= f->cursor.y - y;
	f->cursor.x = x;
	f->cursor.y = y;
	return (1);
}

int	mousepress(int button, int x, int y, void *param)
{
	t_fdf	*f;

	f = (t_fdf *)param;
	if (button == 4)
		return (scale_up(x, y, f));
	else if (button == 5)
		return (scale_down(f));
	if (button != 1)
		return (0);
	f->mousedown = 1;
	f->cursor.x = x;
	f->cursor.y = y;
	(void)param;
	return (1);
}

int	mouserelease(int button, int x, int y, void *param)
{
	t_fdf	*f;

	if (button != 1)
		return (0);
	f = (t_fdf *)param;
	f->mousedown = 0;
	(void)button;
	(void)x;
	(void)y;
	return (1);
}

int	keypress(int keycode, void *param)
{
	t_fdf	*f;

	f = (t_fdf *)param;
	if (keycode == 120 || keycode == 121 || keycode == 122)
		f->c->rotMode = keycode - 120;
	else if (keycode == 116)
		f->c->rotMode = 3;
	else if (keycode == 105)
		f->c->iso = 1 - f->c->iso;
	else if (keycode == LTURN)
		left_arrow(f);
	else if (keycode == RTURN)
		right_arrow(f);
	if (keycode == ESCAPE)
		free_and_exit(f);
	return (keycode);
}
