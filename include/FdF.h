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
#include <math.h>
#include "point.h"
#include "vert.h"
#include "keys.h"
#include "../libft/libft.h"
#include "../linux/minilibx-linux/mlx.h"

#include "../osx/osx.h"

enum	rotMode
{
	ROT_X,
	ROT_Y,
	ROT_Z,
	ROT_ALL
};
typedef	struct s_cam
{
	t_point	offset;
	int		scale;
	double	rot[3];
	int		rotMode;
}				t_cam;

typedef	struct s_mesh
{
	int		width;
	int		height;
	int		zrange;
	int		top;
	int		bottom;
	int		size;
	t_vert	*vert;
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
	int		key[70000];
	t_mesh	*m;
	t_cam	*c;
	char 	*filename;
	
}				t_fdf;


# define COL_ONE 7348635
# define COL_TWO 8401572
# define COL_THR 9454510
# define COL_FOU 10507192
# define COL_FIV 11494337
# define COL_SIX 12481739
# define COL_SEV 13468886
# define COL_EIG 14456288
# define COL_NIN 15378155
# define COL_TEN 16300022

int	parse_file(t_fdf *f);
int	get_next_line(int fd, char **line);
float max(float val1, float val2);
float min(float val1, float val2);
int draw_mesh(t_fdf *f);
int set_point_color(int bottom, int top, int point);

int get_color(t_vert start, t_vert end, t_vert current, t_point delta);
double  percent(int start, int end, int current);

int	keyrelease(int keycode, void *param);
int	keypress(int keycode, void *param);

int    loop_hook(void *param);
void    update(t_fdf *f);
int		free_and_exit(t_fdf *f);

#endif