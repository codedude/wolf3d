/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_spec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 23:46:38 by vparis            #+#    #+#             */
/*   Updated: 2019/01/16 11:27:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"
#include "anim.h"
#include "texture.h"
#include "entity.h"
#include "env.h"
#include "anim.h"

t_bool			anim_skybox(t_sdl *sdl, t_anim *anim)
{
	if (anim->key.counter % anim->key.speed == 0)
		++anim->entity->id;
	if (anim->entity->id == tex_get_wall(sdl, anim->entity->tex_id)->w * 2)
	{
		anim->entity->id = 0;
		anim->key.counter = 0;
		return (True);
	}
	return (False);
}

t_bool			anim_texture(t_sdl *sdl, t_anim *anim)
{
	t_tex		*tex;

	if (anim->entity->type == ENTITY_OBJECT)
		tex = tex_get_sprite(sdl, anim->entity->tex_id);
	else
		tex = tex_get_wall(sdl, anim->entity->tex_id - 1);
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

static t_bool	anim_door_2(t_door *door, int cmp, t_float cmp_val)
{
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

t_bool			anim_door(t_anim *anim)
{
	int			cmp;
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
	return (anim_door_2(door, cmp, cmp_val));
}
