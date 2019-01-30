/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:48:55 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:11:47 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

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

static int			init_mode_selectors(t_env *env, t_b_select *selector,
						t_canvas i_anch)
{
	t_canvas	anchor;
	t_ivec2		ref;
	t_button	*b;

	ref = i_anch.pos + i_anch.size / 2;
	anchor = selector->type_select[0]->anchor;
	anchor.pos.y = (ref.y + (ref.y - anchor.pos.y)) - anchor.size.y;
	anchor.pos.x = selector->type_select[0]->anchor.pos.x;
	if (!(b = button_new(anchor, &env->ui_tex[UI_Painter_Brush],
						env, selector_set_mode)))
		return (ERROR);
	selector->type_select[Brush_Mode] = b;
	b->is_active = True;
	anchor.pos.x = selector->type_select[1]->anchor.pos.x;
	if (!(b = button_new(anchor, &env->ui_tex[UI_Painter_Eraser],
						env, selector_set_mode)))
		return (ERROR);
	selector->type_select[Eraser_Mode] = b;
	return (SUCCESS);
}

int					create_painter_inpector(t_env *env, t_canvas i_anch)
{
	t_button	*b;

	if (init_type_selectors(env, &env->inspector.b_select) == ERROR
		|| init_mode_selectors(env, &env->inspector.b_select, i_anch) == ERROR
		|| !(b = button_new(i_anch, &env->ui_tex[UI_Painter_BG],
				env, inspector_action_painter)))
		return (ERROR);
	b->is_active = True;
	env->inspector.action[Painter] = b;
	env->inspector.get_button[Painter] = inspector_gb_painter;
	env->inspector.draw[Painter] = inspector_draw_painter;
	return (SUCCESS);
}
