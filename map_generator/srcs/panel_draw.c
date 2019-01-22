/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_draw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:27:48 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/22 02:29:23 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "sdl_m.h"

t_bool			draw_px(t_color_pick *cpick, t_color c)
{
	return (!cpick->use_transparency || c.rgba != cpick->ignore_c.rgba);
}

void			draw_tex_color(t_env *env, t_color *tex, t_bool shade,
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

t_color			tex_px_getscaled(t_tex *tex, int kframe, t_ivec2 from, t_ivec2 scale)
{
	t_color		c;
	t_color		c_ret;
	int			convert;

	convert = tex->w * from.x / scale.x + tex->h * from.y / scale.y * tex->w;
	c.rgba = tex->pixels[kframe % tex->n_sprites][convert];
	c_ret.c.r = c.c.b;
	c_ret.c.g = c.c.g;
	c_ret.c.b = c.c.r;
	c_ret.c.a = c.c.a;
	return (c_ret);
}

t_ivec2			get_clamp_min(t_env *env, t_color_pick *cpick, t_canvas anchor)
{
	t_ivec2 	clamp;

	clamp.x = (cpick->canvas_mask.pos.x + 1) - anchor.pos.x;
	if (clamp.x < 0)
		clamp.x = 0;
	clamp.y = (cpick->canvas_mask.pos.y + 1) - anchor.pos.y;
	if (clamp.y < 0)
		clamp.y = 0;
	return (clamp);
}

t_ivec2			get_clamp_max(t_env *env, t_color_pick *cpick, t_canvas anchor)
{
	t_ivec2 	clamp;
	t_ivec2		curr_max;
	t_ivec2		max;

	curr_max = anchor.pos + anchor.size;
	max = cpick->canvas_mask.pos + (cpick->canvas_mask.size - 2);
	if (curr_max.x > max.x)
		clamp.x = (cpick->canvas_mask.size.x - 2);
	else if (cpick->canvas_mask.pos.x > curr_max.x)
		clamp.x = -1;
	else
		clamp.x = anchor.size.x;
	if (curr_max.y > max.y)
		clamp.y = anchor.size.y - (curr_max.y - max.y);
	else if (cpick->canvas_mask.pos.y > curr_max.y)
		clamp.y = -1;
	else
		clamp.y = anchor.size.y;
	return (clamp);
}

void			canvas_get_it_clamp(t_env *env, t_ivec2 clamp[2],
					t_canvas anchor)
{
	t_color_pick	*cpick;

	cpick = &env->cpick;
	if (cpick->use_canvas == False)
	{
		clamp[0] = IVEC2_ZERO;
		clamp[1] = anchor.size;
		return ;
	}
	clamp[0] = get_clamp_min(env, cpick, anchor);
	clamp[1] = get_clamp_max(env, cpick, anchor);
}

void			draw_tex(t_env *env, t_tex *tex, t_bool shade,
						t_canvas anchor)
{
	t_sdl		*sdl;
	t_color		c;
	t_ivec2		it;
	t_ivec2		clamp[2];

	sdl = &env->sdl;
	canvas_get_it_clamp(env, clamp, anchor);
	it.y = clamp[0].y;
	while (it.y < clamp[1].y)
	{
		it.x = clamp[0].x;
		while (it.x < clamp[1].x)
		{
			c = tex_px_getscaled(tex, env->kframe, it, anchor.size);
			if (draw_px(&env->cpick, c))
			{
				if (shade == True)
					c.rgba = (c.rgba >> 2) & 0x3f3f3f;
				sdl_put_pixel_safe(sdl, it + anchor.pos, c);
			}
			it.x++;
		}
		it.y++;
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
	draw_canvas_fill(sdl, &slide_box, &CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), 0x121212);
	draw_canvas_fill(sdl, &slider, &CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), 0x323232);
	if (pan->draw_border == False)
		return ;
	draw_canvas_border(sdl, slider, CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), 0x0);
	draw_canvas_border(sdl, slide_box, CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), 0x888888);
}

static void		draw_panel_elems(t_env *env, t_sdl *sdl, t_panel *pan)
{
	t_canvas	e_anch;
	t_bool		shade;
	t_u32		i;

	i = 0;
	while (i < pan->view_max)
	{
		e_anch = panel_get_elem_anchor(pan, (int)(i - pan->view_min));
		e_anch.pos += pan->anchor.pos;
		shade = (pan->hightlight && i != pan->cursor);
		// draw_tex(env, pan->elem_tex[i], shade, e_anch);
		draw_tex(env, &pan->tex[i], shade, e_anch);
		if (pan->hightlight && i == pan->cursor)
			draw_canvas_border(sdl, e_anch,
				CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), pan->border_col.rgba);
		i++;
	}
}

void			panel_draw(t_env *env, t_sdl *sdl, t_panel *pan)
{
	if (pan->draw_bg)
		draw_canvas_fill(sdl, &pan->anchor,
			&CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), pan->bg_col.rgba);
	if (pan->draw_border)
		draw_canvas_border(sdl, pan->anchor, CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO),
			pan->border_col.rgba);
	env_set_canvas(env, pan->anchor);
	draw_panel_elems(env, sdl, pan);
	draw_panel_slide(sdl, pan);
	env_unset_canvas(env);
}
