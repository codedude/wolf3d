/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:00:34 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/12 00:43:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "sdl_m.h"
#include "ft_type.h"
#include "types.h"
#include "event.h"

static void		event_kb_state_jump(t_env *env, t_cam *cam)
{
	t_float	percent;

	if (cam->action_state & ACTION_FLY_MODE)
	{
		percent = env->sdl.canvas_h / 33.33;
		cam->z_pos += percent;
	}
	else if (cam->action_state & ACTION_GROUNDED)
	{
		cam->action_state &= ~ACTION_GROUNDED;
		cam->action_state |= ACTION_JUMPING;
		cam->jump_time = ACTION_MAX_JUMP_TIME;
	}
}

static void		event_kb_state_move(const Uint8 *state, t_env *env, t_cam *cam,
				t_bool *is_walking)
{
	if (state[SDL_SCANCODE_A])
	{
		*is_walking = True;
		cam->pos = straf(env, cam->pos, cam->dir, player_speed(
			cam->action_state, cam->mov_speed, cam->acceleration, 0.75));
	}
	if (state[SDL_SCANCODE_D])
	{
		*is_walking = True;
		cam->pos = straf(env, cam->pos, cam->dir, player_speed(
			cam->action_state, cam->mov_speed, cam->acceleration, -0.75));
	}
	if (state[SDL_SCANCODE_W])
	{
		*is_walking = True;
		cam->pos = move_forward(env, cam->pos, cam->dir, player_speed(
			cam->action_state, cam->mov_speed, cam->acceleration, 1.0));
	}
	if (state[SDL_SCANCODE_S])
	{
		*is_walking = True;
		cam->pos = move_forward(env, cam->pos, cam->dir, player_speed(
			cam->action_state, cam->mov_speed, cam->acceleration, -0.75));
	}
}

void			event_kb_state(const Uint8 *state, t_env *env)
{
	t_cam	*cam;
	t_bool	is_walking;

	cam = &env->cam;
	is_walking = False;
	event_kb_state_move(state, env, cam, &is_walking);
	if (is_walking == True)
		env->cam.action_state |= ACTION_WALKING;
	else
		env->cam.action_state &= ~ACTION_WALKING;
	if (state[SDL_SCANCODE_LCTRL])
	{
		if (cam->action_state & ACTION_GROUNDED)
			cam->action_state |= ACTION_CROUCHING;
	}
	else
		cam->action_state &= ~ACTION_CROUCHING;
	if (state[SDL_SCANCODE_LSHIFT] && cam->acceleration == 0.0)
		cam->acceleration = 0.25;
	if (state[SDL_SCANCODE_SPACE])
		event_kb_state_jump(env, cam);
}
