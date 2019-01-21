/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_track.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 01:30:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/20 23:25:57 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static int		find_selected_obj(t_env *env)
{
	t_ivec2		mpos;
	t_canvas	anch;
	t_u32		i;

	mpos = env->mouse.pos;
	anch.size = env->obj.mb_size;
	i = 0;
	while (i < env->obj.count)
	{
		anch.pos = map_coord_to_screen(env, env->obj.list[i]->pos);
		anch.pos -= anch.size / 2;
		if (is_bounded(env->mouse.pos, anch))
		{
			env->mouse.obj_offset = env->obj.list[i]->pos
			- mpos_to_map_coord(get_map_boundaries(env), env->mouse.pos, env);
			return ((int)i);
		}
		i++;
	}
	return (-1);
}

static t_bool	g_mw_painter(t_env *env)
{
	if (is_bounded(env->mouse.pos, env->grid))
	{
		env->mouse.is_editing = True;
		env->mouse.b2_cancel_b1 = True;
		clear_map(&env->map_info);
		if (env->editor.mode != Painter && env->editor.mode != World)
			env->mouse.no_trigger = True;
		return (True);
	}
	return (False);

}

static t_bool	g_mw_object_edit(t_env *env)
{
	int		obj;

	obj = find_selected_obj(env);
	if (obj != -1)
	{
		env->obj.holding = True;
		env->obj.edit.selected = obj;
		env->mouse.button_index = (t_u32)obj;
		return (True);
	}
	else if (is_bounded(env->mouse.pos, env->grid))
		env->obj.edit.selected = -1;
	return (False);

}

static t_bool	g_mw_door(t_env *env)
{
	t_ivec2			mpos;
	t_entity		*ent;
	t_door_edit		*dedit;

	dedit = &env->inspector.door_edit;
	if (door_valid_mouse_coord(env))
	{
		mpos = mpos_to_map_index(get_map_boundaries(env), env);
		ent = &env->map_info.map->data[mpos.y][mpos.x];
		dedit->selected = (ent->type == ENTITY_DOOR) ? ent : NULL;
		return (True);
	}
	dedit->selected = NULL;
	return (False);
}

static t_bool	g_area_mw(t_env *env)
{
	t_u32		type;

	type = toolset_get_type(&env->toolset);
	env->obj.holding = False;
	if (is_bounded(env->mouse.pos, env->grid))
	{
		if (env->editor.mode == Painter || env->editor.mode == World
		|| type >= Max_ToolType_Painter)
			return (g_mw_painter(env));
		else if (env->editor.mode == Object_Edit)
			return (g_mw_object_edit(env));
		else if (env->editor.mode == Door)
			return (g_mw_door(env));
	}
	return (False);
}

static t_bool	g_area_mpb(t_env *env)
{
	t_u32		i;
	t_button	*b;
	t_mprops	*props;

	props = &env->map_properties;
	i = 0;
	while (i < Max_editor_action)
	{
		b = props->actions[i];
		if (is_bounded(env->mouse.pos, b->anchor))
		{
			props->tick = 0;
			props->speed = 15;
			env->mouse.b2_cancel_b1 = True;
			env->mouse.button_index = i;
			return (True);
		}
		i++;
	}
	return (False);
}

static t_bool	g_area_i(t_env *env)
{
	if (env->inspector.get_button[env->editor.mode](env))
	{
		env->mouse.b2_cancel_b1 = True;
		return (True);
	}
	return (False);
}

static t_bool	g_area_tb(t_env *env)
{
	t_u32		i;
	t_button	*b;

	i = 0;
	while (i < Max_EditMod_type)
	{
		b = env->editor.switch_b[i];
		if (is_bounded(env->mouse.pos, b->anchor))
		{
			env->mouse.b2_cancel_b1 = True;
			env->mouse.button_index = i;
			return (True);
		}
		i++;
	}
	return (False);
}

static t_bool	g_area_rpan(t_env *env)
{
	int		i;

	i = panel_get_index_by_pos(env->rpan.p[env->rpan.type], env->mouse.pos);
	if (i == -1)
		return (False);
	env->mouse.b2_cancel_b1 = True;
	env->mouse.button_index = (t_u32)i;
	return (True);
}

static void		init_get_area(t_mousetrack *mtrack)
{
	mtrack->get_area[Map_window] = g_area_mw;
	mtrack->get_area[Map_properties_buttons] = g_area_mpb;
	mtrack->get_area[Inspector] = g_area_i;
	mtrack->get_area[Tools_buttons] = g_area_tb;
	mtrack->get_area[Right_Panel] = g_area_rpan;
}

void			mouse_track_update_area(t_env *env)
{
	t_u32		i;

	env->mouse.button_index = 0;
	i = 0;
	while (i < Max_Win_Area && env->mouse.get_area[i](env) == False)
		i++;
	env->mouse.area = i;
}

void			mouse_button_setstate(t_env *env, int button, t_bool state)
{
	t_mousetrack	*tracker;

	tracker = &env->mouse;
	if (button == 1)
	{
		if (state == True)
		{
			tracker->b2_cancel_b1 = False;
			tracker->record_pos_b = tracker->pos;
			tracker->b1_status = Mouse_Press;
			env->mouse.no_trigger = False;
			mouse_track_update_area(env);
		}
		else if (tracker->b1 == True && tracker->area != Not_On_Window
			&& tracker->no_trigger == False)
		{
			tracker->b1_status = Mouse_Release;
			tracker->trigger[tracker->area](env);
		}
		tracker->b1 = state;
	}
	else
	{
		tracker->b2 = state;
		if (state == False && tracker->b2_cancel_b1)
		{
			if (env->mouse.area == Inspector && env->editor.mode == Painter)
				env->inspector.b_select.type = env->inspector.b_select.type_save;
			tracker->is_editing = False;
			tracker->b1 = False;
		}
	}
}

static int		remove_wall(t_env *env, t_entity *ent)
{
	if (ent->type != ENTITY_VOID)
	{
		if (ent == env->inspector.door_edit.selected)
			env->inspector.door_edit.selected = NULL;
		entity_destroy(ent, True);
		return (1);
	}
	return (0);
}

static void		mw_update_map(t_env *env, t_map *map, int **mask, t_ivec2 i)
{
	t_entity	*ent;
	int			save[3];
	int			n;

	n = mask[i.y][i.x];
	if (n == 0)
		return ;
	ft_bzero(save, sizeof(save));
	ent = &map->data[i.y][i.x];
	if (n == -1)
		save[0] = remove_wall(env, ent);
	else
	{
		if ((save[1] = (ent->type == ENTITY_VOID)))
			ent->type = ENTITY_WALL;
		if ((save[2] = (ent->tex_id + 1 != n)))
			ent->tex_id = n - 1;
	}
	n = 0;
	while (n < 3)
		env->saved |= save[n++];
}

static void		t_mw_painter(t_env *env)
{
	t_ivec2		i;
	t_map		*map;
	t_map_info	*m_inf;

	env->mouse.is_editing = False;
	m_inf = &env->map_info;
	map = m_inf->map;
	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			mw_update_map(env, map, m_inf->tmp_data, i);
			i.x++;
		}
		i.y++;
	}
}

static void		t_mw_object_edit(t_env *env)
{
	if (env->obj.holding == True
		&& !is_bounded(env->mouse.pos, get_map_boundaries(env)))
		object_destroy(&env->obj, env->mouse.button_index);
}

static void		t_mw_door(t_env *env)
{
	t_door_edit	*dedit;
	t_entity	*ent;
	t_ivec2		pos;

	dedit = &env->inspector.door_edit;
	pos = mpos_to_map_index(get_map_boundaries(env), env);
	dedit->door_pos = pos;
	if (door_valid_mouse_coord(env))
	{
		ent = &env->map_info.map->data[pos.y][pos.x];
		if (ent->type != ENTITY_DOOR)
			door_create(env, dedit);
		else
			dedit->selected = ent;
	}
	else
		dedit->selected = NULL;
}

static void		t_area_mw(t_env *env)
{
	if (env->editor.mode == Painter || env->editor.mode == World)
		t_mw_painter(env);
	else if (env->editor.mode == Object_Edit)
		t_mw_object_edit(env);
	else if (env->editor.mode == Door)
		t_mw_door(env);
}

static void		t_area_mpb(t_env *env)
{
	t_u32			b_index;
	t_mprops		*props;

	props = &env->map_properties;
	b_index = env->mouse.button_index;
	if (b_index == Recenter)
	{
		if (button_hover(props->actions[b_index], env->mouse.pos) == True)
			button_trigger(props->actions[b_index]);
	}
}

static void		t_area_i(t_env *env)
{
	button_trigger(env->inspector.action[env->editor.mode]);
}

static void		t_area_tb(t_env *env)
{
	t_u32				b_index;

	b_index = env->mouse.button_index;
	if (button_hover(env->editor.switch_b[b_index], env->mouse.pos) == True)
		button_setactive(env->editor.switch_b[b_index], True);
}

static void		t_area_wtm(t_env *env)
{
	t_mousetrack	*tracker;
	t_panel			*p;
	int				y_dist;

	tracker = &env->mouse;
	p = env->rpan.p[Texture_Panel];
	y_dist = tracker->record_pos_b.y - tracker->pos.y;
	if (y_dist < 0)
		y_dist = -y_dist;
	if (y_dist < 15)
	{
		panel_update_cursor(p, tracker->button_index);
		env->palette.brush = (int)p->cursor;
	}
}

static void		t_area_otm(t_env *env)
{
	t_vec2		mpos;
	t_canvas	mbounds;

	if (env->editor.mode == Object_Edit)
	{
		if (env->obj.edit.selected != -1
		&& is_bounded(env->mouse.pos, env->obj.edit.bg_prev))
		{
			env->obj.list[env->obj.edit.selected]->id = env->mouse.button_index;
			return ;
		}
	}
	mbounds = get_map_boundaries(env);
	if (!is_bounded(env->mouse.pos, mbounds))
		return ;
	mpos = mpos_to_map_coord(mbounds, env->mouse.pos, env);
	if (env->obj.g_snap->val != 0.0)
		mpos = vec_snap(mpos + 0.5, env->obj.g_snap->val) - 0.5;
	add_new_object(&env->obj, mpos, 1, env->mouse.button_index);
}

static void		t_area_rpan(t_env *env)
{
	static void	(*pan_trigger[Max_RPan_Type])(t_env *) = {
		t_area_wtm, t_area_otm
	};

	return (pan_trigger[env->rpan.type](env));
}

static void		init_trigger_area(t_mousetrack *mtrack)
{
	mtrack->trigger[Map_window] = t_area_mw;
	mtrack->trigger[Map_properties_buttons] = t_area_mpb;
	mtrack->trigger[Inspector] = t_area_i;
	mtrack->trigger[Tools_buttons] = t_area_tb;
	mtrack->trigger[Right_Panel] = t_area_rpan;
}

t_float			snap_f(t_float snap, t_float height)
{
	t_float		mod;

	mod = fmod(snap, height);
	if (mod >= height / 2.0)
		return (snap - mod + height);
	return (snap - mod);
}

t_vec2			vec_snap(t_vec2 snap, t_float height)
{
	return (VEC2_INIT(snap_f(snap.x, height), snap_f(snap.y, height)));
}

static void		mw_object_edit(t_env *env)
{
	t_vec2		coords;
	t_canvas	bounds;

	bounds = get_map_boundaries(env);
	coords = mpos_to_map_coord(bounds, env->mouse.pos, env)
		+ env->mouse.obj_offset;
	if (env->obj.g_snap->val != 0.0 && is_bounded(env->mouse.pos, bounds))
		coords = vec_snap(coords + 0.5, env->obj.g_snap->val) - 0.5;
	env->obj.list[env->mouse.button_index]->pos = coords;
}

static void		u_mw_painter(t_env *env)
{
	toolset_use_fx(env);
}

static void		u_mw_object_edit(t_env *env)
{
	if (env->obj.holding == True)
		return (mw_object_edit(env));
}

static void		u_mw_door(t_env *env)
{
	t_door_edit	*dedit;

	dedit = &env->inspector.door_edit;
	dedit->door_pos = mpos_to_map_index(get_map_boundaries(env), env);
}

static void		u_area_mw(t_env *env)
{
	t_u32		type;

	type = toolset_get_type(&env->toolset);
	if (type >= Max_ToolType_Painter
	|| env->editor.mode == Painter || env->editor.mode == World)
		u_mw_painter(env);
	else if (env->editor.mode == Object_Edit)
		u_mw_object_edit(env);
	else if (env->editor.mode == Door)
		u_mw_door(env);
}

static void		u_area_mpb(t_env *env)
{
	t_u32			b_index;
	t_mprops		*props;

	props = &env->map_properties;
	b_index = env->mouse.button_index;
	if (b_index != Recenter && props->tick % props->speed == 0)
	{
		button_trigger(props->actions[b_index]);
		if (props->tick > props->speed * 2)
			props->speed = 1;
		else if (props->tick >= props->speed)
			props->speed = 5;
	}
	props->tick++;
}

static void		u_area_i(t_env *env)
{
	button_trigger(env->inspector.action[env->editor.mode]);
}

static void		u_area_tb(t_env *env)
{
	(void)env;
}

static void		u_area_rpan(t_env *env)
{
	(void)env;
}

static void		init_update_area(t_mousetrack *mtrack)
{
	mtrack->update[Map_window] = u_area_mw;
	mtrack->update[Map_properties_buttons] = u_area_mpb;
	mtrack->update[Inspector] = u_area_i;
	mtrack->update[Tools_buttons] = u_area_tb;
	mtrack->update[Right_Panel] = u_area_rpan;
}

void			mouse_track_init(t_env *env)
{
		t_mousetrack *mtrack;

		mtrack = &env->mouse;
		ft_bzero(mtrack, sizeof(*mtrack));
		init_get_area(mtrack);
		init_trigger_area(mtrack);
		init_update_area(mtrack);
}
