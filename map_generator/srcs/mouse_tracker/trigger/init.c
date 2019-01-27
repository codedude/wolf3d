/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:29:36 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:50:07 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

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

void			init_trigger_area(t_mousetrack *mtrack)
{
	mtrack->trigger[Map_window] = t_area_mw;
	mtrack->trigger[Map_properties_buttons] = t_area_mpb;
	mtrack->trigger[Inspector] = t_area_i;
	mtrack->trigger[Tools_buttons] = t_area_tb;
	mtrack->trigger[Right_Panel] = t_area_rpan;
}
