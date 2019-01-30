/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 21:33:07 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:18:27 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "map_edit.h"
#include "types.h"

t_vec2				map_to_center(t_env *env)
{
	t_vec2		center;

	center.x = (t_float)env->grid.pos.x + ((t_float)env->grid.size.x / 2.0f);
	center.y = (t_float)env->grid.pos.y + ((t_float)env->grid.size.y / 2.0f);
	return (center);
}

static void			map_update_zoom_range(t_env *env, t_map_info *minf)
{
	t_map			*map;
	t_float			min[2];
	t_float			max[2];

	map = minf->map;
	min[0] = ipercent_of(env->grid.size.x, 98)
			/ (t_float)(map->size.x);
	max[0] = env->grid.size.x / 2.0f;
	min[1] = ipercent_of(env->grid.size.y, 98)
			/ (t_float)(map->size.y);
	max[1] = env->grid.size.y / 2.0f;
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
	t_map			*map;

	minf = &env->map_info;
	map = minf->map;
	minf->map_center = VEC2_INIT(map->size.x / 2.0f, map->size.y / 2.0f);
	map_update_zoom_range(env, minf);
}
