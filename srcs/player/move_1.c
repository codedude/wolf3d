/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:45:59 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 14:51:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "player.h"
#include "sdl_m.h"
#include "event.h"

void		player_jump(t_sdl *sdl, t_cam *cam, t_player *player)
{
	if (player->action_state & ACTION_JUMPING)
	{
		if (player->jump_time > 0.001f)
		{
			cam->z_pos += ACTION_JUMP_FORCE
				* player->jump_time * sdl->deltatime;
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
		cam->z_pos = float_lerp(cam->z_pos, cam->z_default, 2.5f);
		if (fabs(cam->z_pos - cam->z_default) < 0.001f)
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
		player->acceleration *= 0.85f;
		if (player->acceleration < 0.005f)
			player->acceleration = -(player->mov_speed * 0.2f);
	}
	else if (player->acceleration < 0)
	{
		player->acceleration *= 0.85f;
		if (player->acceleration > -0.005f)
			player->acceleration = 0.0f;
	}
}

void		player_set_z(t_sdl *sdl, t_cam *cam, t_player *player)
{
	cam->z = player->walk_anim + cam->z_pos * sdl->canvas_h;
}
