/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mw_painter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:42:01 by jbulant           #+#    #+#             */
/*   Updated: 2019/02/05 15:00:19 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static int		remove_wall(t_env *env, t_entity *ent)
{
	int		obj_i;

	if (ent->type != ENTITY_VOID)
	{
		if (ent == env->inspector.door_edit.selected)
			door_destroy_selected(env, &env->inspector.door_edit);
		else if (ent->type == ENTITY_DOOR)
		{
			obj_i = ent->e.door->item_id;
			if (obj_i != -1)
				env->obj.list[obj_i]->unlock_door = NULL;
		}
		entity_destroy(ent, True);
		return (1);
	}
	return (0);
}

static void		mw_update_map(t_env *env, t_map *map, int **mask, t_ivec2 i)
{
	t_entity	*ent;
	int			n;

	n = mask[i.y][i.x];
	if (n == 0)
		return ;
	ent = &map->data[i.y][i.x];
	if (n == -1)
		remove_wall(env, ent);
	else
	{
		if (ent->type == ENTITY_VOID)
			ent->type = ENTITY_WALL;
		if (ent->tex_id + 1 != n)
			ent->tex_id = n - 1;
	}
}

void			t_mw_painter(t_env *env)
{
	t_ivec2		i;
	t_map		*map;
	t_map_info	*m_inf;

	env->mouse.is_editing = False;
	m_inf = &env->map_info;
	map = m_inf->map;
	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			mw_update_map(env, map, m_inf->tmp_data, i);
			i.x++;
		}
		i.y++;
	}
}
