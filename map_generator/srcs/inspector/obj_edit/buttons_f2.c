/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_f2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:53:29 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 23:40:11 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void		update_obj_y(t_env *env, t_object_edit *oedit, t_object_e *obj)
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

static void		action_update_obj(t_env *env)
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

void			inspector_action_object_edit(void *v_env)
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

t_bool			inspector_gb_object_edit(t_env *env)
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
