/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/31 02:23:52 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

void		toggle_action(t_env *env, int action)
{
	env->user_action = action;
}

void		toggle_key_action(t_env *env, t_u32 action)
{
	toggle_action(env, (int)action);
	button_setactive(env->act_buttons[action], True);
}

void		manage_down(const Uint8	*state, t_env *env)
{
	if (env->mouse.b1 == False)
		return ;
	if (state[SDL_SCANCODE_X])
		toolset_set_tmp_type(&env->toolset, ZoomIn);
	if (state[SDL_SCANCODE_Z])
		toolset_set_tmp_type(&env->toolset, ZoomOut);
	if (state[SDL_SCANCODE_SPACE])
		toolset_set_tmp_type(&env->toolset, Hand);
	if (state[SDL_SCANCODE_LALT])
		toolset_set_tmp_type(&env->toolset, Picker);
	if (state[SDL_SCANCODE_LCTRL])
		toolset_set_tmp_type(&env->toolset, SpawnSetter);
	if (state[SDL_SCANCODE_LSHIFT])
		toolset_set_tmp_type(&env->toolset, Eraser);
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

int			on_key_press(SDL_Event *event, t_env *env)
{
	if (event->key.keysym.sym == SDLK_SPACE)
	{
		if (env->mouse1 == 1)
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
	else if (event->key.keysym.sym == SDLK_b)
		toggle_key_action(env, Draw_Wall);
	else if (event->key.keysym.sym == SDLK_v)
		toggle_key_action(env, Set_Spawn);
	else if (event->key.keysym.sym == SDLK_c)
		toggle_key_action(env, Erase_Wall);
	else if (event->key.keysym.sym == SDLK_n)
		toggle_key_action(env, Edit_Obj);
	else if (event->key.keysym.sym == SDLK_1)
		button_trigger(env->inspector.b_select.type_select[Pencil]);
	else if (event->key.keysym.sym == SDLK_2)
		button_trigger(env->inspector.b_select.type_select[Line]);
	else if (event->key.keysym.sym == SDLK_3)
		button_trigger(env->inspector.b_select.type_select[Horizontal_line]);
	else if (event->key.keysym.sym == SDLK_4)
		button_trigger(env->inspector.b_select.type_select[Vertical_line]);
	else if (event->key.keysym.sym == SDLK_5)
		button_trigger(env->inspector.b_select.type_select[Square]);
	else if (event->key.keysym.sym == SDLK_6)
		button_trigger(env->inspector.b_select.type_select[Circle]);
	else if (event->key.keysym.sym == SDLK_7)
		button_trigger(env->inspector.b_select.type_select[Paint_Bucket]);
	else if (event->key.keysym.sym == SDLK_p)
		printf("%f\n", env->map_info.zoom);
	else if (event->key.keysym.sym == SDLK_DELETE
		&& env->obj.edit.selected != -1 && env->user_action == Edit_Obj)
		object_destroy(&env->obj, (t_u32)env->obj.edit.selected);
	return (1);
}
int			on_mouse_motion(SDL_Event *event, t_env *env)
{
	t_map_info	*minf;

	minf = &env->map_info;
	if (env->space && env->mouse1)
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
			env->mouse1 = True;
		mouse_button_setstate(env, 1, True);
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
	{
		env->mouse2 = True;
		mouse_button_setstate(env, 2, True);
	}
	return (1);
}

int			check_act_buttons(t_env *env, t_ivec2 mpos)
{
	t_u32		i;

	i = 0;
	while (i < Max_action)
	{
		if (button_hover(env->act_buttons[i], mpos) == True)
		{
			button_setactive(env->act_buttons[i], True);
			return (SUCCESS);
		}
		i++;
	}
	return (ERROR);
}

int			on_mbutton_release(SDL_Event *event, t_env *env)
{
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		t_ivec2	mpos;

		mpos = get_mouse_pos();
		env->map_info.map->data[env->spawn.y][env->spawn.x] = 0;
		SDL_SetRelativeMouseMode(SDL_FALSE);
		env->mouse1 = False;
		mouse_button_setstate(env, 1, False);
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
	{
		env->mouse2 = False;
		mouse_button_setstate(env, 2, False);
	}
	return (1);
}

int			on_mouse_wheel(SDL_Event *event, t_env *env)
{
	t_ivec2	mpos;
	int		dir;

	mpos = get_mouse_pos();
	dir = -event->wheel.y;
	env->mouse.wheel = event->wheel.y;
	if (panel_isinside(env->palette.b_pan, mpos))
	panel_change_view(env->palette.b_pan, dir);
	else if (panel_isinside(env->obj.pan, mpos))
		panel_change_view(env->palette.b_pan, dir);
	else
	{
		panel_update_cursor(env->palette.b_pan,
			(t_u32)((int)env->palette.b_pan->cursor + dir));
		env->palette.brush = (int)env->palette.b_pan->cursor;
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
