/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:00:41 by vparis            #+#    #+#             */
/*   Updated: 2018/12/15 22:50:17 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "libtpool.h"
#include "sdl_m.h"
#include "env.h"
#include "raycast.h"
#include "parser.h"

void	update_skybox_offset(t_cam *cam, t_sdl *sdl, t_map *map)
{
	t_float motion;

	motion = atan2(cam->dir.y, cam->dir.x) + M_PI;
	map->skybox_offset = (int)(motion * (sdl->canvas_w * 2.0) /  M_PI);
}

int			load_objects(t_env *env)
{
	int		i;

	env->objects_nb = 3;
	env->objects = (t_object *)malloc(sizeof(*env->objects)
		* (size_t)env->objects_nb);
	if (env->objects == NULL)
		return (ERROR);
	i = 0;
	while (i < env->objects_nb)
	{
		env->objects[i].walkthrough = !(i > 0);
		env->objects[i].sprite = env->sdl.sprites + i;
		env->objects[i].pos = VEC2_INIT(6.0, 10.0 + i * 2.0) + 0.5;
		env->objects[i].z = 0.0;
		i++;
	}
	return (SUCCESS);
}

static int	wolf_init(t_env *env, t_map *map, t_cam *cam, char *filename)
{
	if (load_map(env, map, filename) == ERROR)
		return (ERROR);
	map->is_skybox = 1;
	map->skybox_anim = 0;
	if (sdl_load_texture(&map->skybox, "skybox/skybox_day.png") == ERROR)
		return (ERROR);
	if (load_objects(env) == ERROR)
		return (ERROR);
	cam->pos = VEC2_INIT((t_float)map->spawn.x, (t_float)map->spawn.y) + 0.5;
	cam->z = env->sdl.canvas_h * 33.0 / 100.0;
	cam->z_default = cam->z;
	cam->z_pos = cam->z_default;
	cam->dir = vec_norm(VEC2_INIT(-1.0, 0.0));
	cam->plane = VEC2_INIT(0.0, 0.88);
	cam->dir = vec_rotate(cam->dir, map->spawn_rotation * DEG_TO_RAD);
	cam->plane = vec_rotate(cam->plane, map->spawn_rotation * DEG_TO_RAD);
	cam->mov_speed = 0.05;
	cam->rot_speed = 0.016;
	cam->acceleration = 0.0;
	cam->height = 0.0;
	cam->action_state = ACTION_GROUNDED;
	cam->jump_time = 0.0;
	cam->walk_anim = 0.0;
	cam->side_filter = EFFECT_SIDE;
	cam->depth_filter = &depth_filter_depth;
	cam->color_filter = NULL;
	update_skybox_offset(cam, &env->sdl, map);
	return (SUCCESS);
}

static void	wolf_destroy(t_map *map, t_cam *cam)
{
	(void)cam;
	map_destroy(map);
	free(map->skybox.data);
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
	if (wolf_init(env, &env->map, &env->cam, filename) == ERROR)
	{
		ft_putstr_fd("Can't init wolf\n", 2);
		return (ERROR);
	}
	env->show_fps = 0;
	return (SUCCESS);
}

void		env_destroy(t_env *env)
{
	tp_destroy(&env->tpool);
	sdl_destroy(&env->sdl);
	wolf_destroy(&env->map, &env->cam);
}
