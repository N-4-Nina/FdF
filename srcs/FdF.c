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

int	alloc(t_fdf *f)
{
	f->c = NULL;
	f->m = NULL;
	f->mlx = NULL;
	f->win = NULL;
	f->c = malloc(sizeof(t_cam));
	if (!f->c)
		return (-1);
	f->m = malloc(sizeof(t_mesh));
	if (!f->m)
	{
		free(f->c);
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (alloc(&fdf) < -1)
		return (-1);
	if (init(argc, argv, &fdf))
		return (-1);
	mlx_hook(fdf.win, 33, (1 << 8), free_and_exit, &fdf);
	mlx_loop_hook(fdf.mlx, loop_hook, &fdf);
	mlx_hook(fdf.win, 02, (1L << 0), keypress, &fdf);
	mlx_hook(fdf.win, 04, (1L << 2), mousepress, &fdf);
	mlx_hook(fdf.win, 06, (1L << 6), mousemotion, &fdf);
	mlx_hook(fdf.win, 05, (1L << 3), mouserelease, &fdf);
	mlx_loop(fdf.mlx);
}
