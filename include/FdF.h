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

# include	<unistd.h>
# include	<fcntl.h>
# include	<math.h>
# include	<limits.h>
# include	"gradient.h"
# include	"point.h"
# include	"vert.h"
# include	"keys.h"
# include	"../libft/libft.h"
# include	"../linux/minilibx-linux/mlx.h"

enum	e_rotMode
{
	ROT_X,
	ROT_Y,
	ROT_Z,
	ROT_ALL
};

typedef struct s_linedraw
{
	t_point	d;
	t_point	s;
	t_vert	current;
	int		er[2];
}				t_linedraw;

typedef struct s_cam
{
	t_point		offset;
	double		rot[3];
	int			scale;
	int			iso;
	int			rotMode;
}				t_cam;

typedef struct s_mesh
{
	int		width;
	int		height;
	int		zrange;
	int		top;
	int		bottom;
	int		size;
	t_vert	*vert;
}				t_mesh;

typedef struct s_fdf
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
	int		mousedown;
	t_mesh	*m;
	t_cam	*c;
	t_point	cursor;
	t_point	offset;
	char	*filename;
}				t_fdf;

# define COS_ISO 0.86602529158
# define SIN_ISO 0.50000019433

int		init(int argc, char **argv, t_fdf *f);
int		parse_file(t_fdf *f);
int		get_next_line(int fd, char **line);
float	max(float val1, float val2);
float	min(float val1, float val2);
int		hextoint(char *s);
void	free_split(char **split);
int		check_extension(char *s);
void	check_rectangle(char **split, t_fdf *f);

int		draw_mesh(t_fdf *f);
t_point	project(t_point p, t_fdf *f);
void	iso(t_point *p);
void	rotate_x(t_vert *v, t_cam *c);
void	rotate_y(t_vert *v, t_cam *c);
void	rotate_z(t_vert *v, t_cam *c);

void	set_point_color(int index, int z, char *str, t_fdf *f);
int		set_default_color(int bottom, int top, int point);

int		get_color(t_vert start, t_vert end, t_vert current, t_point delta);
double	percent(int start, int end, int current);

int		keyrelease(int keycode, void *param);
int		keypress(int keycode, void *param);
int		mousepress(int button, int x, int y, void *param);
int		mouserelease(int button, int x, int y, void *param);
int		mousemotion(int x, int y, void *param);

int		scale_up(int x, int y, t_fdf *f);
int		scale_down(t_fdf *f);
int		left_arrow(t_fdf *f);
int		right_arrow(t_fdf *f);

int		loop_hook(void *param);
void	update(t_fdf *f);
int		abort_parse(char *line, int fd, t_fdf *f);
int		free_and_exit(t_fdf *f);

#endif