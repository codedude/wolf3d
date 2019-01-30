/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 00:06:09 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:48:57 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "sdl_m.h"
#include "types.h"
#include "entity.h"
#include "event.h"
#include "raycast.h"
#include "export_bmp.h"
#include "camera.h"
#include "player.h"
#include "audio.h"

static void	event_kb_poll_down(SDL_Event *event, t_player *player)
{
	if (event->key.keysym.sym == SDLK_a)
		player->axis_state = (player->axis_state & Axis_Vertical) | Axis_Left;
	else if (event->key.keysym.sym == SDLK_d)
		player->axis_state = (player->axis_state & Axis_Vertical) | Axis_Right;
	else if (event->key.keysym.sym == SDLK_w)
		player->axis_state = (player->axis_state & Axis_Horizontal) | Axis_Up;
	else if (event->key.keysym.sym == SDLK_s)
		player->axis_state = (player->axis_state & Axis_Horizontal) | Axis_Down;
}

static void	event_kb_poll_mousemotion(SDL_Event *event, t_cam *cam, t_sdl *sdl)
{
	t_float	motion;

	motion = event->motion.xrel / -250.0f;
	cam->rot += motion;
	cam->dir = vec_rotate(VEC2_INIT(-1.0f, 0.0f), cam->rot);
	cam->plane = vec_rotate(VEC2_INIT(0.0f, sdl->ratio_y),
		cam->rot);
	cam->height = clamp_float(cam->height + (t_float)event->motion.yrel * -2.0f,
					-MAX_OFFSET, MAX_OFFSET);
}

t_bool		event_kb_poll(SDL_Event *event, t_env *env)
{
	if (event->type == SDL_MOUSEMOTION)
	{
		event_kb_poll_mousemotion(event, &env->cam, &env->sdl);
		update_skybox_offset(&env->cam, &env->sdl, &env->map);
	}
	else if (event->type == SDL_KEYDOWN)
		event_kb_poll_down(event, &env->player);
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			return (False);
		else if (event->key.keysym.sym == SDLK_y)
			save_img(&env->sdl);
		else if (event->key.keysym.sym == SDLK_f)
			env->show_fps = !env->show_fps;
		else
			event_kb_poll_up(event, &env->cam, &env->player, env);
	}
	else if (event->type == SDL_QUIT)
		return (False);
	return (True);
}
