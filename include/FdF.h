/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:07:24 by abouchau          #+#    #+#             */
/*   Updated: 2021/06/13 12:10:47 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <fcntl.h>
#include "point.h"
#include "../libft/libft.h"
#include "../linux/minilibx-linux/mlx.h"

#include "../osx/osx.h"

typedef	struct s_cam
{
	float	dist;
}				t_cam;

typedef	struct s_mesh
{
	int	width;
	int	height;
	int	size;
	t_point	*vert;
}				t_mesh;

typedef	struct	s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data;
	int		bpp;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	int		run;
	t_mesh	*m;
	t_cam	*c;
	char 	*filename;
	
}				t_fdf;


int	get_next_line(int fd, char **line);
float min(float val1, float val2);
int draw_mesh(t_fdf *f);

#endif