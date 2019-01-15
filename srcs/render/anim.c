/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:32:48 by vparis            #+#    #+#             */
/*   Updated: 2019/01/15 17:00:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_type.h"
#include "anim.h"
#include "entity.h"
#include "anim.h"

t_anim			*anim_new(t_entity *entity, t_anim_type type, t_bool to_del,
					int key_speed)
{
	t_anim	*tmp;

	if ((tmp = (t_anim *)malloc(sizeof(t_anim))) == NULL)
		return (NULL);
	tmp->entity = entity;
	tmp->type = type;
	tmp->to_del = to_del;
	tmp->key.speed = key_speed;
	tmp->key.counter = 0;
	return (tmp);
}

void			anim_destroy(t_anim *anim)
{
	if (anim->to_del == True)
		entity_destroy(anim->entity);
	free(anim);
}

void			compute_anim(t_sdl *sdl, t_list_anim **head)
{
	t_anim	*anim;
	t_bool	r;

	while (*head != NULL)
	{
		r = False;
		anim = (*head)->value;
		if (anim->entity->type == ENTITY_DOOR)
			r = anim_door(anim);
		else if (anim->entity->type == ENTITY_OBJECT)
			r = anim_object(sdl, anim);
		else if (anim->entity->type == ENTITY_SKYBOX)
			r = anim_skybox(sdl, anim);
		else if (anim->entity->type == ENTITY_WALL)
			r = anim_wall(sdl, anim);
		if (r && anim->type != ANIM_LOOP)
			alist_del_elem(head);
		else
			head = &(*head)->next;
	}
}
