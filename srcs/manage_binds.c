/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:00:34 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/01 16:49:34 by vparis           ###   ########.fr       */
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
	}
	else
		cam->action_state &= ~ACTION_CROUCHING;
	if (state[SDL_SCANCODE_SPACE])
	{
		if (cam->action_state & ACTION_FLY_MODE)
		{
			percent = env->sdl.canvas_h / 33.33;
			cam->z += percent;
		}
		else if (cam->action_state & ACTION_GROUNDED)
		{
			cam->action_state &= ~ACTION_GROUNDED;
			cam->jump_time = ACTION_MAX_JUMP_TIME;
		}
	}
}

void		switch_effect(t_cam *cam, void *new, int type)
{
	void	**current;

	if (type == EFFECT_MASK_DEPTH)
		current = (void **)&cam->depth_filter;
	else if (type == EFFECT_MASK_COLOR)
		current = (void **)&cam->color_filter;
	else
		current = NULL;
	if (*current == new)
		*current = NULL;
	else
		*current = new;
}

int			manage_binds(SDL_Event *event, t_env *env)
{
	int		r;

	r = 1;
	if (event->type == SDL_QUIT)
		return (0);
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			return (0);
	}
	else if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_LSHIFT
			&& env->cam.acceleration == 0.0)
			env->cam.acceleration = 0.25;
		if (event->key.keysym.sym == SDLK_f)
			env->show_fps = !env->show_fps;
		else if (event->key.keysym.sym == SDLK_1)
			env->cam.side_filter ^= EFFECT_SIDE;
		else if (event->key.keysym.sym == SDLK_2)
			switch_effect(&env->cam, depth_filter_depth, EFFECT_MASK_DEPTH);
		else if (event->key.keysym.sym == SDLK_3)
			switch_effect(&env->cam, depth_filter_fog, EFFECT_MASK_DEPTH);
		else if (event->key.keysym.sym == SDLK_4)
			switch_effect(&env->cam, depth_filter_water, EFFECT_MASK_DEPTH);
		else if (event->key.keysym.sym == SDLK_5)
			switch_effect(&env->cam, color_filter_baw, EFFECT_MASK_COLOR);
		else if (event->key.keysym.sym == SDLK_6)
			switch_effect(&env->cam, color_filter_sepia, EFFECT_MASK_COLOR);
		else if (event->key.keysym.sym == SDLK_0)
		{
			env->cam.side_filter = EFFECT_NONE;
			switch_effect(&env->cam, NULL, EFFECT_MASK_DEPTH);
			switch_effect(&env->cam, NULL, EFFECT_MASK_COLOR);
		}
		else if (event->key.keysym.sym == SDLK_g)
		{
			if (env->cam.action_state & ACTION_FLY_MODE)
			{
				env->cam.action_state &= ~ACTION_FLY_MODE;
				if (env->cam.z > env->sdl.half_canvas_h)
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
