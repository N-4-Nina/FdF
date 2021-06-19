#ifndef VERT_H
# define VERT_H

# include    "point.h"

typedef struct s_vert
{
	t_point	p;
	int		hascolor;
	int		color;
}				t_vert;

#endif