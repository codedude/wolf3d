/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 21:36:34 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static void			draw_mprops(t_env *env, t_mprops *props)
{
	t_u32		i;

	draw_canvas_fill(&env->sdl, &props->anchor,
		&CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), 0x222222);
	i = 0;
	while (i < Max_editor_action)
	{
		button_draw(&env->sdl, &env->cpick, props->actions[i]);
		i++;
	}
}

static void			draw_editor(t_env *env)
{
	t_u32		i;

	draw_canvas_fill(&env->sdl, &env->editor.anchor,
		&CANVAS_INIT(IVEC2_ZERO, IVEC2_ZERO), 0x222222);
	i = 0;
	while (i < Max_EditMod_type)
	{
		button_draw(&env->sdl, &env->cpick, env->editor.switch_b[i]);
		i++;
	}
}

void				draw_ui(t_env *env, t_sdl *sdl)
{
	panel_draw(sdl, &env->cpick, env->rpan.p[env->rpan.type]);
	button_draw(sdl, &env->cpick, env->inspector.action[env->editor.mode]);
	env->inspector.draw[env->editor.mode](env);
	draw_mprops(env, &env->map_properties);
	draw_editor(env);
}
