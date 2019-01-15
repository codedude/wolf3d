/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:00:34 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/15 19:38:05 by vparis           ###   ########.fr       */
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
		cam->z_pos += percent;
	}
	else if (player->action_state & ACTION_GROUNDED)
	{
		player->action_state &= ~ACTION_GROUNDED;
		player->action_state |= ACTION_JUMPING;
		player->jump_time = ACTION_MAX_JUMP_TIME;
	}
}

/*
	if ((cmp = state[SDL_SCANCODE_A] != 0))
		env->cam.pos = straf(env, env->cam.pos, env->cam.dir, player_speed(
			player->action_state, player->mov_speed, player->acceleration,
			SPEED_F));
	if ((cmp |= state[SDL_SCANCODE_D] != 0))
		env->cam.pos = straf(env, env->cam.pos, env->cam.dir, player_speed(
			player->action_state, player->mov_speed, player->acceleration,
			-SPEED_F));
	if ((cmp |= state[SDL_SCANCODE_W] != 0))
		env->cam.pos = move_forward(env, env->cam.pos, env->cam.dir,
			player_speed(player->action_state, player->mov_speed,
				player->acceleration, SPEED_F));
	if ((cmp |= state[SDL_SCANCODE_S] != 0))
		env->cam.pos = move_forward(env, env->cam.pos, env->cam.dir,
			player_speed(player->action_state, player->mov_speed,
				player->acceleration, -SPEED_B));
*/

# define PLAYER_ACCEL_FWD	0.05

static void		event_kb_state_move(const Uint8 *state, t_env *env,
					t_player *player, t_bool *is_walking)
{
	if (state[SDL_SCANCODE_D] != 0)
	{
		*is_walking = True;
		player->velocity.x += PLAYER_ACCEL_FWD;
	}
	if (state[SDL_SCANCODE_A] != 0)
	{
		*is_walking = True;
		player->velocity.x -= PLAYER_ACCEL_FWD;
	}
	if (state[SDL_SCANCODE_W] != 0)
	{
		*is_walking = True;
		player->velocity.y -= PLAYER_ACCEL_FWD;
	}
	if (state[SDL_SCANCODE_S] != 0)
	{
		*is_walking = True;
		player->velocity.y += PLAYER_ACCEL_FWD;
	}
	player->velocity.y = clamp_float(player->velocity.y, -1.0, 0.75);
	player->velocity.x = clamp_float(player->velocity.x, -0.75, 0.75);
	printf("%f %f\n", player->velocity.x, player->velocity.y);
}

void			event_kb_state(const Uint8 *state, t_env *env)
{
	t_player	*player;
	t_bool		is_walking;

	player = &env->player;
	is_walking = False;
	event_kb_state_move(state, env, player, &is_walking);
	if (is_walking == True)
		player->action_state |= ACTION_WALKING;
	else
		player->action_state &= ~ACTION_WALKING;
	if (state[SDL_SCANCODE_LCTRL])
	{
		if (player->action_state & ACTION_GROUNDED)
			player->action_state |= ACTION_CROUCHING;
	}
	else
		player->action_state &= ~ACTION_CROUCHING;
	if (state[SDL_SCANCODE_LSHIFT] && player->acceleration == 0.0)
		player->acceleration = 0.25;
	if (state[SDL_SCANCODE_SPACE])
		event_kb_state_jump(&env->sdl, &env->cam, player);
}
