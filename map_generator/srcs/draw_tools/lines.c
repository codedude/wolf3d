/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:06:03 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 21:04:34 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "sdl_m.h"
#include "sdl_plus.h"
#include "types.h"

static void			br_draw_line(void *l_inf, t_ivec2 px)
{
	t_sdl 			*sdl;
	t_color_pick	*cpick;

	sdl = (t_sdl*)(((void **)l_inf)[0]);
	cpick = (t_color_pick*)(((void **)l_inf)[1]);
	sdl_put_pixel_safe(sdl, px, cpick->current);
}

void				draw_line(t_sdl *sdl, t_color_pick *cpick,
						t_ivec2 px1, t_ivec2 px2)
{
	t_bresenham		br_data;
	void			*l_inf[2];

	l_inf[0] = sdl;
	l_inf[1] = cpick;
	br_data = BRES_INIT(px1, px2, l_inf, br_draw_line);
	ft_bresenham(&br_data);
}

static t_bool		line_outofbounds(t_color_pick *cpick, t_ivec2 *from,
						int *p2, int dir)
{
	int		opposite;
	int		min;
	int		max;
	t_ivec2	test;

	if (cpick->use_canvas == False)
		return (False);
	opposite = dir == 0 ? 1 : 0;
	test = *from;
	min = cpick->canvas_mask.pos[opposite];
	max = min + cpick->canvas_mask.size[opposite];
	if (test[opposite] < min || test[opposite] > max)
		return (False);
	min = cpick->canvas_mask.pos[dir];
	max = min + cpick->canvas_mask.size[dir];
	test[dir] = clamp_int(test[dir], min, max);
	*p2 = clamp_int(*p2, min, max);
	*from = test;
	return (test[dir] == *p2);
}

void				draw_hline(t_sdl *sdl, t_color_pick *cpick,
						t_ivec2 from, int x2)
{
	int		tmp;

	if (x2 < from.x)
	{
		tmp = x2;
		x2 = from.x;
		from.x = tmp;
	}
	if (line_outofbounds(cpick, &from, &x2, 0) == True)
		return ;
	while (from.x <= x2)
	{
		sdl_put_pixel_safe(sdl, from, cpick->current);
		from.x++;
	}
}

void				draw_vline(t_sdl *sdl, t_color_pick *cpick,
						t_ivec2 from, int y2)
{
	int		tmp;

	if (y2 < from.y)
	{
		tmp = y2;
		y2 = from.y;
		from.y = tmp;
	}
	if (line_outofbounds(cpick, &from, &y2, 0) == True)
		return ;
	while (from.y <= y2)
	{
		sdl_put_pixel_safe(sdl, from, cpick->current);
		from.y++;
	}
}
