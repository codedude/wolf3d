/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:00:34 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/21 17:18:09 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "sdl_m.h"
#include "ft_type.h"
#include "types.h"
#include "event.h"
#include "camera.h"
#include "player.h"

static void		event_kb_state_jump(t_sdl *sdl, t_cam *cam, t_player *player)
{
	t_float	percent;

	if (player->action_state & ACTION_FLY_MODE)
	{
		percent = sdl->canvas_h / 33.33;
		cam->z_pos += percent * sdl->deltatime;
	}
	else if (player->action_state & ACTION_GROUNDED)
	{
		player->action_state &= ~ACTION_GROUNDED;
		player->action_state |= ACTION_JUMPING;
		player->jump_time = ACTION_MAX_JUMP_TIME;
	}
}

static void		event_kb_state_move(const Uint8 *state, t_player *player)
{
	if (state[SDL_SCANCODE_D] == 0)
		player->axis_state &= Axis_NOT_Right;
	else if ((player->axis_state & Axis_Horizontal) == 0)
		player->axis_state |= Axis_Right;
	if (state[SDL_SCANCODE_A] == 0)
		player->axis_state &= Axis_NOT_Left;
	else if ((player->axis_state & Axis_Horizontal) == 0)
		player->axis_state |= Axis_Left;
	if (state[SDL_SCANCODE_W] == 0)
		player->axis_state &= Axis_NOT_Up;
	else if ((player->axis_state & Axis_Vertical) == 0)
		player->axis_state |= Axis_Up;
	if (state[SDL_SCANCODE_S] == 0)
		player->axis_state &= Axis_NOT_Down;
	else if ((player->axis_state & Axis_Vertical) == 0)
		player->axis_state |= Axis_Down;
}

void			event_kb_state(const Uint8 *state, t_env *env)
{
	t_player	*player;

	player = &env->player;
	event_kb_state_move(state, player);
	if (state[SDL_SCANCODE_LCTRL])
	{
		if (player->action_state & ACTION_GROUNDED)
			player->action_state |= ACTION_CROUCHING;
	}
	else
		player->action_state &= ~ACTION_CROUCHING;
	if (state[SDL_SCANCODE_LSHIFT])
	{
		sound_play(&env->audio, SOUND_DASH);
		player_set_dash(player);
	}
	if (state[SDL_SCANCODE_SPACE])
		event_kb_state_jump(&env->sdl, &env->cam, &env->player);
}
