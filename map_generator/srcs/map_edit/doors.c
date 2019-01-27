/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 07:32:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 21:18:34 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gen_env.h"

static int		get_side_wall(t_map *map, int x, int y)
{
	int			side;

	side = 0;
	if (x > 0 && x < (map->size.x - 1) && y > 0 && y < (map->size.y - 1))
	{
		if (map->data[y][x - 1].type == ENTITY_WALL)
			side |= 0b0001;
		if (map->data[y][x + 1].type == ENTITY_WALL)
			side |= 0b0010;
		if (map->data[y - 1][x].type == ENTITY_WALL)
			side |= 0b0100;
		if (map->data[y + 1][x].type == ENTITY_WALL)
			side |= 0b1000;
	}
	return (side);
}

t_bool			door_check_neighbour(t_map *map, t_entity *ent)
{
	int			side;
	int			x;
	int			y;

	x = ent->id % MAX_SZ_X;
	y = ent->id / MAX_SZ_X;
	side = get_side_wall(map, x, y);
	if ((side & 0b0011) == 0b0011)
	{
		if ((side & 0b1100) != 0b1100)
		{
			ent->e.door->orientation = Dir_Horizontal;
			return (True);
		}
	}
	else if ((side & 0b1100) == 0b1100)
	{
		ent->e.door->orientation = Dir_Vertical;
		return (True);
	}
	return (False);
}

t_bool			door_valid_mouse_coord(t_env *env)
{
	t_ivec2		mcoord;

	mcoord = mpos_to_map_index(get_map_boundaries(env), env);
	return (mcoord.x > 0 && mcoord.x < (env->map_info.map->size.x - 1)
		&& mcoord.y > 0 && mcoord.y < (env->map_info.map->size.y - 1)
		&& !(mcoord.x == env->spawn.x && mcoord.y == env->spawn.y));
}

void			door_destroy_selected(t_env *env, t_door_edit *dedit)
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

int				door_create(t_env *env, t_door_edit *dedit)
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
