/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:00:34 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/27 16:11:43 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"

t_float		player_speed(t_float speed, t_float acceleration, t_float factor)
{
	return ((speed + acceleration) * factor);
}

void		manage_down(const Uint8	*state, t_env *env)
{
	t_cam	*cam;

	cam = &env->cam;
	if (state[SDL_SCANCODE_A])
	{
		env->cam.pos = straf(&env->map, cam->pos, cam->dir,
			player_speed(cam->mov_speed, cam->acceleration, -0.75));
	}
	if (state[SDL_SCANCODE_D])
	{
		cam->pos = straf(&env->map, cam->pos, cam->dir,
			player_speed(cam->mov_speed, cam->acceleration, 0.75));
	}
	if (state[SDL_SCANCODE_W])
	{
		cam->pos = move_forward(&env->map, cam->pos, cam->dir,
			player_speed(cam->mov_speed, cam->acceleration, 1.0));
	}
	if (state[SDL_SCANCODE_S])
	{
		cam->pos = move_forward(&env->map, cam->pos, cam->dir,
			player_speed(cam->mov_speed, cam->acceleration, -0.75));
	}
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
		{
			env->show_fps = !env->show_fps;
		}
		else if (event->key.keysym.sym == SDLK_1)
		{
			env->effect = 0;
		}
		else if (event->key.keysym.sym == SDLK_2)
		{
			env->effect = EFFECT_DEPTH;
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
	}
	return (r);
}
