/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binds_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 02:31:22 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

int			on_key_press_5(SDL_Event *event, t_env *env)
{
	if (event->key.keysym.sym == SDLK_r)
		map_update_center(env);
	else if (event->key.keysym.sym == SDLK_y)
		mprops_act_size_x_up(env);
	else if (event->key.keysym.sym == SDLK_t)
		mprops_act_size_x_down(env);
	else if (event->key.keysym.sym == SDLK_h)
		mprops_act_size_y_up(env);
	else if (event->key.keysym.sym == SDLK_g)
		mprops_act_size_y_down(env);
	return (1);
}

int			on_key_press_4(SDL_Event *event, t_env *env)
{
	if (event->key.keysym.sym == SDLK_c)
		button_setactive(env->editor.switch_b[Painter], True);
	else if (event->key.keysym.sym == SDLK_v)
		button_setactive(env->editor.switch_b[World], True);
	else if (event->key.keysym.sym == SDLK_b)
		button_setactive(env->editor.switch_b[Door], True);
	else if (event->key.keysym.sym == SDLK_n)
		button_setactive(env->editor.switch_b[Object_Edit], True);
	else
		return (on_key_press_5(event, env));
	return (1);
}

int			on_key_press_3(SDL_Event *event, t_env *env)
{
	if (event->key.keysym.sym == SDLK_p)
	{
		ft_putnbrf_fd(env->map_info.zoom, 1, 2);
		ft_putchar('\n');
	}
	else if (event->key.keysym.sym == SDLK_DELETE)
	{
		if (env->editor.mode == Object_Edit)
		{
			if (env->obj.edit.selected != -1)
				object_destroy(&env->obj, (t_u32)env->obj.edit.selected);
		}
		else if (env->editor.mode == Door)
			door_destroy_selected(env, &env->inspector.door_edit);
	}
	else
		return (on_key_press_4(event, env));
	return (1);
}

int			on_key_press_2(SDL_Event *event, t_env *env)
{
	if (event->key.keysym.sym == SDLK_1)
		env_change_brush(env, Pencil);
	else if (event->key.keysym.sym == SDLK_2)
		env_change_brush(env, Line);
	else if (event->key.keysym.sym == SDLK_3)
		env_change_brush(env, Horizontal_line);
	else if (event->key.keysym.sym == SDLK_4)
		env_change_brush(env, Vertical_line);
	else if (event->key.keysym.sym == SDLK_5)
		env_change_brush(env, Square);
	else if (event->key.keysym.sym == SDLK_6)
		env_change_brush(env, Circle);
	else if (event->key.keysym.sym == SDLK_7)
		env_change_brush(env, Paint_Bucket);
	else
		return (on_key_press_3(event, env));
	return (1);
}

int			on_key_press(SDL_Event *event, t_env *env)
{
	if (event->key.keysym.sym == SDLK_SPACE)
	{
		if (env->mouse.b1 == True)
			SDL_SetRelativeMouseMode(SDL_TRUE);
		env->space = True;
	}
	else if (event->key.keysym.sym == SDLK_LCTRL)
		env->ctrl = True;
	else if (event->key.keysym.sym == SDLK_LALT)
		env->alt = True;
	else if (event->key.keysym.sym == SDLK_s)
	{
		if (env->ctrl == True)
			save_file(env);
	}
	else
		return (on_key_press_2(event, env));
	return (1);
}
