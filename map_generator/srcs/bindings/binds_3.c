/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:07:41 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static int	on_mbutton_press(SDL_Event *event, t_env *env)
{
	t_canvas	bounds;

	bounds = get_map_boundaries(env);
	update_mouse_pos(env);
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (env->space == 1)
			SDL_SetRelativeMouseMode(SDL_TRUE);
		mouse_button_setstate(env, 1, True);
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
		mouse_button_setstate(env, 2, True);
	return (1);
}

static int	on_mbutton_release(SDL_Event *event, t_env *env)
{
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		mouse_button_setstate(env, 1, False);
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
		mouse_button_setstate(env, 2, False);
	return (1);
}

static int	on_mouse_wheel(SDL_Event *event, t_env *env)
{
	t_ivec2	mpos;
	int		dir;
	t_panel	*p;

	mpos = get_mouse_pos();
	dir = event->wheel.y < 0 ? 1 : -1;
	env->mouse.wheel = event->wheel.y;
	p = env->rpan.p[env->rpan.type];
	if (panel_isinside(p, mpos))
		panel_change_view(p, dir);
	else if (env->rpan.type == Texture_Panel)
	{
		panel_update_cursor(p, (t_u32)((int)p->cursor + dir));
		env->palette.brush = (int)p->cursor;
	}
	return (1);
}

int			manage_binds(SDL_Event *event, t_env *env)
{
	int		r;

	r = 1;
	if (event->type == SDL_QUIT)
		return (0);
	else if (event->type == SDL_KEYUP)
		return (on_key_release(event, env));
	else if (event->type == SDL_KEYDOWN)
		return (on_key_press(event, env));
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		return (on_mbutton_press(event, env));
	else if (event->type == SDL_MOUSEBUTTONUP)
		return (on_mbutton_release(event, env));
	else if (event->type == SDL_MOUSEWHEEL)
		return (on_mouse_wheel(event, env));
	return (r);
}
