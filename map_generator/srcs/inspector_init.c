
#include "gen_env.h"
#include "libft.h"

static void			action_painter(void *v_env)
{
	t_b_select	*selector;
	t_env		*env;

	env = (t_env*)v_env;
	selector = &env->inspector.b_select;
	button_trigger(selector->type_select[env->mouse.button_index]);
}

static void			draw_painter(t_env *env)
{
	t_u32		i;
	t_button	*b;
	t_b_select	*selector;

	selector = &env->inspector.b_select;
	i = 0;
	while (i < Max_Brush_Buttons)
	{
		b = selector->type_select[i];
		button_draw(env, b);
		i++;
	}
}

static t_bool		gb_painter(t_env *env)
{
	t_u32		i;
	t_button	*b;
	t_b_select	*selector;

	selector = &env->inspector.b_select;
	i = 0;
	while (i < Max_Brush_Buttons)
	{
		b = selector->type_select[i];
		if (button_hover(b, env->mouse.pos))
		{
			selector->type_save = selector->type;
			env->mouse.button_index = i;
			return (True);
		}
		i++;
	}
	return (False);
}

void				env_change_brush(t_env *env, t_u32 type)
{
	t_button	*b;
	t_b_select	*selector;
	t_u32		i;

	selector = &env->inspector.b_select;
	i = 0;
	while (i < Max_brush_type)
	{
		b = selector->type_select[i];
		b->is_active = (type == i);
		i++;
	}
	selector->type = (int)type;
}

static void			change_brush(void *v_env)
{
	t_env		*env;

	env = (t_env*)v_env;
	env_change_brush(env, env->mouse.button_index);
}

static void			init_xy(t_sdl *sdl, int x[2], int y[2])
{
	x[0] = ipercent_of(sdl->width, B_TYPE_B_POS_X);
	x[1] = ipercent_of(sdl->width, B_TYPE_B_POS_X2);
	y[0] = ipercent_of(sdl->height, B_TYPE_B_POS_Y);
	y[1] = ipercent_of(sdl->height, B_TYPE_B_OFF_Y);
}

static int 			init_type_selectors(t_env *env, t_b_select *selector)
{
	t_button	*b;
	t_canvas	anchor;
	int			x[2];
	int			y[2];
	t_u32		i;

	i = 0;
	anchor.size.x = ipercent_of(env->sdl.width, B_TYPE_B_SIZE_X);
	anchor.size.y = ipercent_of(env->sdl.height, B_TYPE_B_SIZE_Y);
	init_xy(&env->sdl, x, y);
	while (i < Max_brush_type)
	{
		anchor.pos = IVEC2_INIT(x[i % 2], y[0] + y[1] * ((int)i / 2));
		b = button_new(anchor, NULL, env, change_brush);
		if (!b)
			return (ERROR);
		anchor.pos = 0;
		texdata_fill_rect(b->tex, anchor.size, anchor, 0xffffff);
		selector->type_select[i] = b;
		i++;
	}
	selector->type_select[0]->is_active = True;
	selector->type = Pencil;
	return (SUCCESS);
}

static void			selector_set_mode(void *v_env)
{
	t_env		*env;
	t_b_select	*selector;

	env = (t_env*)v_env;
	selector = &env->inspector.b_select;
	if (env->mouse.button_index == Brush_Mode)
	{
		toolset_set_type(&env->toolset, Brush);
		selector->type_select[Brush_Mode]->is_active = True;
		selector->type_select[Eraser_Mode]->is_active = False;
	}
	else if (env->mouse.button_index == Eraser_Mode)
	{
		toolset_set_type(&env->toolset, Eraser);
		selector->type_select[Brush_Mode]->is_active = False;
		selector->type_select[Eraser_Mode]->is_active = True;
	}
}

static int 			init_mode_selectors(t_env *env, t_b_select *selector,
						t_canvas i_anch)
{
	t_canvas	anchor;
	t_ivec2		ref;
	t_button	*b;

	ref = i_anch.pos + i_anch.size / 2;
	anchor = selector->type_select[0]->anchor;
	anchor.pos.y = (ref.y + (ref.y - anchor.pos.y)) - anchor.size.y;
	anchor.pos.x = selector->type_select[0]->anchor.pos.x;
	if (!(b = button_new(anchor, NULL, env, selector_set_mode)))
		return (ERROR);
	selector->type_select[Brush_Mode] = b;
	texdata_fill_rect(b->tex, anchor.size,
			CANVAS_INIT(0, anchor.size), 0xffffff);
	b->is_active = True;
	anchor.pos.x = selector->type_select[1]->anchor.pos.x;
	if (!(b = button_new(anchor, NULL, env, selector_set_mode)))
		return (ERROR);
	selector->type_select[Eraser_Mode] = b;
	texdata_fill_rect(b->tex, anchor.size,
			CANVAS_INIT(0, anchor.size), 0xffffff);
	return (SUCCESS);
}

static int			create_painter_inpector(t_env *env, t_canvas i_anch)
{
	t_button	*b;

	if (init_type_selectors(env, &env->inspector.b_select) == ERROR
		|| init_mode_selectors(env, &env->inspector.b_select, i_anch) == ERROR
		|| !(b = button_new(i_anch, NULL, env, action_painter)))
		return (ERROR);
	texdata_fill_rect(b->tex, i_anch.size,
					CANVAS_INIT(0, i_anch.size), 0xacacac);
	env->inspector.action[Painter] = b;
	env->inspector.get_button[Painter] = gb_painter;
	env->inspector.draw[Painter] = draw_painter;
	return (SUCCESS);
}

static void			draw_cf_prev(t_env *env, t_world_i *w_inf)
{
	t_u32		id;

	id = w_inf->id[WButton_Ceil];
	draw_tex(env, &env->sdl.tex_walls[id], False, w_inf->prev[WButton_Ceil]);
	id = w_inf->id[WButton_Floor];
	draw_tex(env, &env->sdl.tex_walls[id], False, w_inf->prev[WButton_Floor]);
}

static void			draw_world(t_env *env)
{
	t_world_i	*w_inf;

	w_inf = &env->inspector.world;
	draw_player_radar(env, &w_inf->radar);
	draw_cf_prev(env, w_inf);
	checkbox_draw(env, w_inf->cbox_ceil);
}

static void			action_player_radar(t_env *env, t_radar *radar)
{
	t_ivec2		mpos;
	t_button	*b;

	b = env->inspector.action[World];
	mpos = env->mouse.pos - radar->center;
	env->spawn_rotation = (int)(atan2(mpos.y, mpos.x) * 180.0 / M_PI) + 180;
}

static void			action_world(void *v_env)
{
	t_env		*env;
	t_world_i	*w_inf;
	t_u32		b_index;

	env = (t_env*)v_env;
	w_inf = &env->inspector.world;
	b_index = env->mouse.button_index;
	if (b_index == WButton_Radar)
		action_player_radar(env, &w_inf->radar);
	else if (env->mouse.b1_status == Mouse_Release)
	{
		if (b_index == WButton_Ceil)
			w_inf->id[WButton_Ceil] = env->rpan.p[Texture_Panel]->cursor;
		else if (b_index == WButton_Floor)
			w_inf->id[WButton_Floor] = env->rpan.p[Texture_Panel]->cursor;
		else if (b_index == WButton_Draw_Ceil)
			checkbox_clic(w_inf->cbox_ceil);
	}
}

static t_bool		gb_player_radar(t_env *env, t_radar *radar)
{
	t_ivec2		rpos;

	rpos = env->mouse.record_pos_b - radar->center;
	return (rpos.x * rpos.x + rpos.y * rpos.y < radar->squ_radius);
}

static t_bool		gb_world(t_env *env)
{
	t_world_i	*w_inf;
	int			button;

	w_inf = &env->inspector.world;
	button = -1;
	if (is_bounded(env->mouse.pos, w_inf->prev[WButton_Ceil]))
		button = WButton_Ceil;
	else if (is_bounded(env->mouse.pos, w_inf->prev[WButton_Floor]))
		button = WButton_Floor;
	else if (gb_player_radar(env, &w_inf->radar) == True)
		button = WButton_Radar;
	else if (checkbox_hover(w_inf->cbox_ceil, env->mouse.pos))
		button = WButton_Draw_Ceil;
	else
		return (False);
	env->mouse.button_index = (t_u32)button;
	return (True);
}

static void			init_radar(t_env *env, t_radar *radar, t_canvas i_anch)
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

static void			init_cf_prev(t_env *env, t_world_i *w_inf, t_canvas i_anch)
{
	t_canvas	anchor;
	int			offset;
	t_button	*b;

	b = env->inspector.action[World];
	anchor.size = env->rpan.p[Texture_Panel]->elem_anchor.size;
	offset = (int)((t_float)anchor.size.x * 0.1);
	anchor.pos.y = w_inf->radar.center.y + (int)(w_inf->radar.f_radius * 1.5);
	anchor.pos.x = w_inf->radar.center.x - (anchor.size.x + offset);
	w_inf->prev[WButton_Ceil] = anchor;
	anchor.pos.x = w_inf->radar.center.x + offset;
	w_inf->prev[WButton_Floor] = anchor;
	anchor.pos -= i_anch.pos;
	texdata_fill_rect(b->tex, i_anch.size, anchor, 0x757575);
	anchor.pos.x = (w_inf->radar.center.x - (anchor.size.x + offset))
			- i_anch.pos.x;
	texdata_fill_rect(b->tex, i_anch.size, anchor, 0x757575);
}

int			gstate_draw_ceil(void *v_env)
{
	t_env		*env;

	env = (t_env*)v_env;
	return ((int)env->inspector.world.draw_ceil);
}

void		rstate_draw_ceil(void *v_env)
{
	t_env 		*env;
	t_world_i	*w_inf;

	env = (t_env*)v_env;
	w_inf = &env->inspector.world;
	w_inf->draw_ceil = !w_inf->draw_ceil;
}

int				init_cbox_draw_ceil(t_env *env, t_sdl *sdl,
					t_world_i *w_inf, t_canvas i_anch)
{
	t_canvas	anchor;

	if (sdl->width < sdl->height)
		anchor.size = ipercent_of(sdl->width, CB_SOL_S_SIZE);
	else
		anchor.size = ipercent_of(sdl->height, CB_SOL_S_SIZE);
	anchor.pos.x = i_anch.pos.x + i_anch.size.x;
	anchor.pos.x -= (int)(anchor.size.x * 1.5);
	anchor.pos.y = w_inf->prev[WButton_Ceil].pos.y
				+ w_inf->prev[WButton_Ceil].size.y;
	anchor.pos.y += (int)(anchor.size.y * 0.5);
	if (!(w_inf->cbox_ceil = checkbox_new(anchor, NULL)))
		return (ERROR);
	checkbox_setup(w_inf->cbox_ceil, env, rstate_draw_ceil, gstate_draw_ceil);
	return (SUCCESS);
}

static int			create_world_inpector(t_env *env, t_canvas i_anch)
{
	t_world_i	*w_inf;
	t_button	*b;

	w_inf = &env->inspector.world;
	if (!(b = button_new(i_anch, NULL, env, action_world)))
		return (ERROR);
	env->inspector.action[World] = b;
	env->inspector.draw[World] = draw_world;
	env->inspector.get_button[World] = gb_world;
	init_radar(env, &w_inf->radar, i_anch);
	init_cf_prev(env, w_inf, i_anch);
	init_cbox_draw_ceil(env, &env->sdl, w_inf, i_anch);
	if (env->loaded == False)
	{
		w_inf->id[WButton_Ceil] = 0;
		w_inf->id[WButton_Floor] = 0;
		env->inspector.world.draw_ceil = False;
	}
	return (SUCCESS);
}

static void			update_obj_y(t_env *env, t_object_edit *oedit,
						t_object_e *obj)
{
	t_float			y;
	t_float			hsize_y;

	hsize_y = oedit->bg_prev.size.y / 2.0;
	y = env->mouse.pos.y - (oedit->bg_prev.pos.y + hsize_y);
	y = clamp_float(y, -hsize_y, hsize_y);
	obj->y_pos = -y / hsize_y;
	if (env->obj.g_snap->val != 0.0)
		obj->y_pos = snap_f(obj->y_pos, env->obj.g_snap->val);
}

static void			action_update_obj(t_env *env)
{
	t_object_edit	*oedit;
	t_object_e		*obj;
	t_ivec2			proj;
	t_float			dist;
	t_float			res;

	oedit = &env->obj.edit;
	obj = env->obj.list[oedit->selected];
	if (!env->ctrl)
		return (update_obj_y(env, oedit, obj));
	proj = env->mouse.pos - env->mouse.record_pos_b;
	dist = sqrt((t_float)(proj.x * proj.x + proj.y * proj.y));
	res = proj.x / (t_float)oedit->bg_prev.size.x * -1;
	obj->scale = clamp_float(res + oedit->saved_scale, 0.1, 2.0);
	if (env->obj.g_snap->val != 0.0)
	{
		obj->scale = snap_f(obj->scale, env->obj.g_snap->val);
		obj->scale = clamp_float(obj->scale, env->obj.g_snap->val, 2.0);
	}

}

static void			action_object_edit(void *v_env)
{
	t_env		*env;

	env = (t_env*)v_env;
	if (env->mouse.button_index == Grid_Snap)
		slider_update_bypos(env->obj.g_snap, env->mouse.pos);
	else if (env->mouse.button_index == Obj_Preview)
		action_update_obj(env);
	else if (env->mouse.b1_status == Mouse_Release)
	{
		if (env->mouse.button_index == Box_Is_Solid
			&& checkbox_hover(env->obj.cbox_solid, env->mouse.pos))
			checkbox_clic(env->obj.cbox_solid);
	}
}

static void			draw_y_line(t_env *env, int y)
{
	t_color		c;
	t_ivec2		px1;
	int			px2;
	int			i;

	c.rgba = 0x2BD929;
	i = -1;
	while (i < 1)
	{
		px1.x = env->obj.edit.bg_prev.pos.x;
		px1.y = y + i;
		px2 = px1.x + env->obj.edit.bg_prev.size.x;
		env_set_color(env, c.rgba);
		draw_hline(env, px1, px2);
		i++;
	}
}

static void			draw_obj_selected(t_env *env)
{
	t_object_e	*obj;
	t_canvas	tex_anchor;
	t_panel		*p;

	obj = env->obj.list[env->obj.edit.selected];
	env_set_canvas(env, env->obj.edit.bg_prev);
	p = env->rpan.p[Object_Panel];
	tex_anchor.size.x = (int)(env->obj.edit.tex_prev.size.x * obj->scale * 0.8);
	tex_anchor.size.y = (int)(env->obj.edit.tex_prev.size.y * obj->scale * 0.8);
	tex_anchor.pos = env->obj.edit.bg_prev.pos;
	tex_anchor.pos += (env->obj.edit.bg_prev.size - tex_anchor.size) / 2;
	tex_anchor.pos.y -= (int)(env->obj.edit.bg_prev.size.y / 2.0 * obj->y_pos);
	if (env->mouse.b1 == True && env->mouse.area == Inspector
	&& env->mouse.button_index == Obj_Preview)
		draw_y_line(env, tex_anchor.pos.y + tex_anchor.size.y / 2);
	env_set_transparency(env, 0x0);
	draw_tex(env, &env->sdl.tex_sprites[obj->id], False, tex_anchor);
	env_unset_transparency(env);
	env_unset_canvas(env);
}

static void			draw_object_edit(t_env *env)
{
	if (env->obj.edit.selected != -1)
		draw_obj_selected(env);
	checkbox_draw(env, env->obj.cbox_solid);
	slider_draw(env, env->obj.g_snap);
}

static t_bool		gb_object_edit(t_env *env)
{
	t_object_edit	*oedit;

	oedit = &env->obj.edit;
	if (slider_hover(env->obj.g_snap, env->mouse.pos))
		env->mouse.button_index = Grid_Snap;
	else if (checkbox_hover(env->obj.cbox_solid, env->mouse.pos))
		env->mouse.button_index = Box_Is_Solid;
	else if (oedit->selected != -1
		&& is_bounded(env->mouse.pos, oedit->bg_prev))
	{
		env->mouse.button_index = Obj_Preview;
		oedit->saved_scale = env->obj.list[oedit->selected]->scale;
	}
	else
		return (False);
	return (True);
}

static void			init_object_edit(t_env *env, t_object_edit *oedit,
								t_button *b, t_canvas i_anch)
{
	t_panel		*p;

	p = env->rpan.p[Object_Panel];
	oedit->bg_prev.size.x = ipercent_of(i_anch.size.x, 95);
	oedit->bg_prev.size.y = ipercent_of(i_anch.size.y, 45);
	oedit->bg_prev.pos.x = i_anch.size.x / 2 - oedit->bg_prev.size.x / 2;
	oedit->bg_prev.pos.y = ipercent_of(i_anch.size.y, 5);
	texdata_fill_rect(b->tex, i_anch.size, env->obj.edit.bg_prev,
				0x484848);
	oedit->bg_prev.pos += i_anch.pos;
	oedit->tex_prev.size = p->elem_anchor.size;
	oedit->tex_prev.pos = oedit->bg_prev.size / 2 - oedit->tex_prev.size / 2;
	oedit->tex_prev.pos += oedit->bg_prev.pos;
}

static int			create_object_edit_inpector(t_env *env, t_canvas i_anch)
{
	t_button	*b;

	init_objects_tools(&env->obj, &env->sdl, env);
	if (!(b = button_new(i_anch, NULL, env, action_object_edit)))
		return (ERROR);
	env->inspector.action[Object_Edit] = b;
	env->inspector.get_button[Object_Edit] = gb_object_edit;
	env->inspector.draw[Object_Edit] = draw_object_edit;
	init_object_edit(env, &env->obj.edit, b, i_anch);
	return (SUCCESS);
}

static void			action_door(void *v_env)
{
	t_door_edit	*dedit;
	t_env		*env;
	t_entity	*ent;
	t_u32		index;

	env = (t_env*)v_env;
	dedit = &env->inspector.door_edit;
	ent = dedit->selected;
	if (ent == NULL || env->mouse.b1_status != Mouse_Release)
		return ;
	index = env->mouse.button_index;
	if (index == Door_Tex)
		ent->tex_id = (int)env->rpan.p[Texture_Panel]->cursor;
	else if (index == Side_Tex)
		ent->e.door->tex_wall_id = (int)env->rpan.p[Texture_Panel]->cursor;
	else if (index == Item_Prev)
		dedit->mode = !dedit->mode;

}

static void			draw_ds_prev(t_env *env, t_door_edit *dedit, t_entity *ent)
{
	int			id;

	id = ent->tex_id;
	draw_tex(env, &env->sdl.tex_walls[id], False, dedit->prev[Door_Tex]);
	id = ent->e.door->tex_wall_id;
	draw_tex(env, &env->sdl.tex_walls[id], False, dedit->prev[Side_Tex]);
	id = ent->e.door->item_id;
	if (id != -1)
		draw_tex(env, &env->sdl.tex_sprites[env->obj.list[id]->id], False,
			dedit->prev[Item_Prev]);
}

static void			draw_door_centerl(t_env *env, t_canvas anch, int dim,
						void (*drawline_ptr)(t_env *, t_ivec2, int))
{
	t_ivec2		pos;
	int			to;
	int			p2;
	int			other_dim;

	other_dim = dim == 1 ? 0 : 1;
	to = ipercent_of(anch.size[dim], 5);
	pos[dim] = anch.pos[dim] + (anch.size[dim] - to) / 2;
	pos[other_dim] = anch.pos[other_dim];
	p2 = anch.pos[other_dim] + anch.size[other_dim];
	to = pos[dim] + to;
	while (pos[dim] < to)
	{
		drawline_ptr(env, pos, p2);
		pos[dim]++;
	}
}

static void			draw_door_prev(t_env *env, t_door_edit *dedit,
						t_entity *ent)
{
	t_canvas	anch;

	anch = dedit->prev[Door_Prev];
	if (door_check_neighbour(env->map_info.map, ent))
		env_set_color(env, 0xFFFFFF);
	else
		env_set_color(env, 0xFF0000);
	if (ent->e.door->orientation == Dir_Horizontal)
		draw_door_centerl(env, anch, 1, draw_hline);
	else
		draw_door_centerl(env, anch, 0, draw_vline);
}

static void			draw_door(t_env *env)
{
	t_door_edit		*dedit;
	t_entity		*ent;
	t_canvas		anch;
	int				i;

	dedit = &env->inspector.door_edit;
	ent = dedit->selected;
	if (ent == NULL)
		return ;
	draw_ds_prev(env, dedit, ent);
	draw_door_prev(env, dedit, ent);
	if (dedit->mode == Object_Select)
	{
		anch = dedit->prev[Item_Prev];
		i = ipercent_of(anch.size.x, 5);
		while (i--)
		{
			draw_canvas_border(&env->sdl, anch, CANVAS_INIT(0, 0), 0xFFFFFF);
			anch.pos += 1;
			anch.size -= 2;
		}
	}
}

static t_bool		gb_door(t_env *env)
{
	t_door_edit		*dedit;
	t_u32			i;

	dedit = &env->inspector.door_edit;
	i = 0;
	while (i < Max_Door_Area)
	{
		if (is_bounded(env->mouse.pos, dedit->prev[i]))
		{
			env->mouse.button_index = i;
			return (True);
		}
		i++;
	}
	return (False);
}

static void			init_tex_bg(t_env *env, t_door_edit *dedit,
						t_canvas i_anch)
{
	t_canvas	anchor;
	t_u32	i;
	t_button	*b;

	b = env->inspector.action[Door];
	i = 0;
	while (i < Max_Door_Area)
	{
		anchor.size = dedit->prev[i].size;
		anchor.pos = dedit->prev[i].pos - i_anch.pos;
		texdata_fill_rect(b->tex, i_anch.size, anchor, 0x757575);
		i++;
	}
}

static void			init_tex_prev(t_env *env, t_door_edit *dedit,
						t_canvas i_anch)
{
	t_ivec2		elem_size;
	t_canvas	anchor;
	int			offset;

	elem_size = env->rpan.p[Texture_Panel]->elem_anchor.size;
	anchor.size = elem_size;
	offset = (int)((t_float)anchor.size.x * 0.1);
	anchor.pos.y = i_anch.pos.y + offset * 2;
	anchor.pos.x = i_anch.pos.x + i_anch.size.x / 2 - (anchor.size.x + offset);
	dedit->prev[Door_Tex] = anchor;
	anchor.pos.x = i_anch.pos.x + i_anch.size.x / 2 + offset;
	dedit->prev[Side_Tex] = anchor;
	anchor.size = ipercent_of(i_anch.size.x, 66);
	anchor.pos.y = dedit->prev[Door_Tex].pos.y + ipercent_of(i_anch.pos.x, 10);
	anchor.pos.x = i_anch.pos.x + i_anch.size.x / 2 - anchor.size.x / 2;
	dedit->prev[Door_Prev] = anchor;
	anchor.size = elem_size;
	anchor.pos.y = i_anch.pos.y + i_anch.size.y - offset * 2 - anchor.size.y;
	anchor.pos.x = i_anch.pos.x + i_anch.size.x / 2 - anchor.size.x / 2;
	dedit->prev[Item_Prev] = anchor;
	init_tex_bg(env, dedit, i_anch);
}

static void			init_door_areas(t_env *env, t_door_edit *dedit,
						t_canvas i_anch)
{
	init_tex_prev(env, dedit, i_anch);
	dedit->selected = NULL;
	dedit->mode = Door_Select;
}

static int			create_door_inpector(t_env *env, t_canvas i_anch)
{
	t_button	*b;

	if (!(b = button_new(i_anch, NULL, env, action_door)))
		return (ERROR);
	env->inspector.action[Door] = b;
	env->inspector.get_button[Door] = gb_door;
	env->inspector.draw[Door] = draw_door;
	init_door_areas(env, &env->inspector.door_edit, i_anch);
	return (SUCCESS);
}

int					env_create_inspect(t_env *env)
{
	t_canvas	anchor;

	anchor.size.x = ipercent_of(env->sdl.width, INSPECTOR_SIZE_X);
	anchor.size.y = ipercent_of(env->sdl.height, INSPECTOR_SIZE_Y);
	anchor.pos.y = ipercent_of(env->sdl.height, INSPECTOR_TOP_POS_Y);
	anchor.pos.x = ipercent_of(env->sdl.width, INSPECTOR_TOP_POS_X);
	if (create_painter_inpector(env, anchor) == ERROR
	|| create_world_inpector(env, anchor) == ERROR
	|| create_door_inpector(env, anchor) == ERROR
	|| create_object_edit_inpector(env, anchor) == ERROR)
		return (ERROR);
	env->editor.mode = Painter;
	return (env_create_mprops(env));
}
