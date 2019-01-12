/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 00:06:09 by vparis            #+#    #+#             */
/*   Updated: 2019/01/12 01:19:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "sdl_m.h"
#include "types.h"
#include "entity.h"
#include "event.h"
#include "raycast.h"
#include "export_bmp.h"

static void	event_kb_poll_up2(SDL_Event *event, t_cam *cam)
{
	if (event->key.keysym.sym == SDLK_1)
		cam->side_filter ^= EFFECT_SIDE;
	else if (event->key.keysym.sym == SDLK_2)
		switch_effect(cam, (void *)&depth_filter_depth, EFFECT_MASK_DEPTH);
	else if (event->key.keysym.sym == SDLK_3)
		switch_effect(cam, (void *)&depth_filter_fog, EFFECT_MASK_DEPTH);
	else if (event->key.keysym.sym == SDLK_4)
		switch_effect(cam, (void *)&depth_filter_water, EFFECT_MASK_DEPTH);
	else if (event->key.keysym.sym == SDLK_5)
		switch_effect(cam, (void *)&color_filter_baw, EFFECT_MASK_COLOR);
	else if (event->key.keysym.sym == SDLK_6)
		switch_effect(cam, (void *)&color_filter_sepia, EFFECT_MASK_COLOR);
}

static void	event_flymode(t_cam *cam, t_env *env)
{
	if (cam->action_state & ACTION_FLY_MODE)
	{
		cam->action_state &= ~ACTION_FLY_MODE;
		if (cam->z > env->sdl.half_canvas_h)
			cam->action_state = (cam->action_state & ~ACTION_GROUNDED)
				| ACTION_FALLING;
	}
	else
	{
		cam->action_state |= ACTION_FLY_MODE;
		env->map.show_ceil = 0;
	}
}

static void	event_kb_poll_up(SDL_Event *event, t_cam *cam, t_env *env)
{
	if (event->key.keysym.sym == SDLK_0)
	{
		cam->side_filter = EFFECT_NONE;
		switch_effect(cam, NULL, EFFECT_MASK_DEPTH);
		switch_effect(cam, NULL, EFFECT_MASK_COLOR);
	}
	else if (event->key.keysym.sym == SDLK_7
		&& !(cam->action_state & ACTION_FLY_MODE))
		env->map.show_ceil = !env->map.show_ceil;
	else if (event->key.keysym.sym == SDLK_g)
		event_flymode(cam, env);
	else if (event->key.keysym.sym == SDLK_e)
		binds_open_door(env);
	else
		event_kb_poll_up2(event, cam);
}

static void	event_kb_poll_mousemotion(SDL_Event *event, t_cam *cam)
{
	t_float	motion;

	motion = event->motion.xrel * -0.33;
	cam->dir = vec_rotate(cam->dir, cam->rot_speed * motion);
	cam->plane = vec_rotate(cam->plane, cam->rot_speed * motion);
	cam->height = clamp_float(cam->height + (t_float)event->motion.yrel * -2.0,
					-MAX_OFFSET, MAX_OFFSET);
}

t_bool		event_kb_poll(SDL_Event *event, t_env *env)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		event_kb_poll_mousemotion(event, &env->cam);
		update_skybox_offset(&env->cam, &env->sdl, &env->map);
	}
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			return (False);
		else if (event->key.keysym.sym == SDLK_y)
			save_img(&env->sdl);
		else if (event->key.keysym.sym == SDLK_f)
			env->show_fps = !env->show_fps;
		else
			event_kb_poll_up(event, &env->cam, env);
	}
	else if (event->type == SDL_QUIT)
		return (False);
	return (True);
}
