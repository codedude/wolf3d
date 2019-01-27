/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upd_map_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:19:19 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:51:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void		u_mw_object_edit(t_env *env)
{
	t_vec2		coords;
	t_canvas	bounds;

	if (env->obj.holding == True)
	{
		bounds = get_map_boundaries(env);
		coords = mpos_to_map_coord(bounds, env->mouse.pos, env)
			+ env->mouse.obj_offset;
		if (env->obj.g_snap->val != 0.0 && is_bounded(env->mouse.pos, bounds))
			coords = vec_snap(coords + 0.5, env->obj.g_snap->val) - 0.5;
		env->obj.list[env->mouse.button_index]->pos = coords;
	}
}

static void		u_mw_door(t_env *env)
{
	t_door_edit	*dedit;

	dedit = &env->inspector.door_edit;
	dedit->door_pos = mpos_to_map_index(get_map_boundaries(env), env);
}

void			u_area_mw(t_env *env)
{
	t_u32		type;

	type = toolset_get_type(&env->toolset);
	if (type >= Max_ToolType_Painter
	|| env->editor.mode == Painter || env->editor.mode == World)
		toolset_use_fx(env);
	else if (env->editor.mode == Object_Edit)
		u_mw_object_edit(env);
	else if (env->editor.mode == Door)
		u_mw_door(env);
}
