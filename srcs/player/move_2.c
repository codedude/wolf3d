/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:46:07 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:41:44 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"

static t_float	set_accel_dim(t_float controller_v, t_float old_v,
					int is_grounded)
{
	t_float		new_v;

	if (is_grounded && controller_v != 0.0f)
		new_v = controller_v * PLAYER_ACCEL;
	else if (old_v != 0.0f)
	{
		new_v = -old_v * (is_grounded ? 1.0f : 0.2f);
		if (fabs(old_v) > PLAYER_STOP_TRESHOLD)
			new_v /= PLAYER_DECEL * (is_grounded ? 1.0f : 7.0f);
	}
	else
		new_v = 0.0f;
	return (new_v);
}

static void		player_set_velocity(t_sdl *sdl, t_player *player)
{
	t_float		max_v;
	t_vec2		accel;

	if ((player->action_state & ACTION_DASHING) == 0)
	{
		accel.x = set_accel_dim(player->controller.x, player->velocity.x,
			(player->action_state & ACTION_GROUNDED));
		accel.y = set_accel_dim(player->controller.y, player->velocity.y,
			(player->action_state & ACTION_GROUNDED));
		player->velocity += accel;
		max_v = vec_len(player->velocity);
		if (max_v > PLAYER_MAXSPEED)
			player->velocity *= PLAYER_MAXSPEED / max_v;
	}
	else
	{
		player->velocity = player->dash * DASH_SPEED * (player->dash_time
				+ (0.1f));
		player->dash_time -= sdl->deltatime;
		if (player->dash_time <= 0.0f)
		{
			player->action_state &= ~ACTION_DASHING;
		}
	}
}

static void		player_calc_controller(t_player *player)
{
	if (player->axis_state & Axis_Vertical)
		player->controller.x = player->axis_state & Axis_Down ? 1.0f : -1.0f;
	else
		player->controller.x = 0.0f;
	if (player->axis_state & Axis_Horizontal)
		player->controller.y = player->axis_state & Axis_Left ? 1.0f : -1.0f;
	else
		player->controller.y = 0.0f;
}

void			compute_player(t_env *env)
{
	t_vec2		dir;
	t_player	*player;
	t_float		speed;

	player = &env->player;
	player_calc_controller(player);
	player_set_velocity(&env->sdl, player);
	speed = 1.0f;
	if (player->velocity.y != 0.0f || player->velocity.x > 0.0f)
		speed *= 0.75f;
	if (player->action_state & ACTION_CROUCHING)
		speed *= 0.5f;
	dir = vec_rotate(player->velocity, env->cam.rot);
	env->cam.pos = move_forward(env, env->cam.pos,
						dir, speed * env->sdl.deltatime);
	player_set_anim(&env->sdl, &env->cam, player, env);
	player_set_z(&env->sdl, &env->cam, player);
}
