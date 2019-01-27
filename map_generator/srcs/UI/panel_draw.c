/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:27:48 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:37:52 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "sdl_m.h"

static void		draw_panel_slide(t_sdl *sdl, t_panel *pan)
{
	t_canvas	slide_box;
	t_canvas	slider;
	t_canvas	canvas_msk;
	t_u32		slider_size;

	slider_size = pan->view_max - pan->view_min;
	if (slider_size >= pan->nb_elem)
		return ;
	canvas_msk = CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO);
	slide_box = pan->anchor;
	slide_box.pos.x += slide_box.size.x;
	slide_box.size.x = ipercent_of(sdl->width, 1);
	slider = slide_box;
	slider.size.y = (int)(slider_size / (t_float)pan->nb_elem
			* (t_float)slide_box.size.y);
	slider.pos.y += (int)(pan->view_min / (t_float)pan->nb_elem
			* (t_float)slide_box.size.y);
	draw_canvas_fill(sdl, &slide_box, &canvas_msk, 0x121212);
	draw_canvas_fill(sdl, &slider, &canvas_msk, 0x323232);
	if (pan->draw_border == False)
		return ;
	draw_canvas_border(sdl, slider, canvas_msk, 0x0);
	draw_canvas_border(sdl, slide_box, canvas_msk, 0x888888);
}

static void		draw_panel_elems(t_sdl *sdl, t_color_pick *cpick, t_panel *pan)
{
	t_canvas	e_anch;
	t_u32		i;

	i = 0;
	while (i < pan->view_max)
	{
		e_anch = panel_get_elem_anchor(pan, (int)(i - pan->view_min));
		e_anch.pos += pan->anchor.pos;
		if (pan->hightlight && i != pan->cursor)
		{
			cpick_set_color_mask(cpick, 0x0, 0.75);
			draw_tex(sdl, cpick, &pan->tex[i], e_anch);
			cpick_unset_color_mask(cpick);
		}
		else
		{
			draw_tex(sdl, cpick, &pan->tex[i], e_anch);
			draw_canvas_border(sdl, e_anch, pan->anchor, pan->border_col.rgba);
		}
		i++;
	}
}

void			panel_draw(t_sdl *sdl, t_color_pick *cpick, t_panel *pan)
{
	if (pan->draw_bg)
		draw_canvas_fill(sdl, &pan->anchor,
			&CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), pan->bg_col.rgba);
	if (pan->draw_border)
		draw_canvas_border(sdl, pan->anchor,
			CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), pan->border_col.rgba);
	cpick_set_canvas(cpick, pan->anchor);
	draw_panel_elems(sdl, cpick, pan);
	draw_panel_slide(sdl, pan);
	cpick_unset_canvas(cpick);
}
