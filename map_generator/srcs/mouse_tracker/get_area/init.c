/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:22:09 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:47:57 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

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

void			init_get_area(t_mousetrack *mtrack)
{
	mtrack->get_area[Map_window] = g_area_mw;
	mtrack->get_area[Map_properties_buttons] = g_area_mpb;
	mtrack->get_area[Inspector] = g_area_i;
	mtrack->get_area[Tools_buttons] = g_area_tb;
	mtrack->get_area[Right_Panel] = g_area_rpan;
}
