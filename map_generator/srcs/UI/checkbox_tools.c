/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:23:16 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 04:24:32 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_plus.h"
#include "sdl_m.h"
#include "ui.h"
#include "ft_type.h"
#include "types.h"

t_bool			checkbox_hover(t_checkbox *cbox, t_ivec2 pos)
{
	return (is_bounded(pos, cbox->anchor));
}

static void		draw_cross(t_sdl *sdl, t_color_pick *cpick, t_checkbox *cbox)
{
	t_ivec2		px1;
	t_ivec2		px2;

	px1 = cbox->anchor.pos + 1;
	px2 = px1 + cbox->anchor.size - 2;
	draw_line(sdl, cpick, px1, px2);
	px1.x++;
	px2.y--;
	draw_line(sdl, cpick, px1, px2);
	px1.x--;
	px1.y++;
	px2.y++;
	px2.x--;
	draw_line(sdl, cpick, px1, px2);
	px2.x = cbox->anchor.pos.x;
	px1.x = px2.x + (cbox->anchor.size.x - 2);
	px1.y = cbox->anchor.pos.y + 1;
	px2.y = px1.y + cbox->anchor.size.y - 2;
	draw_line(sdl, cpick, px1, px2);
	px1.y++;
	px2.x++;
	draw_line(sdl, cpick, px1, px2);
	px1 -= 1;
	px2 -= 1;
	draw_line(sdl, cpick, px1, px2);
}

void			checkbox_clic(t_checkbox *cbox)
{
	cbox->reverse_state(cbox->param);
}

void			checkbox_draw(t_sdl *sdl, t_color_pick *cpick, t_checkbox *cbox)
{
	int		state;

	state = cbox->get_state(cbox->param);
	if (state == Unavailable)
	{
		cpick_set_color_mask(cpick, 0x0, 0.75);
		draw_tex_color(sdl, cpick, cbox->tex, cbox->anchor);
		cpick_unset_color_mask(cpick);
	}
	else
		draw_tex_color(sdl, cpick, cbox->tex, cbox->anchor);
	if (state == Check)
	{
		cpick_set_color(cpick, 0x333333);
		draw_cross(sdl, cpick, cbox);
	}
}
