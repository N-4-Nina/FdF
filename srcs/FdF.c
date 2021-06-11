/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:00:17 by abouchau          #+#    #+#             */
/*   Updated: 2021/06/11 13:50:28 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/FdF.h"

int	parse_line(char *line, int h, t_fdf *f)
{
	char **split;
	int	i;

	i = 0;
	split = ft_split(line, 32);
	while (split[i])
	{
		f->vertices[]
	}

}

int	get_height(int *fd, t_fdf *f)
{
	int	height;
	
	height = 0;
	while (get_next_line(*fd, &line))
	{
		height++;
		free(line);
	}
	free(line);
	close(fd);
	*fd = open(f->filename, O_RDONLY);
	return (height);
}

int	parse_file(int fd)
{
	char *line;
	int	height;

	height = get_height(&fd);
	
	while (get_next_line(fd, &line))
	{
		if (!parse_line(line))
			return(abort_parse(line, fd));
		free(line);
	}
}

int	init(int argc, char **argv, t_fdf *f)
{
	int	fd;

	if (argc != 2)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (-1);
	f->filename = argv[1];
	return (parse_file(fd, f));
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	if (argc != 2)
		return (-1);
	init(argc, argv, &fdf);
}