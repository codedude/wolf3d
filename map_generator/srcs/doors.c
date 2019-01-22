/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 07:32:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/21 23:23:23 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gen_env.h"

static t_bool	pos_on_spawner(t_env *env, t_ivec2 pos)
{
	return ((pos.x == env->spawn.x && pos.y == env->spawn.y));
}

t_bool		door_valid_mouse_coord(t_env *env)
{
	t_ivec2		mcoord;

	mcoord = mpos_to_map_index(get_map_boundaries(env), env);
	return (mcoord.x > 0 && mcoord.x < (env->map_info.map->size.x - 1)
		&& mcoord.y > 0 && mcoord.y < (env->map_info.map->size.y - 1)
		&& !pos_on_spawner(env, mcoord));
}

void		door_destroy_selected(t_env *env, t_door_edit *dedit)
{
	t_entity	*ent;
	int			obj_i;

	ent = dedit->selected;
	if (ent == NULL)
		return ;
	obj_i = ent->e.door->item_id;
	if (obj_i != -1)
		env->obj.list[obj_i]->unlock_door = NULL;
	entity_destroy(ent, True);
	dedit->mode = Door_Select;
	dedit->selected = NULL;
}

int			door_create(t_env *env, t_door_edit *dedit)
{
	t_entity	*ent;
	t_door		*door;

	ent = &env->map_info.map->data[dedit->door_pos.y][dedit->door_pos.x];
	if (ent->type != ENTITY_DOOR)
	{
		door = entity_new_door(Dir_Horizontal,
				(int)env->rpan.p[Texture_Panel]->cursor);
		if (door == NULL)
			return (ERROR);
		if (ent->type == ENTITY_VOID)
			ent->tex_id = door->tex_wall_id;
		ent->e.door = door;
		ent->type = ENTITY_DOOR;
	}
	dedit->selected = ent;
	return (SUCCESS);
}
