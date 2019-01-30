/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 21:31:37 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:32:44 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "sdl_plus.h"

void			sdl_draw_rect(t_sdl *sdl, t_color_pick *cpick,
					t_canvas rect, int line_h)
{
	t_ivec2		from;
	int			xy;
	int			i;

	i = 0;
	while (i < line_h)
	{
		from = rect.pos - i;
		xy = rect.pos.y + rect.size.y + i;
		draw_vline(sdl, cpick, from, xy);
		from.x = rect.pos.x + rect.size.x + i;
		draw_vline(sdl, cpick, from, xy);
		from = rect.pos - i;
		xy = rect.pos.x + rect.size.x + i;
		draw_hline(sdl, cpick, from, xy);
		from.y = rect.pos.y + rect.size.y + i;
		draw_hline(sdl, cpick, from, xy);
		i++;
	}
}

void			sdl_draw_circle(t_sdl *sdl, t_ivec2 pos, t_float radius,
					t_u32 color)
{
	int			i;
	t_ivec2		px;

	i = 0;
	while (i <= 360 * radius)
	{
		px = pos;
		px.x += (int)(sin((t_float)i) * radius);
		px.y += (int)(cos((t_float)i) * radius);
		sdl_put_pixel_safe(sdl, px, (t_color)color);
		i++;
	}
}
