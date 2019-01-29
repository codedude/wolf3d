/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig_map_window.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:42:05 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 19:39:07 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void		t_mw_object_edit(t_env *env)
{
	if (env->obj.holding == True
		&& !is_bounded(env->mouse.pos, get_map_boundaries(env)))
		object_destroy(&env->obj, env->mouse.button_index);
}

static void		t_mw_door_obj(t_env *env, t_door_edit *dedit)
{
	t_entity	*ent;
	int			id;

	ent = dedit->selected;
	if (ent == NULL)
		return ;
	if (ent->e.door->item_id != -1)
		env->obj.list[ent->e.door->item_id]->unlock_door = NULL;
	ent->e.door->item_id = get_obj_at_mpos(env);
	id = ent->e.door->item_id;
	if (id != -1)
		env->obj.list[id]->unlock_door = ent;
	dedit->mode = Door_Select;
}

static void		t_mw_door(t_env *env)
{
	t_door_edit	*dedit;
	t_entity	*ent;
	t_ivec2		pos;

	dedit = &env->inspector.door_edit;
	if (dedit->mode == Object_Select)
		return (t_mw_door_obj(env, dedit));
	pos = mpos_to_map_index(get_map_boundaries(env), env);
	dedit->door_pos = pos;
	if (door_valid_mouse_coord(env))
	{
		ent = &env->map_info.map->data[pos.y][pos.x];
		if (ent->type == ENTITY_DOOR)
			dedit->selected = ent;
		else if (dedit->selected != NULL)
			dedit->selected = NULL;
		else
			door_create(env, dedit);
	}
	else
		dedit->selected = NULL;
}

void			t_area_mw(t_env *env)
{
	if (env->editor.mode == Painter || env->editor.mode == World)
		t_mw_painter(env);
	else if (env->editor.mode == Object_Edit)
		t_mw_object_edit(env);
	else if (env->editor.mode == Door)
		t_mw_door(env);
}
