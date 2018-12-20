/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/20 13:37:33 by jbulant          ###   ########.fr       */
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
	if (state[SDL_SCANCODE_X])
	{
		env->zoom *= 1.01;
	}
	if (state[SDL_SCANCODE_Z])
	{
		env->zoom /= 1.01;
	}
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
		env->map_pos = map_to_center(env);
	else if (event->key.keysym.sym == SDLK_y
		&& env->map->size.x < MAX_SIZE_X)
		env->map->size.x++;
	else if (event->key.keysym.sym == SDLK_t
		&& env->map->size.x > MIN_SIZE_X)
		env->map->size.x--;
	else if (event->key.keysym.sym == SDLK_h
		&& env->map->size.y < MAX_SIZE_Y)
		env->map->size.y++;
	else if (event->key.keysym.sym == SDLK_g
		&& env->map->size.y > MIN_SIZE_Y)
		env->map->size.y--;
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
	return (1);
}

int			on_mouse_motion(SDL_Event *event, t_env *env)
{
	if (env->space && env->mouse1)
	{
		env->map_pos.x += event->motion.xrel;
		env->map_pos.y += event->motion.yrel;
	}
	return (1);
}

int			on_mbutton_press(SDL_Event *event, t_env *env)
{
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if (env->space == 1)
				SDL_SetRelativeMouseMode(SDL_TRUE);
			env->mouse1 = True;
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
		env->mouse2 = True;
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
		env->map->data[env->spawn.y][env->spawn.x] = 0;
		if (panel_isinside(env->brush_pan, mpos))
		{
			int		tmp;

			tmp = panel_get_index_by_pos(env->brush_pan, mpos);
			if (tmp != -1)
			{
				panel_update_cursor(env->brush_pan, (t_u32)tmp);
				env->brush = (int)env->brush_pan->cursor;
			}
			// switch_brush(mpos, env);
		}
		else
			check_act_buttons(env, mpos);
		SDL_SetRelativeMouseMode(SDL_FALSE);
		env->mouse1 = False;
	}
	else if (event->button.button == SDL_BUTTON_RIGHT)
		env->mouse2 = False;
	return (1);
}

int			on_mouse_wheel(SDL_Event *event, t_env *env)
{
	t_ivec2	mpos;
	int		dir;

	mpos = get_mouse_pos();
	dir = -event->wheel.y;
	if (panel_isinside(env->brush_pan, mpos))
	panel_change_view(env->brush_pan, dir);
	else if (panel_isinside(env->obj_pan, mpos))
		panel_change_view(env->brush_pan, dir);
	else
	{
		panel_update_cursor(env->brush_pan,
			(t_u32)((int)env->brush_pan->cursor + dir));
		env->brush = (int)env->brush_pan->cursor;
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
	else if (event->type == SDL_MOUSEMOTION)
		return (on_mouse_motion(event, env));
	else if (event->type == SDL_MOUSEBUTTONDOWN)
		return (on_mbutton_press(event, env));
	else if (event->type == SDL_MOUSEBUTTONUP)
		return (on_mbutton_release(event, env));
	else if (event->type == SDL_MOUSEWHEEL)
		return (on_mouse_wheel(event, env));
	return (r);
}
