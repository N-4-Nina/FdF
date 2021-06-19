#include "../include/FdF.h"

int	check_extension(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	if (i < 4)
		return (0);
	i--;
	return (s[i] == 'f' && s[i - 1] == 'd'\
	&& s[i - 2] == 'f' && s[i - 3] == '.');
}

void	display_logo(void)
{
	write(1, "\033[1;36m", 8);
	write(1, "  ______  _ ______\n", 20);
	write(1, " |  ____|| |  ___\n", 19);
	write(1, " | |__ __| | |__ \n", 19);
	write(1, " |  __/ _` |  __|\n", 19);
	write(1, " | | | (_| | |   \n", 19);
	write(1, " |_|  \\__,_|_|   \n\n\n", 21);
}

void	display_start(void)
{
	char	*start;

	write(1, "\033[1;32m Done !\n\n\n\n", 19);
	write(1, "\033[1;37m Welcome to \n", 21);
	display_logo();
	write(1, "\033[0;37m Since I'm too lazy to do a\
 proper graphic menu, here are the commands:\n\n", 81);
	write(1, "\033[1;37m ← → \033[0;37m arrows are \
used to rotate the mesh. \n", 62);
	write(1, "\033[1;37m X, Y & Z \033[0;37m set th\
e rotation axis respectively -default is Z-. \n", 78);
	write(1, "\033[1;37m T \033[0;37m sets the rota\
tion axis to X Y and Z simultaneously. \n", 72);
	write(1, "\033[1;37m I \033[0;37m switches from\
 iso to front perspective. \n", 60);
	write(1, "\033[1;37m clic & drag \033[0;37m to \
 move the mesh around -translation-. \n", 69);
	write(1, "\033[1;37m scroll wheel \033[0;37m to zoom in and out. \n", 51);
	write(1, "\033[1;36m That's it ! Have fun. \n\n", 33);
	write(1, "\033[5m PRESS ENTER TO START \n\033[0;37m", 35);
	get_next_line(0, &start);
	free(start);
}

void	init_cam(t_fdf *f)
{
	f->c->rot[0] = 0;
	f->c->rot[1] = 0;
	f->c->rot[2] = 0;
	f->c->offset.x = 0;
	f->c->offset.y = 0;
	f->c->rotMode = 2;
	f->c->iso = 1;
	f->c->scale = min(f->width / f->m->width / 2, f->height / f->m->height / 2);
	f->m->size = f->m->width * f->m->height;
}

int	init(int argc, char **argv, t_fdf *f)
{
	if (argc != 2 || !check_extension(argv[1]))
	{
		write(1, "Error: program needs a single \
argument with .fdf extension.\n", 60);
		free_and_exit(f);
	}	
	f->filename = argv[1];
	f->run = 1;
	f->m->top = 0;
	f->m->bottom = 0;
	f->mousedown = 0;
	write(1, "\033[5m", 5);
	write(1, "Parsing...", 11);
	write(1, "\033[25m", 6);
	if (parse_file(f) < 0)
	{
		write(1, "Error: parsing failed, check the .fdf file.\n", 45);
		free_and_exit(f);
	}	
	f->mlx = mlx_init();
	mlx_get_screen_size(f->mlx, &f->width, &f->height);
	display_start();
	f->win = mlx_new_window(f->mlx, f->width, f->height, "FdF");
	init_cam(f);
	return (0);
}
