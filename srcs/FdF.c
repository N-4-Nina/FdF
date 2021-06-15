/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:00:17 by abouchau          #+#    #+#             */
/*   Updated: 2021/06/13 12:24:25 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"
#include <stdio.h>

int	parse_line(char *line, t_fdf *f)
{
	char **split;
	int	i;
	static	int	lineNb = 0;

	i = 0;
	split = ft_split(line, 32);
	if (!lineNb)
	{
		while (split[i])
			i++;
		f->m->width = i;
		f->m->vert = malloc(sizeof(t_point) * i * f->m->height);
		i = 0;
	}
	
	while(split[i])
	{
		f->m->vert[i+(lineNb*f->m->width)] = (t_point){ i, lineNb, ft_atoi(split[i])};
		i++;
	}
	free(split);
	lineNb++;
	return (lineNb);
}

int	get_height(t_fdf *f)
{
	int		height;
	int		fd;
	char	*line;
	
	height = 0;
	line = NULL;
	fd = open(f->filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	while (get_next_line(fd, &line))
	{
		height++;
		free(line);
	}
	free(line);
	close(fd);
	
	return (height);
}

int	abort_parse(char *line, int fd, t_fdf *f)
{
	int	i;

	i = 0;
	free(line);
	close(fd);
	free(f->m->vert);
	return (-1);
}

int	parse_file(t_fdf *f)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(f->filename, O_RDONLY);
	if (fd < 0)
		return (-1);
	f->m->height = get_height(f);
	while (get_next_line(fd, &line))
	{
		// printf("%s\n", line);
		if (!parse_line(line, f))
			return(abort_parse(line, fd, f));
		free(line);
	}
	return (0);
}

int	init(int argc, char **argv, t_fdf *f)
{
	if (argc != 2)
		return (-1);
	f->mlx = mlx_init();
	mlx_get_screen_size(f->mlx, &f->width, &f->height);
	f->width /= 1.25;
	f->height /= 1.25;
	f->win = mlx_new_window(f->mlx, f->width, f->height, "FdF");
	f->filename = argv[1];
	if (parse_file(f)< 0)
		return (-1);
	f->m->size = f->m->width * f->m->height;
	f->c->dist = min(f->width / f->m->width / 2, f->height/ f->m->height /2);
	f->img = mlx_new_image(f->mlx, f->width, f->height);
	f->data = (char *)mlx_get_data_addr(f->img, &f->bpp, &f->size_line, &f->endian);
	return (0);
}

int	alloc(t_fdf *f)
{
	f->c = malloc(sizeof(t_cam));
	f->m = malloc(sizeof(t_mesh));
	return (0);
}

void print_vert(t_fdf fdf)
{
	int i = 0;
	while (i < fdf.m->height*fdf.m->width)
	{
		printf("%d %d %d \n", fdf.m->vert[i].x, fdf.m->vert[i].y, fdf.m->vert[i].z);
		i++;
	}
}

// int	loop(t_fdf *f)
// {
// 	while (f->run)
// 	{
// 		// update();
// 		f->img = mlx_new_image(f->mlx, f->width, f->height);
// 		f->data = mlx_get_data_addr(f->img, &f->bpp, &f->size_line, &f->endian);
// 		draw_mesh(f);
// 		mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
// 		mlx_clear_window(f->mlx, f->win);
// 		mlx_destroy_image(f->mlx, f->img);
// 	}
// 	return (0);
// }

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	
	alloc(&fdf);
	if (init(argc, argv, &fdf))
		return (-1);
	

	draw_mesh(&fdf);
	mlx_put_image_to_window(fdf.mlx, fdf.win, fdf.img, 0, 0);
	while (1)
		NULL;
	// mlx_loop_hook(fdf.mlx, &loop, &fdf);
	// mlx_loop(fdf.mlx);
}