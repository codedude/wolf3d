/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:00:34 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/30 13:33:46 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"

t_float		player_speed(int action_state, t_float speed,
					t_float acceleration, t_float factor)
{
	if (action_state & ACTION_CROUCHING)
		factor *= 0.6;
	return ((speed + acceleration) * factor);
}

void		manage_down(const Uint8	*state, t_env *env)
{
	t_cam	*cam;
	t_float	percent;
	int		is_walking;


	cam = &env->cam;
	is_walking = False;
	if (state[SDL_SCANCODE_A])
	{
		is_walking = True;
		cam->pos = straf(&env->map, cam->pos, cam->dir,
			player_speed(cam->action_state, cam->mov_speed,
					cam->acceleration, -0.75));
	}
	if (state[SDL_SCANCODE_D])
	{
		is_walking = True;
		cam->pos = straf(&env->map, cam->pos, cam->dir,
			player_speed(cam->action_state, cam->mov_speed,
					cam->acceleration, 0.75));
	}
	if (state[SDL_SCANCODE_W])
	{
		is_walking = True;
		cam->pos = move_forward(&env->map, cam->pos, cam->dir,
			player_speed(cam->action_state, cam->mov_speed,
					cam->acceleration, 1.0));
	}
	if (state[SDL_SCANCODE_S])
	{
		is_walking = True;
		cam->pos = move_forward(&env->map, cam->pos, cam->dir,
			player_speed(cam->action_state, cam->mov_speed,
					cam->acceleration, -0.75));
	}
	if (is_walking == True)
		env->cam.action_state |= ACTION_WALKING;
	else
		env->cam.action_state &= ~ACTION_WALKING;
	if (state[SDL_SCANCODE_Q])
	{
		cam->dir = vec_rotate(cam->dir, -cam->rot_speed);
		cam->plane = vec_rotate(cam->plane, -cam->rot_speed);
	}
	if (state[SDL_SCANCODE_E])
	{
		cam->dir = vec_rotate(cam->dir, cam->rot_speed);
		cam->plane = vec_rotate(cam->plane, cam->rot_speed);
	}
	if (state[SDL_SCANCODE_LCTRL])
	{
		if (cam->action_state & ACTION_GROUNDED)
			cam->action_state |= ACTION_CROUCHING;
		// percent = env->sdl.height / 35;
		// cam->z_pos -= percent;
	}
	else
		cam->action_state &= ~ACTION_CROUCHING;
	if (state[SDL_SCANCODE_SPACE])
	{
		if (cam->action_state & ACTION_FLY_MODE)
		{
			percent = env->sdl.height / 35;
			cam->z_pos += percent;
		}
		else if (cam->action_state & ACTION_GROUNDED)
		{
			cam->action_state &= ~ACTION_GROUNDED;
			cam->jump_time = ACTION_MAX_JUMP_TIME;
		}
	}
}

int			switch_effect(int current, int new, int mask)
{
	if (current & mask && !(current & new))
		return ((current & ~mask) ^ new);
	else
		return (current ^ new);
}

int			manage_binds(SDL_Event *event, t_env *env)
{
	int		r;

	r = 1;
	if (event->type == SDL_QUIT)
		r = 0;
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			r = 0;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_LSHIFT
			&& env->cam.acceleration == 0.0)
			env->cam.acceleration = 0.25;
		if (event->key.keysym.sym == SDLK_f)
			env->show_fps = !env->show_fps;
		else if (event->key.keysym.sym == SDLK_1)
			env->effect = switch_effect(env->effect, EFFECT_SIDE,
				EFFECT_MASK);
		else if (event->key.keysym.sym == SDLK_2)
			env->effect = switch_effect(env->effect, EFFECT_DEPTH,
				EFFECT_MASK_DEPTH);
		else if (event->key.keysym.sym == SDLK_3)
			env->effect = switch_effect(env->effect, EFFECT_FOG,
				EFFECT_MASK_DEPTH);
		else if (event->key.keysym.sym == SDLK_4)
			env->effect = switch_effect(env->effect, EFFECT_WATER,
				EFFECT_MASK_DEPTH);
		else if (event->key.keysym.sym == SDLK_5)
			env->effect = switch_effect(env->effect, EFFECT_SEPIA,
				EFFECT_MASK_FILTERS);
		else if (event->key.keysym.sym == SDLK_6)
			env->effect = switch_effect(env->effect, EFFECT_BAW,
				EFFECT_MASK_FILTERS);
		else if (event->key.keysym.sym == SDLK_0)
			env->effect = EFFECT_NONE;
		else if (event->key.keysym.sym == SDLK_g)
		{
			if (env->cam.action_state & ACTION_FLY_MODE)
			{
				env->cam.action_state &= ~ACTION_FLY_MODE;
				if (env->cam.z_pos > env->sdl.height / 2.0)
					env->cam.action_state =
					(env->cam.action_state & ~ACTION_GROUNDED) | ACTION_FALLING;
			}
			else
				env->cam.action_state |= ACTION_FLY_MODE;
		}
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		env->cam.dir = vec_rotate(env->cam.dir,
					env->cam.rot_speed *
					(t_float)(event->motion.xrel * 0.33));
		env->cam.plane = vec_rotate(env->cam.plane,
					env->cam.rot_speed *
					(t_float)(event->motion.xrel * 0.33));
		env->cam.height = clamp_float(
						env->cam.height + -(t_float)event->motion.yrel * 2.0,
						-MAX_OFFSET, MAX_OFFSET);
	}
	return (r);
}
