/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 00:47:18 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/31 02:03:24 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void			map_fx_brush(t_env *env)
{
	if (env->inspector.b_select.type != Pencil)
		clear_map(env->map_info.map_mask);
	draw_on_map(env, (int)(env->palette.brush + 1));
}

void			map_fx_spawnsetter(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		map_pos;

	bounds = get_map_boundaries(env);
	map_pos = mpos_to_map_index(bounds, env->mouse.pos, env);
	env->spawn = clamp_ivec2(map_pos, 0, env->map_info.map->size - 1);
}

void			map_fx_eraser(t_env *env)
{
	if (env->inspector.b_select.type != Pencil)
		clear_map(env->map_info.map_mask);
	draw_on_map(env, 0);
}

void			map_fx_picker(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		map_pos;
	int			map_b;

	bounds = get_map_boundaries(env);
	map_pos = mpos_to_map_index(bounds, env->mouse.pos, env);
	map_pos = clamp_ivec2(map_pos, 0, env->map_info.map->size - 1);
	map_b = env->map_info.map->data[map_pos.y][map_pos.x];
	if (map_b != 0 )
	{
		panel_update_cursor(env->palette.b_pan, (t_u32)(map_b - 1));
		env->palette.brush = map_b - 1;
	}
}

void			map_fx_hand(t_env *env)
{
	t_map_info	*minf;

	minf = &env->map_info;
	minf->pos.x += env->mouse.rel_pos.x * (1.0 / env->map_info.zoom);
	minf->pos.y += env->mouse.rel_pos.y * (1.0 / env->map_info.zoom);
}

void			map_fx_zoomin(t_env *env)
{
	t_vec2		mpos;
	t_float		old_zoom;

	old_zoom = env->map_info.zoom;
	mprops_act_scale_up(env);
	if (old_zoom == env->map_info.zoom)
		return ;
	mpos.x = env->mouse.pos.x - (env->grid.pos.x + env->map_info.grid_center.x);
	mpos.y = env->mouse.pos.y - (env->grid.pos.y + env->map_info.grid_center.y);
	mpos /= env->map_info.zoom;
	env->map_info.pos -= mpos * 0.02;
}

void			map_fx_zoomout(t_env *env)
{
	t_vec2		mpos;
	t_float		old_zoom;

	old_zoom = env->map_info.zoom;
	mprops_act_scale_down(env);
	if (old_zoom == env->map_info.zoom)
		return ;
	mpos.x = env->mouse.pos.x - (env->grid.pos.x + env->map_info.grid_center.x);
	mpos.y = env->mouse.pos.y - (env->grid.pos.y + env->map_info.grid_center.y);
	mpos /= env->map_info.zoom;
	env->map_info.pos += mpos * 0.02;
}

void			init_toolset(t_toolset *toolset)
{
	toolset->map_fx[Brush] = map_fx_brush;
	toolset->map_fx[SpawnSetter] = map_fx_spawnsetter;
	toolset->map_fx[Eraser] = map_fx_eraser;
	toolset->map_fx[Picker] = map_fx_picker;
	toolset->map_fx[Hand] = map_fx_hand;
	toolset->map_fx[ZoomIn] = map_fx_zoomin;
	toolset->map_fx[ZoomOut] = map_fx_zoomout;
	toolset->type = Brush;
	toolset->use_tmp = False;
}

void			toolset_use_fx(t_env *env)
{
	t_toolset	*toolset;

	toolset = &env->toolset;
	if (toolset->use_tmp)
	{
		toolset->map_fx[toolset->tmp_type](env);
		toolset->use_tmp = False;
	}
	else
		toolset->map_fx[toolset->type](env);
}

void			toolset_set_type(t_toolset *toolset, t_u32 type)
{
	toolset->type = type;
}

void			toolset_set_tmp_type(t_toolset *toolset, t_u32 type)
{
	toolset->tmp_type = type;
	toolset->use_tmp = True;
}

void			toolset_unset_tmp_type(t_toolset *toolset)
{
	toolset->use_tmp = False;
}
