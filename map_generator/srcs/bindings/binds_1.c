/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   release.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 02:22:10 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

void		manage_down(const Uint8	*state, t_env *env)
{
	int		test;

	env->ctrl = (state[SDL_SCANCODE_LCTRL] != 0);
	if ((test = (state[SDL_SCANCODE_X] != 0)))
		toolset_set_tmp_type(&env->toolset, ZoomIn);
	else if ((test = (state[SDL_SCANCODE_Z] != 0)))
		toolset_set_tmp_type(&env->toolset, ZoomOut);
	else if ((test = (state[SDL_SCANCODE_SPACE] != 0)))
		toolset_set_tmp_type(&env->toolset, Hand);
	else if ((test = (state[SDL_SCANCODE_LALT] != 0)))
		toolset_set_tmp_type(&env->toolset, Picker);
	else if ((test = (state[SDL_SCANCODE_LCTRL] != 0)))
		toolset_set_tmp_type(&env->toolset, SpawnSetter);
	else if ((test = (state[SDL_SCANCODE_LSHIFT] != 0)))
		toolset_set_tmp_type(&env->toolset, Eraser);
	if (test && env->mouse.b1_status == Mouse_Hold
		&& env->editor.mode != Painter && env->editor.mode != World)
		env->mouse.no_trigger = True;
}

int			on_key_release(SDL_Event *event, t_env *env)
{
	if (event->key.keysym.sym == SDLK_ESCAPE)
		return (0);
	else if (event->key.keysym.sym == SDLK_SPACE)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		env->space = False;
	}
	else if (event->key.keysym.sym == SDLK_LALT)
		env->alt = False;
	else if (event->key.keysym.sym == SDLK_LCTRL)
		env->ctrl = False;
	return (1);
}
