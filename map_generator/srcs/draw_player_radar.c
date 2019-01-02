/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_radar.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:14:56 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/31 02:32:09 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"
#include "algo.h"

static void			draw_view_lines(t_env *env, t_radar *radar, t_u32 t_col)
{
	t_vec2		dir[2];
	t_ivec2		px[3];

	dir[0] = vec_rotate(VEC2_INIT(-1, 0),
			(-env->spawn_rotation + 33.0) / 180.0 * M_PI);
	dir[0] *= radar->vlines_height;
	dir[1] = vec_rotate(VEC2_INIT(-1, 0),
			(-env->spawn_rotation - 33.0) / 180.0 * M_PI);
	dir[1] *= radar->vlines_height;
	px[0] = radar->center;
	px[1].x = px[0].x + (int)dir[0].x;
	px[1].y = px[0].y + (int)dir[0].y;
	px[2].x = px[0].x + (int)dir[1].x;
	px[2].y = px[0].y + (int)dir[1].y;
	draw_line(env, px[0], px[1], t_col);
	draw_line(env, px[0], px[2], t_col);
}

static void			fill_view_triangle(t_env *env, t_radar *radar, t_u32 t_col)
{
	t_vec2		dir;
	t_ivec2		px;

	dir = vec_rotate(VEC2_INIT(-1, 0),
			(-env->spawn_rotation) / 180.0 * M_PI);
	dir *= radar->triangle_cdist;
	px = radar->center;
	px.x += (int)dir.x;
	px.y += (int)dir.y;
	paint_bucket_tools(env, px, t_col);
}

static void			draw_radar_gizmos(t_env *env, t_radar *radar)
{
	t_ivec2		px;
	t_float		radius;

	px = radar->center;
	radius = radar->gizmo_rad;
	env_set_color(env, 0x555555);
	draw_hline(env, IVEC2_INIT(px.x - (int)round(radius), px.y),
			px.x + (int)round(radius));
	draw_vline(env, IVEC2_INIT(px.x, px.y - (int)round(radius)),
			px.y + (int)round(radius));
	sdl_draw_circle(&env->sdl, px, radius, 0xcccccc);
	sdl_draw_circle(&env->sdl, px, radius * 0.66, 0x999999);
	sdl_draw_circle(&env->sdl, px, radius * 0.33, 0x555555);
}

static t_u32		get_triangle_color(t_env *env)
{
	if (is_bounded(env->spawn, CANVAS_INIT(0, env->map_info.map->size)))
		return (0x2BD929);
	return (0x292BD9);
}

void				draw_player_radar(t_env *env)
{
	t_radar			*radar;
	t_u32			t_col;
	t_vec2			dir;
	t_ivec2			px2;
	t_ivec2			px1;

	radar = &env->inspector.radar;
	t_col = get_triangle_color(env);
	draw_view_lines(env, radar, t_col);
	fill_view_triangle(env, radar, t_col);
	draw_radar_gizmos(env, radar);
	px1 = radar->center;
	dir = vec_rotate(VEC2_INIT(-1, 0),
			-env->spawn_rotation / 180.0 * M_PI) * radar->f_radius;
	px2.x = px1.x + (int)round(dir.x);
	px2.y = px1.y + (int)round(dir.y);
	draw_line(env, px1, px2, 0x20cccc);
}
