/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 23:52:51 by vparis            #+#    #+#             */
/*   Updated: 2019/01/11 23:53:47 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
