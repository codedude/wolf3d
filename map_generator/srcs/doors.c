/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 07:32:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/18 05:19:13 by jbulant          ###   ########.fr       */
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
	t_canvas	mbounds;

	mbounds = get_map_boundaries(env);
	mcoord = mpos_to_map_index(mbounds, env);
	return (is_bounded(env->mouse.pos, mbounds)
		&& !pos_on_spawner(env, mcoord));
}

void		door_destroy_selected(t_door_edit *dedit)
{
	t_door	*prev;
	t_door	*next;

	if (dedit->selected == dedit->list)
		dedit->list = dedit->list->next;
	prev = dedit->selected->prev;
	next = dedit->selected->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	free(dedit->selected);
	dedit->selected = NULL;
}

static void	door_add(t_door_edit *dedit, t_door *door)
{
	t_door	*next;

	next = dedit->list;
	if (next)
	{
		door->next = next;
		next->prev = door;
	}
	dedit->list = door;
	dedit->selected = door;
	dedit->count--;
}

int			door_create(t_env *env, t_door_edit *dedit)
{
	t_door		*door;

	if (!(door = (t_door*)malloc(sizeof(*door))))
		return (ERROR);
	door->next = NULL;
	door->prev = NULL;
	door->tex_id[Door_Tex] = env->rpan.p[Texture_Panel]->cursor;
	door->tex_id[Side_Tex] = door->tex_id[Door_Tex];
	door->pos = dedit->door_pos;
	door->direction = Dir_Horizontal;
	door_add(dedit, door);
	dedit->count++;
	return (SUCCESS);
}
