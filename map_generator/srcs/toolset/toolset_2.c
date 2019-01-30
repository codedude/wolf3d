/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolset_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 00:47:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:27:44 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void			map_fx_brush(t_env *env)
{
	if (env->inspector.b_select.type != Pencil)
		clear_map(&env->map_info);
	map_usebrush(env, (int)(env->palette.brush + 1));
}

void			map_fx_spawnsetter(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		map_pos;

	bounds = get_map_boundaries(env);
	map_pos = mpos_to_map_index(bounds, env);
	env->spawn = clamp_ivec2(map_pos, 0, env->map_info.map->size - 1);
}

void			map_fx_eraser(t_env *env)
{
	if (env->inspector.b_select.type != Pencil)
		clear_map(&env->map_info);
	map_usebrush(env, 0);
}
