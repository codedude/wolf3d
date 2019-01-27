/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:19:19 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:46:25 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

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

void			init_update_area(t_mousetrack *mtrack)
{
	mtrack->update[Map_window] = u_area_mw;
	mtrack->update[Map_properties_buttons] = u_area_mpb;
	mtrack->update[Inspector] = u_area_i;
	mtrack->update[Tools_buttons] = u_area_tb;
	mtrack->update[Right_Panel] = u_area_rpan;
}
