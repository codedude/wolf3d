/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 00:06:46 by vparis            #+#    #+#             */
/*   Updated: 2019/01/29 19:13:28 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"
#include "env.h"
#include "sdl_m.h"
#include "types.h"
#include "entity.h"
#include "event.h"
#include "anim.h"
#include "camera.h"
#include "player.h"

void		update_skybox_offset(t_cam *cam, t_sdl *sdl, t_map *map)
{
	t_float	motion;

	motion = atan2f(cam->dir.y, cam->dir.x) + MY_PI;
	map->skybox->tex_key = (int)(motion * (sdl->canvas_w * 2.0f) / MY_PI);
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

void		binds_open_door(t_env *env, t_cam *cam, t_map *map)
{
	t_ivec2		cam_pos;
	t_ivec2		look_pos;
	t_door		*door;
	t_anim		*anim;

	cam_pos = IVEC2_INIT((int)cam->pos.x, (int)cam->pos.y);
	look_pos.x = (int)(cam->pos.x + cam->dir.x * 0.8f);
	look_pos.y = (int)(cam->pos.y + cam->dir.y * 0.8f);
	if ((cam_pos.x == look_pos.x && cam_pos.y == look_pos.y)
		|| 0 > look_pos.y || look_pos.y >= map->height
		|| 0 > look_pos.x || look_pos.x >= map->width)
		return ;
	door = map->data[look_pos.y][look_pos.x].e.door;
	if (map->data[look_pos.y][look_pos.x].type == ENTITY_DOOR
		&& door->is_active == False)
	{
		if (door->item_id != -1
		&& klist_find(&env->player.inventory, door->item_id) == NULL)
			return ;
		anim = anim_new(&map->data[look_pos.y][look_pos.x],
			ANIM_DOOR | ANIM_ONCE, False, ANIM_DOOR_SPEED);
		if (alist_push(&env->anims, anim) == SUCCESS)
			sound_play(&env->audio, SOUND_DOOR_OPEN);
	}
}
