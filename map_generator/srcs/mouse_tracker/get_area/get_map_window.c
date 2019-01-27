/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:34:26 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:48:33 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static t_bool	g_mw_painter(t_env *env)
{
	if (is_bounded(env->mouse.pos, env->grid))
	{
		env->mouse.is_editing = True;
		env->mouse.b2_cancel_b1 = True;
		clear_map(&env->map_info);
		if (env->editor.mode != Painter && env->editor.mode != World)
			env->mouse.no_trigger = True;
		return (True);
	}
	return (False);

}

static t_bool	g_mw_object_edit(t_env *env)
{
	int		obj;

	obj = get_obj_at_mpos(env);
	if (obj != -1)
	{
		env->obj.holding = True;
		env->obj.edit.selected = obj;
		env->mouse.button_index = (t_u32)obj;
		return (True);
	}
	env->obj.edit.selected = -1;
	return (False);

}

static t_bool	g_mw_door(t_env *env)
{
	t_ivec2			mpos;
	t_entity		*ent;
	t_door_edit		*dedit;

	dedit = &env->inspector.door_edit;
	if (dedit->selected && dedit->mode == Object_Select)
		return (True);
	if (door_valid_mouse_coord(env))
	{
		mpos = mpos_to_map_index(get_map_boundaries(env), env);
		ent = &env->map_info.map->data[mpos.y][mpos.x];
		return (True);
	}
	dedit->selected = NULL;
	return (False);
}

t_bool			g_area_mw(t_env *env)
{
	t_u32		type;

	type = toolset_get_type(&env->toolset);
	env->obj.holding = False;
	if (is_bounded(env->mouse.pos, env->grid))
	{
		if (env->editor.mode == Painter || env->editor.mode == World
		|| type >= Max_ToolType_Painter)
			return (g_mw_painter(env));
		else if (env->editor.mode == Object_Edit)
			return (g_mw_object_edit(env));
		else if (env->editor.mode == Door)
			return (g_mw_door(env));
	}
	return (False);
}
