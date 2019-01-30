/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:46:36 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:49:02 by vparis           ###   ########.fr       */
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

static void	event_flymode(t_cam *cam, t_player *player, t_env *env)
{
	if (player->action_state & ACTION_FLY_MODE)
	{
		player->action_state &= ~ACTION_FLY_MODE;
		if (cam->z > env->sdl.half_canvas_h)
			player->action_state = (player->action_state & ~ACTION_GROUNDED)
				| ACTION_FALLING;
	}
	else
	{
		player->action_state |= ACTION_FLY_MODE;
		env->map.show_ceil = 0;
	}
}

static void	event_kb_poll_up3(SDL_Event *event, t_cam *cam, t_env *env)
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
	else if (event->key.keysym.sym == SDLK_8)
		music_play(&env->audio, MUSIC_TITLE);
	else if (event->key.keysym.sym == SDLK_9)
		music_stop(&env->audio);
}

static void	event_kb_poll_up2(SDL_Event *event, t_cam *cam, t_player *player,
				t_env *env)
{
	if (event->key.keysym.sym == SDLK_0)
	{
		cam->side_filter = EFFECT_NONE;
		switch_effect(cam, NULL, EFFECT_MASK_DEPTH);
		switch_effect(cam, NULL, EFFECT_MASK_COLOR);
	}
	else if (event->key.keysym.sym == SDLK_7
		&& !(player->action_state & ACTION_FLY_MODE))
		env->map.show_ceil = !env->map.show_ceil;
	else if (event->key.keysym.sym == SDLK_g)
		event_flymode(cam, player, env);
	else if (event->key.keysym.sym == SDLK_e)
		binds_open_door(env, &env->cam, &env->map);
	else
		event_kb_poll_up3(event, cam, env);
}

void		event_kb_poll_up(SDL_Event *event, t_cam *cam, t_player *player,
				t_env *env)
{
	if (event->key.keysym.sym == SDLK_a)
		player->axis_state = (player->axis_state & Axis_Vertical) | Axis_Left;
	else if (event->key.keysym.sym == SDLK_d)
		player->axis_state = (player->axis_state & Axis_Vertical) | Axis_Right;
	else if (event->key.keysym.sym == SDLK_w)
		player->axis_state = (player->axis_state & Axis_Horizontal) | Axis_Up;
	else if (event->key.keysym.sym == SDLK_s)
		player->axis_state = (player->axis_state & Axis_Horizontal) | Axis_Down;
	else
		event_kb_poll_up2(event, cam, player, env);
}
