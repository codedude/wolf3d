/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:19:00 by vparis            #+#    #+#             */
/*   Updated: 2019/01/09 16:34:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"
#include "types.h"
#include "entity.h"

t_entity	*entity_new(int tex_id, int crossable, int id)
{
	t_entity	*tmp;

	if ((tmp = (t_entity *)malloc(sizeof(t_entity))) == NULL)
		return (NULL);
	tmp->tex_id = tex_id;
	tmp->id = id;
	tmp->crossable = crossable;
	return (tmp);
}

t_brick		*entity_new_brick(int max_hp)
{
	t_brick	*tmp;

	if ((tmp = (t_brick *)malloc(sizeof(t_brick))) == NULL)
		return (NULL);
	tmp->max_hp = max_hp;
	tmp->current_hp = max_hp;
	return (tmp);
}

t_door		*entity_new_door(int orientation)
{
	t_door	*tmp;

	if ((tmp = (t_door *)malloc(sizeof(t_door))) == NULL)
		return (NULL);
	tmp->orientation = orientation;
	tmp->open_offset = 1.0;
	tmp->is_open = False;
	tmp->is_active = False;
	return (tmp);
}

t_object	*entity_new_object(t_vec3 pos, t_vec3 size, int collectable)
{
	t_object	*tmp;

	if ((tmp = (t_object *)malloc(sizeof(t_object))) == NULL)
		return (NULL);
	tmp->pos = pos;
	tmp->size = size;
	tmp->collectable = collectable;
	return (tmp);
}

void		entity_merge(t_entity *entity, void *obj, t_entity_type type)
{
	entity->type = type;
	if (type == ENTITY_BRICK)
		entity->e.brick = (t_brick *)obj;
	else if (type == ENTITY_DOOR)
		entity->e.door = (t_door *)obj;
	else if (type == ENTITY_OBJECT)
		entity->e.object = (t_object *)obj;
	else
		entity->e.brick = NULL;
}
