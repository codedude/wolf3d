/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radar.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:14:56 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 23:49:47 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"
#include "algo.h"

void				init_radar(t_env *env, t_radar *radar, t_canvas i_anch)
{
	t_button	*b;

	b = env->inspector.action[World];
	texdata_fill_rect(b->tex, i_anch.size, CANVAS_INIT(0, i_anch.size),
					0xacacac);
	radar->f_radius = (t_float)ipercent_of(i_anch.size.x, 95) / 2.0;
	radar->center = (int)i_anch.size.x / 2;
	radar->center.y += (int)(radar->f_radius * 0.2);
	texdata_draw_circle_filled(b->tex, CANVAS_INIT(radar->center, i_anch.size)
					, radar->f_radius, 0x757575);
	radar->center += i_anch.pos;
	radar->radius = (int)radar->f_radius;
	radar->vlines_height = radar->f_radius + 2.0;
	radar->squ_radius = radar->radius * radar->radius;
	radar->triangle_cdist = radar->vlines_height / 2.0;
	radar->gizmo_rad = (int)round(radar->f_radius);
}

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
	cpick_set_color(&env->cpick, t_col);
	draw_line(&env->sdl, &env->cpick, px[0], px[1]);
	draw_line(&env->sdl, &env->cpick, px[0], px[2]);
}

static void			fill_view_triangle(t_env *env, t_radar *radar, t_u32 t_col)
{
	t_vec2		dir;
	t_ivec2		px;

	if (env->spawn_rotation)
		dir = vec_rotate(VEC2_INIT(-1, 0),
			(-env->spawn_rotation) / 180.0 * M_PI);
	else
		dir = VEC2_INIT(-1, 0);
	dir *= radar->triangle_cdist;
	px = radar->center;
	px.x += (int)dir.x;
	px.y += (int)dir.y;
	cpick_set_color(&env->cpick, t_col);
	paint_bucket_tools(&env->sdl, &env->cpick, px);
}

static void			draw_radar_gizmos(t_env *env, t_radar *radar)
{
	t_ivec2		px;
	t_float		radius;

	px = radar->center;
	radius = radar->gizmo_rad;
	cpick_set_color(&env->cpick, 0x555555);
	draw_hline(&env->sdl, &env->cpick,
			IVEC2_INIT(px.x - (int)round(radius), px.y),
			px.x + (int)round(radius));
	draw_vline(&env->sdl, &env->cpick,
			IVEC2_INIT(px.x, px.y - (int)round(radius)),
			px.y + (int)round(radius));
	sdl_draw_circle(&env->sdl, px, radius, 0xcccccc);
	sdl_draw_circle(&env->sdl, px, radius * 0.66, 0x999999);
	sdl_draw_circle(&env->sdl, px, radius * 0.33, 0x555555);
}

void				draw_radar(t_env *env, t_radar *radar)
{
	t_u32			t_col;
	t_vec2			dir;
	t_ivec2			px2;
	t_ivec2			px1;

	if (is_bounded(env->spawn, CANVAS_INIT(0, env->map_info.map->size)))
		t_col = 0x2BB929;
	else
		t_col = 0x292BD9;
	draw_view_lines(env, radar, t_col);
	fill_view_triangle(env, radar, t_col);
	draw_radar_gizmos(env, radar);
	px1 = radar->center;
	dir = vec_rotate(VEC2_INIT(-1, 0),
			-env->spawn_rotation / 180.0 * M_PI) * radar->f_radius;
	px2.x = px1.x + (int)round(dir.x);
	px2.y = px1.y + (int)round(dir.y);
	cpick_set_color(&env->cpick, 0xcccc20);
	draw_line(&env->sdl, &env->cpick, px1, px2);
}
