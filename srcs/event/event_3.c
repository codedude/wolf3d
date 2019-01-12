/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 00:06:46 by vparis            #+#    #+#             */
/*   Updated: 2019/01/12 01:54:18 by vparis           ###   ########.fr       */
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
	t_ivec2		cam_pos;
	t_ivec2		look_pos;
	t_door		*door;
	t_anim		*anim;

	cam_pos.x = (int)env->cam.pos.x;
	cam_pos.y = (int)env->cam.pos.y;
	look_pos.x = (int)(env->cam.pos.x + env->cam.dir.x * 0.8);
	look_pos.y = (int)(env->cam.pos.y + env->cam.dir.y * 0.8);
	if ((cam_pos.x == look_pos.x && cam_pos.y == look_pos.y)
		|| 0 > look_pos.y || look_pos.y >= env->map.height
		|| 0 > look_pos.x || look_pos.x >= env->map.width)
		return ;
	door = env->map.data[look_pos.y][look_pos.x].e.door;
	if (env->map.data[look_pos.y][look_pos.x].type == ENTITY_DOOR
		&& door->is_active == False)
	{
		anim = anim_new(&env->map.data[look_pos.y][look_pos.x], ANIM_ONCE,
			ANIM_DOOR_SPEED);
		if (alist_push(&env->anims, anim) == ERROR)
			return ;
	}
}
