/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brushes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 19:20:39 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/20 16:15:47 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "algo.h"
#include "gen_env.h"

static void		draw_wall(void *v_env, t_ivec2 pos)
{
	t_env	*env;
	int		**tmp_data;
	t_ivec2	size;

	env = (t_env*)v_env;
	tmp_data = env->map_info.tmp_data;
	size = env->map_info.map->size;
	if (pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x)
		return ;
	tmp_data[pos.y][pos.x] = env->palette.brush;
}

static void		compute_simple_brush(t_env *env, t_canvas bounds)
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

static void		compute_line_tracer(t_env *env, t_canvas bounds)
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

static void		compute_hline_tracer(t_env *env, t_canvas bounds)
{
	compute_udline_tracer(env, UD_LINE_HORIZONTAL, bounds);
}

static void		compute_vline_tracer(t_env *env, t_canvas bounds)
{
	compute_udline_tracer(env, UD_LINE_VERTICAL, bounds);
}

static void		compute_square_tracer(t_env *env, t_canvas bounds)
{
	t_ud_line		udl_data;
	t_ivec2			mpos_i;
	t_ivec2			mpos_i2;
	t_ivec2			size;

	mpos_i = mpos_to_map_index(bounds, env);
	mpos_i2 = pos_to_map_index(bounds, env->mouse.record_pos_b, env);
	size = mpos_i2 - mpos_i;
	udl_data = UDL_INIT(mpos_i, size.x, UD_LINE_HORIZONTAL, env, draw_wall);
	ft_unidir_line(&udl_data);
	udl_data.point.y = mpos_i2.y;
	if (mpos_i2.x < mpos_i.x)
		udl_data.len = -udl_data.len;
	ft_unidir_line(&udl_data);
	udl_data = UDL_INIT(mpos_i, size.y, UD_LINE_VERTICAL, env, draw_wall);
	ft_unidir_line(&udl_data);
	udl_data.point.x = mpos_i2.x;
	if (mpos_i2.y < mpos_i.y)
		udl_data.len = -udl_data.len;
	ft_unidir_line(&udl_data);
	env->map_info.tmp_data[mpos_i2.y][mpos_i2.x] = env->palette.brush;
}

static void		compute_circle_tracer(t_env *env, t_canvas bounds)
{
	t_circle		c_data;
	t_ivec2			mpos_i;
	t_ivec2			mpos_i2;
	t_float			radius;

	mpos_i = pos_to_map_index(bounds, env->mouse.record_pos_b, env);
	mpos_i2 = mpos_to_map_index(bounds, env) - mpos_i;
	mpos_i2 = IVEC2_INIT((int)abs(mpos_i2.x), (int)abs(mpos_i2.y));
	radius = (t_float)(mpos_i2.x > mpos_i2.y ? mpos_i2.x : mpos_i2.y);
	c_data = CIRCLE_INIT(mpos_i, radius, env, draw_wall);
	ft_circle(&c_data);
}

static int		wall_pbuck_cond(t_flood_d *f_data, t_ivec2 point)
{
	t_env	*env;
	t_map	*map;
	int		tex_id;

	env = (t_env*)f_data->param;
	map = env->map_info.map;
	if (point.y < 0 || point.y >= map->size.y
		|| point.x < 0 || point.x >= map->size.x)
		return (False);
	if (map->data[point.y][point.x].type == ENTITY_VOID)
		tex_id = 0;
	else
		tex_id = map->data[point.y][point.x].tex_id + 1;
	return (tex_id == env->ed_map_value
	&& env->map_info.tmp_data[point.y][point.x] != env->palette.brush);
}

static void		wall_pbuck_act(t_flood_d *f_data, t_ivec2 point)
{
	t_env	*env;

	env = (t_env*)f_data->param;
	env->map_info.tmp_data[point.y][point.x] = env->palette.brush;
}

static void		compute_bucket_filler(t_env *env, t_canvas bounds)
{
	t_flood_d		f_data;
	t_entity		*ent;
	t_ivec2			mpos_i;

	mpos_i = mpos_to_map_index(bounds, env);
	ent = &env->map_info.map->data[mpos_i.y][mpos_i.x];
	env->ed_map_value = (ent->type == ENTITY_VOID) ? 0 : ent->tex_id + 1;
	if (env->ed_map_value == env->palette.brush)
		return ;
	f_data = FLOOD_D_INIT(wall_pbuck_cond, wall_pbuck_act, env);
	ft_flood(&f_data, mpos_i);
}

static void 	init_brush_fx(t_palette *palette)
{
	palette->b_fx[Pencil] = compute_simple_brush;
	palette->b_fx[Line] = compute_line_tracer;
	palette->b_fx[Horizontal_line] = compute_hline_tracer;
	palette->b_fx[Vertical_line] = compute_vline_tracer;
	palette->b_fx[Square] = compute_square_tracer;
	palette->b_fx[Circle] = compute_circle_tracer;
	palette->b_fx[Paint_Bucket] = compute_bucket_filler;
}

void 			palette_init(t_env *env)
{
	t_palette	*palette;

	palette = &env->palette;
	palette->brush = 0;
	init_brush_fx(palette);
}
