/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:45:59 by vparis            #+#    #+#             */
/*   Updated: 2018/12/04 11:54:54 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "raycast.h"

t_vec2	vec_rotate(t_vec2 dir, t_float speed)
{
	t_float old_x;

	old_x = dir.x;
	dir.x = dir.x * cos(-speed) - dir.y * sin(-speed);
	dir.y = old_x * sin(-speed) + dir.y * cos(-speed);
	return (dir);
}

void	player_jump(t_cam *player)
{
	if (player->jump_time > 0.001)
	{
		player->z_pos += ACTION_JUMP_FORCE * player->jump_time;
		player->jump_time -= (ACTION_MAX_JUMP_TIME / 10.0);
	}
	else
	{
		player->action_state |= ACTION_FALLING;
		player->action_state &= ~ACTION_JUMPING;
	}
}

void	player_fall(t_cam *player)
{
	if (player->z_pos < player->z_default)
	{
		player->action_state |= ACTION_GROUNDED;
		player->action_state &= ~ACTION_FALLING;
	}
	else
	{
		player->z_pos -= ACTION_FALL_SPEED * player->jump_time;
		player->jump_time += 0.15;
	}
}

void	player_set_acceleration(t_cam *player)
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

void	player_set_z(t_cam *player)
{
	player->z = player->walk_anim + player->z_pos;
}