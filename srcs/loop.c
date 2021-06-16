#include "../include/FdF.h"

int	loop(void *param)
{
	t_fdf *f;

	f = (t_fdf*)param;
	while (f->run)
	{        
		//update(f);
		f->img = mlx_new_image(f->mlx, f->width, f->height);
		f->data = mlx_get_data_addr(f->img, &f->bpp, &f->size_line, &f->endian);
		draw_mesh(f);
		mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
		//mlx_clear_window(f->mlx, f->win);
		mlx_destroy_image(f->mlx, f->img);
	}
    //free_and_exit();
	return (0);
}