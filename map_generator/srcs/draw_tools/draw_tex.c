/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:06:03 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:37:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "sdl_m.h"
#include "sdl_plus.h"
#include "types.h"

static t_ivec2		get_clamp_min(t_color_pick *cpick, t_canvas anchor)
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

static t_ivec2		get_clamp_max(t_color_pick *cpick, t_canvas anchor)
{
	t_ivec2 	clamp;
	t_ivec2		curr_max;
	t_ivec2		max;

	curr_max = anchor.pos + anchor.size;
	max = cpick->canvas_mask.pos + (cpick->canvas_mask.size - 2);
	if (curr_max.x > max.x)
		clamp.x = anchor.size.x - (curr_max.x - max.x);
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

static void			canvas_get_it_clamp(t_color_pick *cpick, t_ivec2 clamp[2],
						t_canvas anchor)
{
	if (cpick->use_canvas == False)
	{
		clamp[0] = IVEC2_ZERO;
		clamp[1] = anchor.size;
	}
	else
	{
		clamp[0] = get_clamp_min(cpick, anchor);
		clamp[1] = get_clamp_max(cpick, anchor);
	}
}

void				draw_tex_color(t_sdl *sdl, t_color_pick *cpick,
						t_color *tex, t_canvas anchor)
{
	t_color		c;
	t_ivec2		it;
	t_ivec2		clamp[2];

	canvas_get_it_clamp(cpick, clamp, anchor);
	it.y = clamp[0].y;
	while (it.y < clamp[1].y)
	{
		it.x = clamp[0].x;
		while (it.x < clamp[1].x)
		{
			c = tex[it.x + it.y * anchor.size.x];
			if (!cpick->use_transparency || c.rgba != cpick->ignore_c.rgba)
			{
				c = compute_color(cpick, c);
				sdl_put_pixel_safe(sdl, it + anchor.pos, c);
			}
			it.x++;
		}
		it.y++;
	}
}

void				draw_tex(t_sdl *sdl, t_color_pick *cpick,
						t_tex *tex, t_canvas anchor)
{
	t_color		c;
	t_ivec2		it;
	t_ivec2		clamp[2];

	canvas_get_it_clamp(cpick, clamp, anchor);
	it.y = clamp[0].y;
	while (it.y < clamp[1].y)
	{
		it.x = clamp[0].x;
		while (it.x < clamp[1].x)
		{
			c = tex_px_getscaled(tex, cpick->kframe, it, anchor.size);
			if (!cpick->use_transparency || c.rgba != cpick->ignore_c.rgba)
			{
				c = compute_color(cpick, c);
				sdl_put_pixel_safe(sdl, it + anchor.pos, c);
			}
			it.x++;
		}
		it.y++;
	}
}
