/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 16:32:48 by vparis            #+#    #+#             */
/*   Updated: 2019/01/10 18:53:35 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_type.h"
#include "anim.h"
#include "entity.h"
#include "texture.h"

t_anim			*anim_new(t_entity *entity, t_anim_type type, int key_speed)
{
	t_anim	*tmp;

	if ((tmp = (t_anim *)malloc(sizeof(t_anim))) == NULL)
		return (NULL);
	tmp->entity = entity;
	tmp->type = type;
	tmp->key.speed = key_speed;
	tmp->key.counter = 0;
	return (tmp);
}

void			anim_destroy(t_anim *anim)
{
	if (anim->type == ANIM_DESTROY)
		entity_destroy(anim->entity);
	free(anim);
}

t_list_anim		*alist_new(t_anim *value)
{
	t_list_anim	*tmp;

	tmp = (t_list_anim *)malloc(sizeof(t_list_anim));
	if (tmp == NULL)
		return (NULL);
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

int				alist_push(t_list_anim **head, t_anim *entry)
{
	t_list_anim	*tmp;

	if ((tmp = alist_new(entry)) == NULL)
		return (ERROR);
	tmp->next = *head;
	*head = tmp;
	return (SUCCESS);
}

void			alist_del_elem(t_list_anim **head)
{
	t_list_anim *next;

	next = (*head)->next;
	anim_destroy((*head)->value);
	free(*head);
	*head = next;
}

void			alist_del(t_list_anim **head, t_list_anim *entry)
{
	while (*head != entry)
		head = &(*head)->next;
	*head = entry->next;
	anim_destroy(entry->value);
	free(entry);
}

void			alist_clear(t_list_anim **head)
{
	while (*head)
		alist_del(head, *head);
}

void			anim_compute(t_sdl *sdl, t_list_anim **head)
{
	t_anim	*anim;
	int		r;

	while (*head != NULL)
	{
		r = False;
		anim = (*head)->value;
		if (anim->entity->type == ENTITY_DOOR)
			r = anim_door(anim);
		else if (anim->entity->type == ENTITY_OBJECT)
			r = anim_object(sdl, anim);
		if (r && anim->type != ANIM_LOOP)
			alist_del_elem(head);
		else
			head = &(*head)->next;
	}
}

t_bool			anim_object(t_sdl *sdl, t_anim *anim)
{
	t_object	*obj;
	t_tex		*tex;

	obj = anim->entity->e.object;
	tex = tex_get_sprite(sdl, anim->entity->tex_id);
	if (anim->key.counter % anim->key.speed == 0)
		++anim->entity->tex_key;
	if (anim->entity->tex_key == tex->n_sprites)
	{
		anim->entity->tex_key = 0;
		anim->key.counter = 0;
		return (True);
	}
	++anim->key.counter;
	return (False);
}

t_bool			anim_door(t_anim *anim)
{
	t_u32		cmp;
	t_float		cmp_val;
	t_float		off;
	t_door		*door;

	door = anim->entity->e.door;
	if (door->is_open == False)
	{
		cmp = (door->open_offset <= 0.0);
		cmp_val = 0.0;
		off = -ANIM_DOOR_OFFSET;
	}
	else
	{
		cmp = (door->open_offset >= 1.0);
		cmp_val = 1.0;
		off = ANIM_DOOR_OFFSET;
	}
	door->open_offset += off;
	if (cmp)
	{
		door->open_offset = cmp_val;
		door->is_open = !door->is_open;
		door->is_active = False;
		return (True);
	}
	else
		door->is_active = True;
	return (False);
}