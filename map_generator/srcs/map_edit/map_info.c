/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:34:33 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:18:00 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "map_edit.h"
#include "sdl_m.h"
#include "sdl_plus.h"
#include "types.h"

static void		init_grid(t_env *env, t_sdl *sdl)
{
	env->grid.size.x = ipercent_of(sdl->width, GRID_SZ_X);
	env->grid.size.y = ipercent_of(sdl->height, GRID_SZ_Y);
	env->grid.pos.x = ipercent_of(sdl->width, GRID_OFF_X);
	env->grid.pos.y = ipercent_of(sdl->height, GRID_OFF_Y);
}

int				init_map_info(t_env *env, t_map_info *minf, char *mapfile)
{
	t_map	*map;

	if (!(minf->tmp_data = (int**)new_ar_data(MAX_SZ_Y, sizeof(int) * MAX_SZ_X))
	|| load_map(env, mapfile) == ERROR)
		return (ERROR);
	init_grid(env, &env->sdl);
	map_scale2grid(env);
	map = minf->map;
	minf->map_center = VEC2_INIT(map->size.x, map->size.y) / 2.0;
	minf->grid_center = VEC2_INIT(env->grid.size.x, env->grid.size.y) / 2.0;
	minf->pos = 0;
	return (SUCCESS);
}

void			destroy_map_info(t_map_info *minf)
{
	destroy_map(minf->map);
	free_ar_data((void **)minf->tmp_data, MAX_SZ_Y);
}
