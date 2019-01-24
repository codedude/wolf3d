/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:45:59 by vparis            #+#    #+#             */
/*   Updated: 2019/01/24 13:07:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"

void		player_jump(t_sdl *sdl, t_cam *cam, t_player *player, t_env *env)
{
	if (player->action_state & ACTION_JUMPING)
	{
		if (player->jump_time > 0.001)
		{
			cam->z_pos += ACTION_JUMP_FORCE * player->jump_time * sdl->deltatime;
			player->jump_time -= sdl->deltatime;
		}
		else
		{
			player->action_state |= ACTION_FALLING;
			player->action_state &= ~ACTION_JUMPING;
		}
	}
}

void		player_fall(t_sdl *sdl, t_cam *cam, t_player *player, t_env *env)
{
	if (player->action_state & ACTION_GROUNDED)
		return ;
	if (cam->z_pos < cam->z_default)
	{
		cam->z_pos = float_lerp(cam->z_pos, cam->z_default, 2.5);
		if (fabs(cam->z_pos - cam->z_default) < 0.001)
		{
			player->action_state |= ACTION_GROUNDED;
			player->action_state &= ~ACTION_FALLING;
			sound_play(&env->audio, SOUND_FALL_JUMP);
		}
	}
	else
	{
		cam->z_pos -= ACTION_FALL_SPEED * player->jump_time * sdl->deltatime;
		player->jump_time += sdl->deltatime;
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

void		player_set_z(t_sdl *sdl, t_cam *cam, t_player *player)
{
	cam->z = player->walk_anim + cam->z_pos * sdl->canvas_h;
}
