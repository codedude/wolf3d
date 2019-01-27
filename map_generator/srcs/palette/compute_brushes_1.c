/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_brushes_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 19:20:39 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 20:30:21 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "gen_env.h"

void			compute_simple_brush(t_env *env, t_canvas bounds)
{
	t_bresenham		br_data;
	t_ivec2			mpos_i;
	t_ivec2			mpos_i2;

	mpos_i = mpos_to_map_index(bounds, env);
	mpos_i2 = pos_to_map_index(bounds, env->mouse.last_pos, env);
	env->map_info.tmp_data[mpos_i.y][mpos_i.x] = env->palette.brush;
	if (mpos_i.x != mpos_i2.x || mpos_i.y != mpos_i2.y)
	{
		br_data = BRES_INIT(mpos_i2, mpos_i, env, draw_wall);
		ft_bresenham(&br_data);
	}
}

void			compute_line_tracer(t_env *env, t_canvas bounds)
{
	t_bresenham		br_data;
	t_ivec2			mpos_i;
	t_ivec2			mpos_i2;

	mpos_i = mpos_to_map_index(bounds, env);
	mpos_i2 = pos_to_map_index(bounds, env->mouse.record_pos_b, env);
	br_data = BRES_INIT(mpos_i2, mpos_i, env, draw_wall);
	ft_bresenham(&br_data);
	env->map_info.tmp_data[mpos_i.y][mpos_i.x] = env->palette.brush;
}

static void		compute_udline_tracer(t_env *env, int dir, t_canvas bounds)
{
	t_ud_line		udl_data;
	t_ivec2			mpos_i;

	mpos_i = mpos_to_map_index(bounds, env);
	mpos_i[dir] = 0;
	udl_data = UDL_INIT(mpos_i, env->map_info.map->size[dir],
				dir, env, draw_wall);
	ft_unidir_line(&udl_data);
}

void			compute_hline_tracer(t_env *env, t_canvas bounds)
{
	compute_udline_tracer(env, UD_LINE_HORIZONTAL, bounds);
}

void			compute_vline_tracer(t_env *env, t_canvas bounds)
{
	compute_udline_tracer(env, UD_LINE_VERTICAL, bounds);
}
