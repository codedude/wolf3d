/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 21:33:07 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 02:07:50 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "map_edit.h"
#include "types.h"

t_ivec2		map_coord_to_screen(t_env *env, t_vec2 v2)
{
	t_map_info	*inf;
	t_vec2		top_left;
	t_vec2		coord;

	inf = &env->map_info;
	top_left = (inf->pos - inf->map_center) * inf->zoom;
	coord = top_left + v2 * inf->zoom + inf->grid_center;
	return (IVEC2_INIT((int)coord.x, (int)coord.y) + env->grid.pos);
}

t_canvas	get_map_boundaries(t_env *env)
{
	t_canvas	bounds;
	t_vec2		pos;

	pos = (env->map_info.pos - env->map_info.map_center) * env->map_info.zoom
		+ env->map_info.grid_center;
	bounds.pos = IVEC2_INIT((int)pos.x, (int)pos.y) + env->grid.pos;
	bounds.size.x = (int)(env->map_info.map->size.x * env->map_info.zoom);
	bounds.size.y = (int)(env->map_info.map->size.y * env->map_info.zoom);
	return (bounds);
}

t_vec2		mpos_to_map_coord(t_canvas bounds, t_ivec2 mpos, t_env *env)
{
	t_vec2		v2;

	mpos -= bounds.pos;
	v2 = VEC2_INIT((t_float)mpos.x, (t_float)mpos.y) / env->map_info.zoom;
	return (v2);
}

t_ivec2		mpos_to_map_index(t_canvas bounds, t_env *env)
{
	t_vec2		v2;

	v2 = mpos_to_map_coord(bounds, env->mouse.pos, env);
	return (IVEC2_INIT((int)v2.x, (int)v2.y));
}

t_ivec2		pos_to_map_index(t_canvas bounds, t_ivec2 pos, t_env *env)
{
	t_vec2		v2;

	v2 = mpos_to_map_coord(bounds, pos, env);
	return (IVEC2_INIT((int)v2.x, (int)v2.y));
}
