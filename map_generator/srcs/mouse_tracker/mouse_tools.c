/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:20:05 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:24:24 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

t_ivec2			get_mouse_pos(void)
{
	int			x;
	int			y;

	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	return (IVEC2_INIT(x, y));
}

void			update_mouse_pos(t_env *env)
{
	int			x;
	int			y;

	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	env->mouse.last_pos = env->mouse.pos;
	env->mouse.pos = IVEC2_INIT(x, y);
	env->mouse.rel_pos = env->mouse.pos - env->mouse.last_pos;
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

static void		mouse_setstate_b2(t_env *env, t_mousetrack *tracker,
					t_bool state)
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
		mouse_setstate_b2(env, tracker, state);
}
