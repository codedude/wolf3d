/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 00:06:46 by vparis            #+#    #+#             */
/*   Updated: 2019/01/12 00:08:49 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "env.h"
#include "sdl_m.h"
#include "types.h"
#include "entity.h"
#include "event.h"
#include "anim.h"

void		update_skybox_offset(t_cam *cam, t_sdl *sdl, t_map *map)
{
	t_float	motion;

	motion = atan2(cam->dir.y, cam->dir.x) + M_PI;
	map->skybox->tex_key = (int)(motion * (sdl->canvas_w * 2.0) / M_PI);
}

void		switch_effect(t_cam *cam, void *new, int type)
{
	void	**current;

	if (type == EFFECT_MASK_DEPTH)
		current = (void **)&cam->depth_filter;
	else if (type == EFFECT_MASK_COLOR)
		current = (void **)&cam->color_filter;
	else
		current = NULL;
	if (*current == new)
		*current = NULL;
	else
		*current = new;
}

void		binds_open_door(t_env *env)
{
	t_ivec2		i;
	t_door		*door;
	t_anim		*anim;

	i.y = 0;
	while (i.y < (int)env->map.height)
	{
		i.x = 0;
		while (i.x < (int)env->map.width)
		{
			door = env->map.data[i.y][i.x].e.door;
			if (env->map.data[i.y][i.x].type == ENTITY_DOOR
				&& door->is_active == False)
			{
				anim = anim_new(&env->map.data[i.y][i.x], ANIM_ONCE,
					ANIM_DOOR_SPEED);
				if (alist_push(&env->anims, anim) == ERROR)
					return ;
			}
			i.x++;
		}
		i.y++;
	}
}
