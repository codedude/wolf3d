/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/31 01:12:27 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static void			init_grid(t_env *env, t_sdl *sdl)
{
	env->grid.size.x = ipercent_of(sdl->width, GRID_SIZE_X);
	env->grid.size.y = ipercent_of(sdl->height, GRID_SIZE_Y);
	env->grid.pos.x = ipercent_of(sdl->width, GRID_OFF_X);
	env->grid.pos.y = ipercent_of(sdl->height, GRID_OFF_Y);
	env->space = 0;
	env->alt = 0;
	env->mouse2 = 0;
}

void				map_update_zoom_range(t_env *env, t_map_info *minf)
{
	t_map 			*map;
	t_float			min[2];
	t_float			max[2];

	map = minf->map;
	min[0] = ipercent_of(env->grid.size.x, 98)
			/ (t_float)(map->size.x);
	max[0] = env->grid.size.x / 2.0;
	min[1] = ipercent_of(env->grid.size.y, 98)
			/ (t_float)(map->size.y);
	max[1] = env->grid.size.y / 2.0;
	if (min[0] < min[1])
	{
		minf->zoom_min = min[0];
		minf->zoom_max = max[0];
	}
	else
	{
		minf->zoom_min = min[1];
		minf->zoom_max = max[1];
	}
}

void				map_scale2grid(t_env *env)
{
	t_map_info		*minf;

	minf = &env->map_info;
	map_update_zoom_range(env, minf);
	minf->zoom = minf->zoom_min;
}

void				map_update_center(t_env *env)
{
	t_map_info		*minf;
	t_map 			*map;

	minf = &env->map_info;
	map = minf->map;
	minf->map_center = VEC2_INIT(map->size.x / 2.0, map->size.y / 2.0);
	map_update_zoom_range(env, minf);
}

static void			init_map_info(t_env *env, t_map_info *minf)
{
	t_map 	*map;

	map = minf->map;
	map_scale2grid(env);
	// minf->zoom = 200;
	minf->map_center = VEC2_INIT(map->size.x / 2.0, map->size.y / 2.0);
	minf->grid_center = VEC2_INIT(env->grid.size.x / 2.0,
								env->grid.size.y / 2.0);
	minf->pos = 0;
}

static int			env_init2(t_env *env, char *filename)
{
	t_map		*map;

	map = env->map_info.map;
	init_grid(env, &env->sdl);
	env->user_action = Draw_Wall;
	env->save_file = filename;
	env->mouse1 = 0;
	env->space = 0;
	env->spawn = IVEC2_INIT(map->size.x / 2, map->size.y / 2);
	env->spawn_rotation = 0;
	env->saved = True;
	button_setactive(env->act_buttons[Draw_Wall], True);
	mouse_track_init(env);
	palette_init(env);
	env->spawner_id = (int)env->palette.b_pan->nb_elem;
	init_map_info(env, &env->map_info);
	init_toolset(&env->toolset);
	return (SUCCESS);
}

int					env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(*env));
	if (is_valid_mapfile(filename) == False)
		return (ERROR);
	if (sdl_init(&env->sdl, MAP_GEN_NAME, WIN_X, WIN_Y) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if (!(env->map_info.map_mask = create_new_map(IVEC2_INIT(DEF_SIZE_X, DEF_SIZE_Y)))
		|| !(env->map_info.map = create_new_map(IVEC2_INIT(DEF_SIZE_X, DEF_SIZE_Y)))
		|| env_create_buttons(env) == ERROR)
	{
		perror("W3dEditor");
		return (ERROR);
	}
	return (env_init2(env, filename));
}
