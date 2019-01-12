/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/11 04:29:35 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static void			draw_mprops(t_env *env, t_mprops *props)
{
	t_u32		i;

	draw_canvas_fill(&env->sdl, props->anchor, CANVAS_INIT(0, 0), 0x222222);
	i = 0;
	while (i < Max_editor_action)
	{
		button_draw(env, props->actions[i]);
		i++;
	}
}

static void			draw_editmod(t_env *env)
{
	t_u32		i;

	draw_canvas_fill(&env->sdl, env->editmod.anchor,
				CANVAS_INIT(0, 0), 0x222222);
	i = 0;
	while (i < Max_EditMod_type)
	{
		button_draw(env, env->editmod.switch_b[i]);
		i++;
	}
}

static void			draw_ui(t_env *env, t_sdl *sdl)
{
	panel_draw(env, sdl, env->rpan.p[env->rpan.type]);
	button_draw(env, env->inspector.action[env->inspector.mod]);
	env->inspector.draw[env->inspector.mod](env);
	draw_mprops(env, &env->map_properties);
	draw_editmod(env);
}

static void			draw_obj_prev_on_mouse(t_env *env)
{
	t_canvas		anchor;
	t_panel			*p;

	p = env->rpan.p[Object_Panel];
	anchor.size = env->obj.mb_size;
	anchor.pos = env->mouse.pos - anchor.size / 2;
	draw_tex(env, env->obj.map_boxes[env->mouse.button_index], False, anchor);
}

t_ivec2				map_coord_to_screen(t_env *env, t_vec2 v2)
{
	t_map_info	*inf;
	t_vec2		top_left;
	t_vec2		coord;

	inf = &env->map_info;
	top_left = (inf->pos - inf->map_center) * inf->zoom;
	coord = top_left + v2 * inf->zoom + inf->grid_center;
	return (IVEC2_INIT((int)coord.x, (int)coord.y) + env->grid.pos);
}

static void			sdl_draw_rect(t_env *env, t_canvas rect, int line_h)
{
	t_ivec2		from;
	int			xy;
	int			i;

	i = 0;
	while (i < line_h)
	{
		from = rect.pos - i;
		xy = rect.pos.y + rect.size.y + i;
		draw_vline(env, from, xy);
		from.x = rect.pos.x + rect.size.x + i;
		draw_vline(env, from, xy);
		from = rect.pos - i;
		xy = rect.pos.x + rect.size.x + i;
		draw_hline(env, from, xy);
		from.y = rect.pos.y + rect.size.y + i;
		draw_hline(env, from, xy);
		i++;
	}
}

static void			draw_map_obj(t_env *env)
{
	t_u32				i;
	t_objects_tools		*otools;
	t_object			*obj;
	t_canvas			anchor;

	env_set_color(env, 0xffffff);
	env_set_canvas(env, env->grid);
	i = 0;
	otools = &env->obj;
	anchor.size = otools->mb_size;
	while (i < otools->count)
	{
		obj = otools->list[i];
		anchor.pos = map_coord_to_screen(env, obj->pos);
		if (is_bounded(anchor.pos, env->grid))
		{
			anchor.pos -= anchor.size / 2;
			draw_tex(env, env->obj.map_boxes[obj->id], False, anchor);
			if (env->editmod.type == Object
				&& (int)i == env->obj.edit.selected)
				sdl_draw_rect(env, anchor, 3);
		}
		i++;
	}
	env->cpick.use_canvas = False;
}

void				draw_grid(t_env *env, t_sdl *sdl)
{
	sdl_clear_color(sdl, 0x101010);
	draw_canvas_fill(sdl, env->grid, CANVAS_INIT(0, 0), 0x252525);
	draw_map(env, sdl);
	draw_ui(env, sdl);
	if (env->editmod.type == Object && env->mouse.area == Right_Panel
		&& env->mouse.b1 == True)
		draw_obj_prev_on_mouse(env);
	draw_map_obj(env);
}
