/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:27:48 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/29 17:42:14 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "sdl_m.h"

t_bool			draw_px(t_color_pick *cpick, t_color c)
{
	return (!cpick->use_transparency || c.rgba != cpick->ignore_c.rgba);
}

void			draw_tex(t_env *env, t_color *tex, t_bool shade,
						t_canvas anchor)
{
	t_sdl		*sdl;
	t_ivec2		i;
	t_color		c;

	sdl = &env->sdl;
	i.y = 0;
	while (i.y < anchor.size.y)
	{
		i.x = 0;
		while (i.x < anchor.size.x)
		{
			c = tex[i.x + i.y * anchor.size.x];
			if (draw_px(&env->cpick, c))
			{
				if (shade == True)
					c.rgba = (c.rgba >> 2) & 0x3f3f3f;
				sdl_put_pixel_safe(sdl, i + anchor.pos, c);
			}
			i.x++;
		}
		i.y++;
	}
}

static void		draw_panel_slide(t_sdl *sdl, t_panel *pan)
{
	t_canvas	slide_box;
	t_canvas	slider;
	t_u32		slider_size;

	slider_size = pan->view_max - pan->view_min;
	if (slider_size >= pan->nb_elem)
		return ;
	slide_box = pan->anchor;
	slide_box.pos.x += slide_box.size.x;
	slide_box.size.x = ipercent_of(sdl->width, 1);
	slider = slide_box;
	slider.size.y = (int)(slider_size / (t_float)pan->nb_elem
			* (t_float)slide_box.size.y);
	slider.pos.y += (int)(pan->view_min / (t_float)pan->nb_elem
			* (t_float)slide_box.size.y);
	draw_canvas_fill(sdl, slide_box, CANVAS_INIT(0, 0), 0x121212);
	draw_canvas_fill(sdl, slider, CANVAS_INIT(0, 0), 0x323232);
	if (pan->draw_border == False)
		return ;
	draw_canvas_border(sdl, slider, CANVAS_INIT(0, 0), 0x0);
	draw_canvas_border(sdl, slide_box, CANVAS_INIT(0, 0), 0x888888);
}

static void		draw_panel_elems(t_env *env, t_sdl *sdl, t_panel *pan)
{
	t_canvas	e_anch;
	t_u32		tmp_min;
	t_bool		shade;
	int			i;

	i = 0;
	tmp_min = pan->view_min;
	while (tmp_min < pan->view_max)
	{
		e_anch = panel_get_elem_anchor(pan, i);
		e_anch.pos += pan->anchor.pos;
		shade = (pan->hightlight && tmp_min != pan->cursor);
		draw_tex(env, pan->elem_tex[tmp_min], shade, e_anch);
		if (pan->hightlight && tmp_min == pan->cursor)
			draw_canvas_border(sdl, e_anch,
				CANVAS_INIT(0, 0), pan->border_col.rgba);
		tmp_min++;
		i++;
	}
}

void			panel_draw(t_env *env, t_sdl *sdl, t_panel *pan)
{
	if (pan->draw_bg)
		draw_canvas_fill(sdl, pan->anchor,
			CANVAS_INIT(0, 0), pan->bg_col.rgba);
	if (pan->draw_border)
		draw_canvas_border(sdl, pan->anchor, CANVAS_INIT(0, 0),
			pan->border_col.rgba);
	draw_panel_elems(env, sdl, pan);
	draw_panel_slide(sdl, pan);
}
