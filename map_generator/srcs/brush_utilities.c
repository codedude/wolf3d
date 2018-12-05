/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brush_utilities.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/05 17:33:11 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static t_bool	is_visible_brush(t_env *env, t_tex_pbox **found)
{
	t_tex_pbox	*box;
	int			y;

	box = env->brush_box;
	while (box && box->tex_id != env->brush)
		box = box->next;
	*found = box;
	y = box->canvas.pos.y - env->brush_c_offset;
	if (y > env->brush_canvas.pos.y && y + box->canvas.size.y
						< env->brush_canvas.pos.y + env->brush_canvas.size.y)
		return (True);
	return (False);
}

static int		get_new_brush_c_offset(t_env *env, t_tex_pbox *box)
{
	int		elem_shown;
	t_float	offset;

	offset = (t_float)box->canvas.size.y * 1.5;
	elem_shown = (int)((t_float)env->brush_canvas.size.y / offset);
	if (box->canvas.pos.y + box->canvas.size.y
		>= env->brush_canvas.pos.y + env->brush_canvas.size.y)
		return ((int)((t_float)((box->tex_id + 1) - elem_shown) * offset));
	return ((int)((t_float)(box->tex_id) * offset));
}

void			update_c_offset(t_env *env)
{
	t_tex_pbox	*box;

	if (is_visible_brush(env, &box))
		return ;
	if (box == env->brush_box)
		env->brush_c_offset = env->max_bcoffset;
	else if (box->tex_id == 0)
		env->brush_c_offset = 0;
	else
		env->brush_c_offset = get_new_brush_c_offset(env, box);
}

void			switch_brush(t_ivec2 mpos, t_env *env)
{
	t_tex_pbox		*box;
	t_canvas		canvas;

	box = env->brush_box;
	canvas.size = box->canvas.size;
	canvas.pos.x = box->canvas.pos.x;
	while (box)
	{
		canvas.pos.y = box->canvas.pos.y - env->brush_c_offset;
		if (is_bounded(mpos, canvas))
		{
			env->brush = box->tex_id;
			break ;
		}
		box = box->next;
	}
}
