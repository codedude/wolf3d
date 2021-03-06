/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:48:55 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 03:49:59 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void			inspector_action_painter(void *v_env)
{
	t_b_select	*selector;
	t_env		*env;

	env = (t_env*)v_env;
	selector = &env->inspector.b_select;
	button_trigger(selector->type_select[env->mouse.button_index]);
}

void			inspector_draw_painter(t_env *env)
{
	t_b_select		*selector;
	t_sdl			*sdl;
	t_color_pick	*cpick;

	selector = &env->inspector.b_select;
	sdl = &env->sdl;
	cpick = &env->cpick;
	button_draw(sdl, cpick, selector->type_select[selector->type]);
	if (env->toolset.type == Brush)
		button_draw(sdl, cpick, selector->type_select[Brush_Mode]);
	else
		button_draw(sdl, cpick, selector->type_select[Eraser_Mode]);
}

t_bool			inspector_gb_painter(t_env *env)
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
