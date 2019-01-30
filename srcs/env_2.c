/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:00:41 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:13:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "sdl_m.h"
#include "env.h"
#include "types.h"
#include "raycast.h"
#include "event.h"
#include "parser.h"
#include "camera.h"
#include "player.h"

static void	init_player(t_player *player)
{
	player->axis_state = Axis_None;
	player->velocity = VEC2_ZERO;
	player->dash_time = 0.0f;
	player->mov_speed = 0.05f;
	player->rot_speed = 0.016f;
	player->acceleration = 0.0f;
	player->walk_anim = 0.0f;
	player->jump_time = 0.0f;
	player->action_state = ACTION_GROUNDED;
	player->inventory = NULL;
}

static void	init_cam(t_cam *cam, t_sdl *sdl, t_map *map)
{
	cam->pos = VEC2_INIT((t_float)map->spawn.x,
		(t_float)map->spawn.y) + 0.5f;
	cam->z = 40.0f / 100.0f;
	cam->z_default = cam->z;
	cam->z_pos = cam->z_default;
	cam->rot = map->spawn_rotation * DEG_TO_RAD;
	cam->dir = vec_norm(VEC2_INIT(-1.0f, 0.0f));
	cam->plane = VEC2_INIT(0.0f, sdl->ratio_y);
	cam->dir = vec_rotate(cam->dir, cam->rot);
	cam->plane = vec_rotate(cam->plane, cam->rot);
	cam->height = 0.0f;
	cam->side_filter = EFFECT_SIDE;
	cam->depth_filter = &depth_filter_depth;
	cam->color_filter = NULL;
}

int			wolf_init(t_env *env, char *filename)
{
	if (load_map(env, &env->map, filename) == ERROR)
		return (ERROR);
	env->map.skybox = entity_new(0, 0, 0);
	entity_merge(env->map.skybox, NULL, ENTITY_SKYBOX);
	init_cam(&env->cam, &env->sdl, &env->map);
	init_player(&env->player);
	return (SUCCESS);
}

void		wolf_destroy(t_env *env, t_map *map)
{
	int	i;

	destroy_map_data(&map->data, map->width, map->height);
	i = 0;
	while (i < env->objects_nb)
	{
		free(env->objects[i].e.brick);
		++i;
	}
	free(env->objects);
	alist_clear(&env->anims);
}
