/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 01:30:31 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 04:05:25 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gen_env.h"
#include "libft.h"

void			slider_draw(t_sdl *sdl, t_color_pick *cpick, t_slider *slider)
{
	t_canvas	anch;
	int			stepped;

	anch.pos = slider->pos;
	anch.size = slider->slid_img_size;
	cpick_set_transparency(cpick, 0x0);
	if (slider->draw_bar == True)
		draw_tex_color(sdl, cpick, slider->slid_img, anch);
	anch.size = slider->curs_img_size;
	stepped = (int)((slider->val - slider->min_val)
				/ slider->range * (t_float)slider->size);
	if (slider->direction == Dir_Horizontal)
	{
		anch.pos.x += stepped - anch.size.x / 2;
		anch.pos.y -= (anch.size.y - slider->slid_img_size.y) / 2;
	}
	else
	{
		anch.pos.y += stepped - anch.size.y / 2;
		anch.pos.x -= (anch.size.x - slider->slid_img_size.x) / 2;
	}
	draw_tex_color(sdl, cpick, slider->curs_img, anch);
	cpick_unset_transparency(cpick);
}

t_bool			slider_hover(t_slider *slider, t_ivec2 pos)
{
	t_canvas	anch;

	anch.size = slider->slid_img_size;
	anch.pos = slider->pos;
	if (slider->direction == Dir_Horizontal)
	{
		anch.size.y = slider->curs_img_size.y;
		anch.pos.y -= (slider->curs_img_size.y - slider->slid_img_size.y) / 2;
	}
	else
	{
		anch.size.x = slider->curs_img_size.x;
		anch.pos.x -= (slider->curs_img_size.x - slider->slid_img_size.x) / 2;
	}
	return (is_bounded(pos, anch));
}

void			slider_update_bypos(t_slider *slider, t_ivec2 pos)
{
	int			tmp;
	t_float		diff;

	if (slider->direction == Dir_Horizontal)
	{
		tmp = pos.x - slider->pos.x;
		tmp = clamp_int(tmp, 0, slider->slid_img_size.x);
		diff = tmp / (t_float)slider->slid_img_size.x;
	}
	else
	{
		tmp = pos.y - slider->pos.y;
		tmp = clamp_int(tmp, 0, slider->slid_img_size.y);
		diff = tmp / (t_float)slider->slid_img_size.y;
	}
	slider->val = snap_f(diff * slider->range, slider->step) + slider->min_val;
}
