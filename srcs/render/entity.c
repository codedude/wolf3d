/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/09 16:19:00 by vparis            #+#    #+#             */
/*   Updated: 2019/01/15 13:10:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"
#include "types.h"
#include "entity.h"

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
	entity->tex_calc = IVEC3_ZERO;
	entity->id = 0;
	entity->crossable = 1;
	entity->type = ENTITY_VOID;
	entity->e.brick = NULL;
}

void		entity_set_wall(t_entity *entity, int tex_id, int id,
				int crossable)
{
	entity->type = ENTITY_WALL;
	entity->e.brick = NULL;
	entity_set(entity, tex_id, id, crossable);
}

void		entity_set(t_entity *entity, int tex_id, int id,
				int crossable)
{
	entity->tex_id = tex_id;
	entity->tex_key = 0;
	entity->tex_calc = IVEC3_ZERO;
	entity->id = id;
	entity->crossable = crossable;
}

void		entity_destroy(t_entity *entity)
{
	free(entity->e.brick);
	entity->e.brick = NULL;
	if (entity->type == ENTITY_OBJECT)
		free(entity);
	else
		entity_set_void(entity);
}
