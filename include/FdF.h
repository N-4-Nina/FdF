/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FdF.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:07:24 by abouchau          #+#    #+#             */
/*   Updated: 2021/06/11 13:06:09 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include <unistd.h>
#include <fcntl.h>
#include "point.h"
#include "../libft/libft.h"

typedef	struct	s_fdf
{
	t_point	**vertices;
	char 	*filename;
	int		height;
	int		width;
}				t_fdf;


int	get_next_line(int fd, char **line);

#endif