/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/22 03:17:08 by jbulant          ###   ########.fr       */
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

	draw_canvas_fill(&env->sdl, &props->anchor,
		&CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), 0x222222);
	i = 0;
	while (i < Max_editor_action)
	{
		button_draw(env, props->actions[i]);
		i++;
	}
}

static void			draw_editor(t_env *env)
{
	t_u32		i;

	draw_canvas_fill(&env->sdl, &env->editor.anchor,
		&CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), 0x222222);
	i = 0;
	while (i < Max_EditMod_type)
	{
		button_draw(env, env->editor.switch_b[i]);
		i++;
	}
}

static void			draw_ui(t_env *env, t_sdl *sdl)
{
	panel_draw(env, sdl, env->rpan.p[env->rpan.type]);
	button_draw(env, env->inspector.action[env->editor.mode]);
	env->inspector.draw[env->editor.mode](env);
	draw_mprops(env, &env->map_properties);
	draw_editor(env);
}

static void			draw_obj_prev_on_mouse(t_env *env)
{
	t_canvas		anchor;
	t_panel			*p;

	p = env->rpan.p[Object_Panel];
	anchor.size = env->obj.mb_size;
	anchor.pos = env->mouse.pos - anchor.size / 2;
	draw_tex(env, &env->sdl.tex_sprites[env->mouse.button_index], False, anchor);
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

void				sdl_draw_rect(t_env *env, t_canvas rect, int line_h)
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

static t_bool		test_position(t_canvas anch, t_canvas grid)
{
	if ((anch.pos.x < grid.pos.x && anch.pos.x + anch.size.x < grid.pos.x)
	|| (anch.pos.y < grid.pos.y && anch.pos.y + anch.size.y < grid.pos.y))
		return (False);
	return (True);
}

static t_ivec2		get_prev_size(t_env *env)
{
	t_map_info	*m_inf;

	m_inf = &env->map_info;
	return (m_inf->x_draw[1] - m_inf->x_draw[0]);
}

static void			draw_single_obj(t_env *env, t_objects_tools *otools,
						t_canvas anchor, int i)
{
	t_object_e			*obj;

	obj = otools->list[i];
	anchor.pos = map_coord_to_screen(env, obj->pos);
	if (test_position(anchor, env->grid))
	{
		anchor.pos -= anchor.size / 2;
		if (env->editor.mode == Object_Edit && (int)i == env->obj.edit.selected)
			sdl_draw_rect(env, anchor, 3);
		if (obj->unlock_door != NULL)
		{
			i = anchor.size.x / 10;
			while (i--)
			{
				anchor.size -= 2;
				anchor.pos += 1;
				draw_canvas_border(&env->sdl, anchor, env->grid, 0xffff00);
			}
		}
		draw_tex(env, &env->sdl.tex_sprites[obj->id], False, anchor);
	}
}

static void			draw_map_obj(t_env *env)
{
	t_u32				i;
	t_objects_tools		*otools;
	t_canvas			anchor;

	env_set_color(env, 0xffffff);
	env_set_canvas(env, env->grid);
	i = 0;
	otools = &env->obj;
	anchor.size = get_prev_size(env);
	while (i < otools->count)
	{
		draw_single_obj(env, otools, anchor, (int)i);
		i++;
	}
	env_unset_canvas(env);
}

void				draw_grid(t_env *env, t_sdl *sdl)
{
	t_canvas		c;

	c.size = IVEC2_ZERO;
	c.pos = IVEC2_ZERO;
	sdl_clear_color(sdl, 0x101010);
	draw_canvas_fill(sdl, &env->grid, &c, 0x252525);
	draw_map(env, sdl);
	draw_ui(env, sdl);
	if (env->editor.mode == Object_Edit && env->mouse.area == Right_Panel
		&& env->mouse.b1 == True)
		draw_obj_prev_on_mouse(env);
	draw_map_obj(env);
}
