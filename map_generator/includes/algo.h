/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:02:08 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/22 21:36:34 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ALGO_H
# define ALGO_H

# include "types.h"

typedef struct	s_ud_line {
	t_ivec2		point;
	int			len;
	int			dir;
	void		*param;
	void		(*call)(void*, t_ivec2);
}				t_ud_line;

# define	UD_LINE_HORIZONTAL	0
# define	UD_LINE_VERTICAL	1

typedef struct	s_bresenham {
	t_ivec2		v1;
	t_ivec2		v2;
	void		*param;
	void		(*call)(void*, t_ivec2);
}				t_bresenham;

typedef struct	s_circle {
	t_ivec2		pos;
	t_float 	radius;
	void		*param;
	void		(*call)(void*, t_ivec2);
}				t_circle;

typedef struct	s_flood_d {
	int			(*condition)(struct s_flood_d *, t_ivec2);
	void		(*action)(struct s_flood_d *, t_ivec2);
	void		*param;
}				t_flood_d;

# define UDL_INIT(x, y, z, w, v)	(t_ud_line){(x), (y), (z), (w), (v)}
# define BRES_INIT(x, y, z, w)		(t_bresenham){(x), (y), (z), (w)}
# define CIRCLE_INIT(x, y, z, w)	(t_circle){(x), (y), (z), (w)}
# define FLOOD_D_INIT(x, y, z)		(t_flood_d){(x), (y), (z)}

void			ft_circle(t_circle *data);
void			ft_unidir_line(t_ud_line *data);
void			ft_bresenham(t_bresenham *data);
void			ft_flood(t_flood_d *f_data, t_ivec2 px);

#endif
