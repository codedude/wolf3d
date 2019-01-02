
#include "gen_env.h"
#include "libft.h"

static void			action_brush_select(void *v_env)
{
	t_b_select	*selector;
	t_env		*env;

	env = (t_env*)v_env;
	selector = &env->inspector.b_select;
	button_trigger(selector->type_select[selector->type]);
}

static void			draw_brush_select(t_env *env)
{
	t_u32		i;
	t_button	*b;
	t_b_select	*selector;

	selector = &env->inspector.b_select;
	i = 0;
	while (i < Max_brush_type)
	{
		b = selector->type_select[i];
		button_draw(env, b);
		i++;
	}
}

static t_bool		gb_brush_select(t_env *env)
{
	t_u32		i;
	t_button	*b;
	t_b_select	*selector;

	selector = &env->inspector.b_select;
	i = 0;
	while (i < Max_brush_type)
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

static int			create_brush_select_inpector(t_env *env, t_canvas i_anch)
{
	t_button	*b;

	if (!(b = button_new(i_anch, NULL, env, action_brush_select)))
		return (ERROR);
	texdata_fill_rect(b->tex, i_anch.size,
					CANVAS_INIT(0, i_anch.size), 0xacacac);
	env->inspector.action[Brush_Select] = b;
	env->inspector.get_button[Brush_Select] = gb_brush_select;
	env->inspector.draw[Brush_Select] = draw_brush_select;
	return (SUCCESS);
}

static void			action_player_radar(void *v_env)
{
	t_ivec2		mpos;
	t_radar		*radar;
	t_env		*env;
	t_button	*b;

	env = (t_env*)v_env;
	radar = &env->inspector.radar;
	b = env->inspector.action[Player_Radar];
	mpos = env->mouse.pos - radar->center;
	env->spawn_rotation = (int)(atan2(mpos.y, mpos.x) * 180.0 / M_PI) + 180;
}

static t_bool		gb_player_radar(t_env *env)
{
	t_radar		*radar;
	t_ivec2		rpos;

	radar = &env->inspector.radar;
	rpos = env->mouse.record_pos_b - radar->center;
	return (rpos.x * rpos.x + rpos.y * rpos.y < radar->squ_radius);
}

static int			create_player_radar_inpector(t_env *env, t_canvas i_anch)
{
	t_button	*b;
	t_radar		*radar;

	radar = &env->inspector.radar;
	if (!(b = button_new(i_anch, NULL, env, action_player_radar)))
		return (ERROR);
	texdata_fill_rect(b->tex, i_anch.size, CANVAS_INIT(0, i_anch.size),
					0x424242);
	radar->f_radius = (t_float)i_anch.size.x / 2.0;
	radar->center = (int)radar->f_radius;
	radar->center.y += (int)(radar->f_radius * 0.2);
	texdata_draw_circle_filled(b->tex, CANVAS_INIT(radar->center, i_anch.size)
					, (t_float)i_anch.size.x / 2.0, 0xababab);
	radar->center += i_anch.pos;
	radar->radius = (int)radar->f_radius;
	radar->vlines_height = (t_float)i_anch.size.x * 0.51;
	radar->squ_radius = radar->radius * radar->radius;
	radar->triangle_cdist = (t_float)i_anch.size.x * 0.25;
	radar->gizmo_rad = (int)((i_anch.size.x + 1) / 2.0);
	env->inspector.action[Player_Radar] = b;
	env->inspector.draw[Player_Radar] = draw_player_radar;
	env->inspector.get_button[Player_Radar] = gb_player_radar;
	return (SUCCESS);
}

static void			update_obj_y(t_env *env)
{
	t_object_edit	*oedit;
	t_object		*obj;
	t_float			y;
	t_float			hsize_y;

	oedit = &env->obj.edit;
	obj = env->obj.list[oedit->selected];
	hsize_y = oedit->bg_prev.size.y / 2.0;
	y = env->mouse.pos.y - (oedit->bg_prev.pos.y + hsize_y);
	y = clamp_float(y, -hsize_y, hsize_y);
	obj->y_pos = -y / hsize_y;
	if (env->obj.g_snap->val != 0.0)
		obj->y_pos = snap_f(obj->y_pos, env->obj.g_snap->val);
}

static void			action_object_edit(void *v_env)
{
	t_env		*env;

	env = (t_env*)v_env;
	if (env->mouse.button_index == Grid_Snap)
		slider_update_bypos(env->obj.g_snap, env->mouse.pos);
	else if (env->mouse.button_index == Obj_Preview)
		update_obj_y(env);
	else if (env->mouse.b1_status == Mouse_Release
		&& env->mouse.button_index == Box_Is_Solid
		&& checkbox_hover(env->obj.cbox_solid, env->mouse.pos))
		checkbox_clic(env->obj.cbox_solid);
}

static void			draw_y_line(t_env *env, t_object *obj, int y)
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
	t_object	*obj;
	t_canvas	tex_anchor;

	obj = env->obj.list[env->obj.edit.selected];
	tex_anchor = env->obj.edit.tex_prev;
	tex_anchor.pos.y -= (int)((env->obj.edit.bg_prev.size.y - tex_anchor.size.y)
					/ 2.0 * obj->y_pos);
	if (env->mouse.b1 == True && env->mouse.area == Inspector
	&& env->mouse.button_index == Obj_Preview)
		draw_y_line(env, obj, tex_anchor.pos.y + tex_anchor.size.y / 2);
	env_set_transparency(env, 0x0);
	draw_tex(env, env->obj.pan->elem_tex[obj->id], False, tex_anchor);
	env_unset_transparency(env);
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
	if (slider_hover(env->obj.g_snap, env->mouse.pos))
	{
		env->mouse.button_index = Grid_Snap;
		return (True);
	}
	else if (checkbox_hover(env->obj.cbox_solid, env->mouse.pos))
	{
		env->mouse.button_index = Box_Is_Solid;
		return (True);
	}
	else if (env->obj.edit.selected != -1
		&& is_bounded(env->mouse.pos, env->obj.edit.bg_prev))
	{
		env->mouse.button_index = Obj_Preview;
		return (True);
	}
	return (False);
}

static void			init_object_edit(t_env *env, t_object_edit *oedit,
								t_button *b, t_canvas i_anch)
{
	oedit->bg_prev.size.x = ipercent_of(i_anch.size.x, 95);
	oedit->bg_prev.size.y = ipercent_of(i_anch.size.y, 45);
	oedit->bg_prev.pos.x = i_anch.size.x / 2 - oedit->bg_prev.size.x / 2;
	oedit->bg_prev.pos.y = ipercent_of(i_anch.size.y, 5);
	texdata_fill_rect(b->tex, i_anch.size, env->obj.edit.bg_prev,
				0x484848);
	oedit->bg_prev.pos += i_anch.pos;
	oedit->tex_prev.size = env->obj.pan->elem_anchor.size;
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

int					env_create_inspect(t_env *env)
{
	t_canvas	anchor;

	anchor.size.x = ipercent_of(env->sdl.width, INSPECTOR_SIZE_X);
	anchor.size.y = ipercent_of(env->sdl.height, INSPECTOR_SIZE_Y);
	anchor.pos.y = ipercent_of(env->sdl.height, INSPECTOR_TOP_POS_Y);
	anchor.pos.x = ipercent_of(env->sdl.width, INSPECTOR_TOP_POS_X);
	if (create_brush_select_inpector(env, anchor) == ERROR
	|| create_player_radar_inpector(env, anchor) == ERROR
	|| create_object_edit_inpector(env, anchor) == ERROR)
		return (ERROR);
	env->inspector.mod = Brush_Select;
	return (env_create_mprops(env));
}
