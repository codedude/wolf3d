/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trig_rpanels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:42:02 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:51:02 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

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

void			t_area_rpan(t_env *env)
{
	static void	(*pan_trigger[Max_RPan_Type])(t_env *) = {
		t_area_wtm, t_area_otm
	};

	return (pan_trigger[env->rpan.type](env));
}
