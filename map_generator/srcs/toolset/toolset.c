/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 00:47:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:28:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void			map_fx_picker(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		map_pos;
	t_entity	*ent;

	bounds = get_map_boundaries(env);
	map_pos = mpos_to_map_index(bounds, env);
	map_pos = clamp_ivec2(map_pos, 0, env->map_info.map->size - 1);
	ent = &env->map_info.map->data[map_pos.y][map_pos.x];
	if (ent->type != ENTITY_VOID)
	{
		panel_update_cursor(env->rpan.p[Texture_Panel], (t_u32)ent->tex_id);
		env->palette.brush = ent->tex_id;
	}
}

void			map_fx_hand(t_env *env)
{
	t_map_info	*minf;

	minf = &env->map_info;
	minf->pos.x += env->mouse.rel_pos.x * (1.0f / env->map_info.zoom);
	minf->pos.y += env->mouse.rel_pos.y * (1.0f / env->map_info.zoom);
}

void			map_fx_zoomin(t_env *env)
{
	t_vec2		mpos;
	t_float		old_zoom;

	old_zoom = env->map_info.zoom;
	env->map_properties.tick = 25;
	mprops_act_scale_up(env);
	if (old_zoom == env->map_info.zoom)
		return ;
	mpos.x = env->mouse.pos.x - (env->grid.pos.x + env->map_info.grid_center.x);
	mpos.y = env->mouse.pos.y - (env->grid.pos.y + env->map_info.grid_center.y);
	mpos /= env->map_info.zoom;
	env->map_info.pos -= mpos * 0.02f;
}

void			map_fx_zoomout(t_env *env)
{
	t_vec2		mpos;
	t_float		old_zoom;

	old_zoom = env->map_info.zoom;
	env->map_properties.tick = 25;
	mprops_act_scale_down(env);
	if (old_zoom == env->map_info.zoom)
		return ;
	mpos.x = env->mouse.pos.x - (env->grid.pos.x + env->map_info.grid_center.x);
	mpos.y = env->mouse.pos.y - (env->grid.pos.y + env->map_info.grid_center.y);
	mpos /= env->map_info.zoom;
	env->map_info.pos += mpos * 0.02f;
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
