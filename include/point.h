/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouchau <abouchau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 12:14:44 by abouchau          #+#    #+#             */
/*   Updated: 2021/06/13 10:19:06 by abouchau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_H
# define POINT_H

typedef struct s_dpoint
{
	double	x;
	double	y;
	double	z;
}				t_dpoint;

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}				t_point;

#endif