/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:00:41 by vparis            #+#    #+#             */
/*   Updated: 2019/01/13 12:52:52 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "libtpool.h"
#include "sdl_m.h"
#include "env.h"
#include "types.h"
#include "raycast.h"
#include "event.h"
#include "parser.h"
#include "texture.h"
#include "camera.h"
#include "player.h"

int			load_objects(t_env *env)
{
	int			i;
	t_object	*obj;

	env->objects_nb = 4;
	env->objects = (t_entity *)malloc(sizeof(*env->objects)
		* (size_t)(env->objects_nb));
	if (env->objects == NULL)
		return (ERROR);
	i = 0;
	while (i < env->objects_nb)
	{
		obj = entity_new_object(VEC2_INIT(5.0, 8.0 + i * 2.0),
			VEC2_INIT(1.0, 1.0), 0.0, 0);
		entity_set(&env->objects[i], i, i, 0);
		entity_merge(&env->objects[i], (void *)obj, ENTITY_OBJECT);
		i++;
	}
	return (SUCCESS);
}

void		init_player(t_player *player)
{
	player->mov_speed = 0.05;
	player->rot_speed = 0.016;
	player->acceleration = 0.0;
	player->walk_anim = 0.0;
	player->jump_time = 0.0;
	player->action_state = ACTION_GROUNDED;
}

void		init_cam(t_cam *cam, t_sdl *sdl, t_map *map)
{
	cam->pos = VEC2_INIT((t_float)map->spawn.x,
		(t_float)map->spawn.y) + 0.5;
	cam->z = sdl->canvas_h * 40.0 / 100.0;
	cam->z_default = cam->z;
	cam->z_pos = cam->z_default;
	cam->dir = vec_norm(VEC2_INIT(-1.0, 0.0));
	cam->plane = VEC2_INIT(0.0, 0.88);
	cam->dir = vec_rotate(cam->dir, 270.0 * DEG_TO_RAD);
	cam->plane = vec_rotate(cam->plane, 270.0 * DEG_TO_RAD);
	cam->height = 0.0;
	cam->side_filter = EFFECT_SIDE;
	cam->depth_filter = &depth_filter_depth;
	cam->color_filter = NULL;
}

static int	wolf_init(t_env *env, char *filename)
{
	if (load_map(env, &env->map, filename) == ERROR)
		return (ERROR);
	env->map.show_ceil = 1;
	env->map.skybox = entity_new(env->sdl.tex_wall_nb - 1, 0, 0);
	entity_merge(env->map.skybox, NULL, ENTITY_SKYBOX);
	env->map.ceil_id = 1;
	env->map.floor_id = 4;
	if (load_objects(env) == ERROR)
		return (ERROR);
	init_cam(&env->cam, &env->sdl, &env->map);
	init_player(&env->player);
	return (SUCCESS);
}

static void	wolf_destroy(t_env *env, t_map *map, t_cam *cam)
{
	int	i;

	(void)cam;
	map_destroy(map);
	i = 0;
	while (i < env->objects_nb)
	{
		free(env->objects[i].e.brick);
		++i;
	}
	free(env->objects);
	entity_destroy(map->skybox);
	alist_clear(&env->anims);
}

int			env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(*env));
	if (sdl_init(&env->sdl, WINDOW_NAME, 1280, 720) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if ((env->tpool = tp_create(THREADS, TP_FPS_MODE)) == NULL)
	{
		ft_putstr_fd("Thread pool can't start\n", 2);
		return (ERROR);
	}
	if (wolf_init(env, filename) == ERROR)
	{
		ft_putstr_fd("Can't init wolf\n", 2);
		return (ERROR);
	}
	env->show_fps = 0;
	env->anims = NULL;
	return (SUCCESS);
}

void		env_destroy(t_env *env)
{
	tp_destroy(&env->tpool);
	sdl_destroy(&env->sdl);
	wolf_destroy(env, &env->map, &env->cam);
}
