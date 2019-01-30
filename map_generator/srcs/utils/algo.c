/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:05:14 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:32:14 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include "algo.h"
#include "types.h"

void			ft_bresenham(t_bresenham *data)
{
	t_ivec2 orientation;
	t_ivec2 direction;
	int		error[2];

	direction = IVEC2_INIT(abs(data->v1.x - data->v2.x),
					abs(data->v1.y - data->v2.y));
	orientation = IVEC2_INIT(((data->v1.x < data->v2.x) ? 1 : -1),
					((data->v1.y < data->v2.y) ? 1 : -1));
	error[0] = ((direction.x > direction.y) ? direction.x : -direction.y) / 2;
	while (!(data->v1.x == data->v2.x && data->v1.y == data->v2.y))
	{
		data->call(data->param, data->v1);
		error[1] = error[0];
		if (error[1] > -direction.x)
		{
			error[0] -= direction.y;
			data->v1.x += orientation.x;
		}
		if (error[1] < direction.y)
		{
			error[0] += direction.x;
			data->v1.y += orientation.y;
		}
	}
}

void			ft_unidir_line(t_ud_line *data)
{
	int			i;
	t_ivec2		local_dir;

	local_dir = 0;
	if (data->len < 0)
	{
		data->len = -data->len;
		local_dir[data->dir] = -1;
	}
	else
		local_dir[data->dir] = 1;
	i = 0;
	while (i < data->len)
	{
		data->call(data->param, data->point + (i * local_dir));
		i++;
	}
}

void			ft_flood(t_flood_d *f_data, t_ivec2 px)
{
	if (f_data->condition(f_data, px))
	{
		f_data->action(f_data, px);
		ft_flood(f_data, IVEC2_INIT(px.x - 1, px.y));
		ft_flood(f_data, IVEC2_INIT(px.x + 1, px.y));
		ft_flood(f_data, IVEC2_INIT(px.x, px.y - 1));
		ft_flood(f_data, IVEC2_INIT(px.x, px.y + 1));
	}
}

void			ft_circle(t_circle *c)
{
	int			i;
	t_ivec2		point;

	i = 0;
	while (i <= 360 * c->radius)
	{
		point = c->pos;
		point.x += (int)round(sin((t_float)i) * c->radius);
		point.y += (int)round(cos((t_float)i) * c->radius);
		c->call(c->param, point);
		i++;
	}
}
