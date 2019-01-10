/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:19:00 by vparis            #+#    #+#             */
/*   Updated: 2019/01/10 17:45:24 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"
#include "types.h"
#include "entity.h"

t_entity	*entity_new(int tex_id, int id, int crossable)
{
	t_entity	*tmp;

	if ((tmp = (t_entity *)malloc(sizeof(t_entity))) == NULL)
		return (NULL);
	tmp->tex_id = tex_id;
	tmp->tex_key = 0;
	tmp->id = id;
	tmp->crossable = crossable;
	tmp->type = ENTITY_NONE;
	tmp->e.brick = NULL;
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

t_object	*entity_new_object(t_vec2 pos, t_vec2 size, t_float z,
				int collectable)
{
	t_object	*tmp;

	if ((tmp = (t_object *)malloc(sizeof(t_object))) == NULL)
		return (NULL);
	tmp->pos = pos;
	tmp->z = z;
	tmp->size = size;
	tmp->collectable = collectable;
	tmp->z_buffer = 0.0;
	tmp->y_start = 0;
	tmp->y_end = 0;
	tmp->x_end = 0;
	tmp->x_start = 0;
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

void		entity_set_void(t_entity *entity)
{
	entity->tex_id = 0;
	entity->id = 0;
	entity->crossable = 1;
	entity->type = ENTITY_VOID;
	entity->e.brick = NULL;
}

void		entity_set_wall(t_entity *entity, int tex_id, int id,
				int crossable)
{
	entity_set(entity, tex_id, id, crossable);
	entity->type = ENTITY_WALL;
	entity->e.brick = NULL;
}

void		entity_set(t_entity *entity, int tex_id, int id,
				int crossable)
{
	entity->tex_id = tex_id;
	entity->tex_key = 0;
	entity->id = id;
	entity->crossable = crossable;
}

void		entity_destroy(t_entity *entity)
{
	free(entity->e.brick);
	if (entity->type == ENTITY_OBJECT)
		free(entity);
	else
		entity_set_void(entity);
}