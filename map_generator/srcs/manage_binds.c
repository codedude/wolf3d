/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/22 02:34:46 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
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

void		call_remove(t_env *env)
{
	if (env->editor.mode == Object_Edit)
	{
		if (env->obj.edit.selected != -1)
			object_destroy(&env->obj, (t_u32)env->obj.edit.selected);
	}
	else if (env->editor.mode == Door)
		door_destroy_selected(env, &env->inspector.door_edit);
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
	else if (event->key.keysym.sym == SDLK_r)
		map_update_center(env);
	else if (event->key.keysym.sym == SDLK_y)
		mprops_act_size_x_up(env);
	else if (event->key.keysym.sym == SDLK_t)
		mprops_act_size_x_down(env);
	else if (event->key.keysym.sym == SDLK_h)
		mprops_act_size_y_up(env);
	else if (event->key.keysym.sym == SDLK_g)
		mprops_act_size_y_down(env);
	else if (event->key.keysym.sym == SDLK_LALT)
		env->alt = True;
	else if (event->key.keysym.sym == SDLK_s)
	{
		if (env->ctrl == True)
			save_file(env);
	}
	else if (event->key.keysym.sym == SDLK_c)
		button_setactive(env->editor.switch_b[Painter], True);
	else if (event->key.keysym.sym == SDLK_v)
		button_setactive(env->editor.switch_b[World], True);
	else if (event->key.keysym.sym == SDLK_b)
		button_setactive(env->editor.switch_b[Door], True);
	else if (event->key.keysym.sym == SDLK_n)
		button_setactive(env->editor.switch_b[Object_Edit], True);
	else if (event->key.keysym.sym == SDLK_1)
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
	else if (event->key.keysym.sym == SDLK_p)
		printf("%f\n", env->map_info.zoom);
	else if (event->key.keysym.sym == SDLK_DELETE)
		call_remove(env);
	return (1);
}

int			on_mouse_motion(SDL_Event *event, t_env *env)
{
	t_map_info	*minf;

	minf = &env->map_info;
	if (env->space && env->mouse.b1 && env->mouse.area == Map_window)
	{
		minf->pos.x += event->motion.xrel * (1.5 / env->map_info.zoom);
		minf->pos.y += event->motion.yrel * (1.5 / env->map_info.zoom);
	}
	return (1);
}

int			on_mbutton_press(SDL_Event *event, t_env *env)
{
	t_canvas	bounds;

	bounds = get_map_boundaries(env);
	// env->last_mpos = get_mouse_pos();
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

int			on_mbutton_release(SDL_Event *event, t_env *env)
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

int			on_mouse_wheel(SDL_Event *event, t_env *env)
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
	// else if (event->type == SDL_MOUSEMOTION)
	// 	return (on_mouse_motion(event, env));
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		return (on_mbutton_press(event, env));
	else if (event->type == SDL_MOUSEBUTTONUP)
		return (on_mbutton_release(event, env));
	else if (event->type == SDL_MOUSEWHEEL)
		return (on_mouse_wheel(event, env));
	return (r);
}
