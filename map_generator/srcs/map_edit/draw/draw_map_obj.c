/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_obj.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 01:03:07 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 21:34:27 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "map_edit.h"
#include "gen_env.h"

static t_bool		test_position(t_canvas anch, t_canvas grid)
{
	if ((anch.pos.x < grid.pos.x && anch.pos.x + anch.size.x < grid.pos.x)
	|| (anch.pos.y < grid.pos.y && anch.pos.y + anch.size.y < grid.pos.y))
		return (False);
	return (True);
}

static t_ivec2		get_prev_size(t_env *env)
{
	t_map_info	*m_inf;

	m_inf = &env->map_info;
	return (m_inf->x_draw[1] - m_inf->x_draw[0]);
}

static void			draw_single_obj(t_env *env, t_objects_tools *otools,
						t_canvas anchor, int i)
{
	t_object_e			*obj;

	obj = otools->list[i];
	anchor.pos = map_coord_to_screen(env, obj->pos);
	if (test_position(anchor, env->grid))
	{
		anchor.pos -= anchor.size / 2;
		if (env->editor.mode == Object_Edit && (int)i == env->obj.edit.selected)
			sdl_draw_rect(&env->sdl, &env->cpick, anchor, 3);
		if (obj->unlock_door != NULL)
		{
			i = anchor.size.x / 10;
			while (i--)
			{
				anchor.size -= 2;
				anchor.pos += 1;
				draw_canvas_border(&env->sdl, anchor, env->grid, 0xffff00);
			}
		}
		draw_tex(&env->sdl, &env->cpick,
			&env->sdl.tex_sprites[obj->id], anchor);
	}
}

void				draw_map_obj(t_env *env)
{
	t_u32				i;
	t_objects_tools		*otools;
	t_canvas			anchor;

	cpick_set_color(&env->cpick, 0xffffff);
	i = 0;
	otools = &env->obj;
	anchor.size = get_prev_size(env);
	while (i < otools->count)
	{
		draw_single_obj(env, otools, anchor, (int)i);
		i++;
	}
}
