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

int	get_height(int *fd, t_fdf *f)
{
	int	height;
	char	*line;
	
	height = 0;
	while (get_next_line(*fd, &line))
	{
		height++;
		free(line);
	}
	free(line);
	close(*fd);
	*fd = open(f->filename, O_RDONLY);
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

int	parse_file(int fd, t_fdf *f)
{
	char	*line;

	f->m->height = get_height(&fd, f);
	while (get_next_line(fd, &line))
	{
		if (!parse_line(line, f))
			return(abort_parse(line, fd, f));
		free(line);
	}
	return (0);
}

int	init(int argc, char **argv, t_fdf *f)
{
	int	fd;

	if (argc != 2)
		return (-1);
	f->mlx = mlx_init();
	mlx_get_screen_size(f->mlx, &f->width, &f->height);
	f->win = mlx_new_window(f->mlx, f->width, f->height, "FdF");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	f->filename = argv[1];
	return (parse_file(fd, f));
}

int	alloc(t_fdf *f)
{
	f->c = malloc(sizeof(t_cam));
	f->m = malloc(sizeof(t_mesh));
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	
	alloc(&fdf);
	if (init(argc, argv, &fdf))
		return (-1);
	printf("%d%d\n", WIDTH, HEIGHT);
	while (1)
		NULL;
}