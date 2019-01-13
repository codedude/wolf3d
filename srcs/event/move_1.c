/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:45:59 by vparis            #+#    #+#             */
/*   Updated: 2019/01/13 12:59:22 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"

void		player_jump(t_cam *cam, t_player *player)
{
	if (player->jump_time > 0.001)
	{
		cam->z_pos += ACTION_JUMP_FORCE * player->jump_time;
		player->jump_time -= (ACTION_MAX_JUMP_TIME / 10.0);
	}
	else
	{
		player->action_state |= ACTION_FALLING;
		player->action_state &= ~ACTION_JUMPING;
	}
}

void		player_fall(t_cam *cam, t_player *player)
{
	if (cam->z_pos < cam->z_default)
	{
		player->action_state |= ACTION_GROUNDED;
		player->action_state &= ~ACTION_FALLING;
	}
	else
	{
		cam->z_pos -= ACTION_FALL_SPEED * player->jump_time;
		player->jump_time += 0.15;
	}
}

void		player_set_acceleration(t_player *player)
{
	if (player->acceleration > 0)
	{
		player->acceleration *= 0.85;
		if (player->acceleration < 0.005)
			player->acceleration = -(player->mov_speed * 0.2);
	}
	else if (player->acceleration < 0)
	{
		player->acceleration *= 0.85;
		if (player->acceleration > -0.005)
			player->acceleration = 0.0;
	}
}

void		player_set_z(t_cam *cam, t_player *player)
{
	cam->z = player->walk_anim + cam->z_pos;
}

t_float		player_speed(int action_state, t_float speed,
					t_float acceleration, t_float factor)
{
	if (action_state & ACTION_CROUCHING)
		factor *= 0.6;
	return ((speed + acceleration) * factor);
}
