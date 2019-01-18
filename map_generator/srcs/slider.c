/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slider.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 01:30:31 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/18 05:24:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gen_env.h"
#include "libft.h"

static t_color	*create_button_tex(t_tex *tex, t_ivec2 size, t_u32 c)
{
	t_color		*btex;
	t_ivec2		i;

	if (tex)
		return (new_texdata(tex, size));
	if (!(btex = (t_color*)malloc(sizeof(t_color) * (size_t)(size.x * size.y))))
		return (NULL);
	i.y = 0;
	while (i.y < size.y)
	{
		i.x = 0;
		while (i.x < size.x)
		{
			btex[i.x + i.y * size.x].rgba = c;
			i.x++;
		}
		i.y++;
	}
	return (btex);
}

t_slider		*slider_new(t_ivec2 pos, t_tex *imgs[2],
						t_ivec2 img_size[2])
{
	t_slider	*slider;
	int			err;

	if (!(slider = (t_slider*)ft_memalloc(sizeof(t_slider))))
		return (NULL);
	err = !(slider->slid_img = create_button_tex(imgs[0], img_size[0], 0x542dd2));
	err |= !(slider->curs_img = create_button_tex(imgs[1], img_size[1], 0xd2542d));
	slider->slid_img_size = img_size[0];
	slider->curs_img_size = img_size[1];
	slider->pos = pos;
	if (err)
		slider_destroy(&slider);
	return (slider);
}

void			slider_setup(t_slider *slider,
						int direction, t_vec2 range, t_float step)
{
	slider->direction = direction;
	slider->range = range.y - range.x;
	if (direction == Dir_Horizontal)
		slider->size = slider->slid_img_size.x;
	else
		slider->size = slider->slid_img_size.y;
	if (step == 0.0)
		slider->step = (range.y - range.x) / (t_float)slider->size;
	else
		slider->step = (range.y - range.x) / step;
	slider->min_val = range.x;
	slider->max_val = range.y;
	slider->val = slider->min_val;
}

void			slider_draw(t_env *env, t_slider *slider)
{
	t_canvas	anch;
	int			stepped;

	anch.pos = slider->pos;
	anch.size = slider->slid_img_size;
	draw_tex_color(env, slider->slid_img, False, anch);
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
	draw_tex_color(env, slider->curs_img, False, anch);
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

void			slider_destroy(t_slider **slider)
{
	if (*slider)
	{
		free((*slider)->slid_img);
		free((*slider)->curs_img);
	}
	free(*slider);
	*slider = NULL;
}
