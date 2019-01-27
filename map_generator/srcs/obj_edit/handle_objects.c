/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_objects.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 01:22:45 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:22:45 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void			add_new_object(t_objects_tools *otools, t_vec2 pos,
						t_bool is_solid, t_u32 id)
{
	t_object_e	*obj;

	if (otools->count == MAX_OBJECTS)
		return ;
	obj = (t_object_e*)malloc(sizeof(*obj));
	if (!obj)
		return ;
	obj->pos = pos;
	obj->is_solid = is_solid;
	obj->unlock_door = NULL;
	obj->scale = 1.0;
	obj->id = id;
	obj->y_pos = 0.0;
	otools->list[otools->count++] = obj;
}

void			object_destroy(t_objects_tools *otools, t_u32 obj_i)
{
	t_entity	*ent;

	if (obj_i >= otools->count)
		return ;
	ent = otools->list[obj_i]->unlock_door;
	if (ent != NULL)
		ent->e.door->item_id = -1;
	free(otools->list[obj_i]);
	if (otools->count > 1)
		otools->list[obj_i] = otools->list[otools->count - 1];
	if ((int)obj_i == otools->edit.selected)
		otools->edit.selected = -1;
	otools->count--;
}
