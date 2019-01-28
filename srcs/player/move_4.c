/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:50:06 by vparis            #+#    #+#             */
/*   Updated: 2019/01/28 14:54:47 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"

t_float			float_lerp(t_float from, t_float to, t_float t)
{
	if (t == 0.0f)
		return (0.0f);
	return (from + (to - from) / t);
}

static void		player_set_walk_anim(t_sdl *sdl, t_player *player)
{
	t_float		speed;

	speed = WALKANIM_SPEED * sdl->deltatime;
	if ((player->controller.x != 0.0f || player->controller.y != 0.0f)
	&& !(player->action_state & ACTION_DASHING))
	{
		if (player->wanim_towards == 0.0f)
			player->wanim_towards = 1.0f;
		player->walk_anim += player->wanim_towards * speed;
		if (fabs(player->walk_anim) >= WALKANIM_MAXHEIGHT)
		{
			player->walk_anim = WALKANIM_MAXHEIGHT * player->wanim_towards;
			player->wanim_towards = -player->wanim_towards;
		}
	}
	else if (player->walk_anim != 0.0f)
	{
		player->wanim_towards = 0.0f;
		player->walk_anim = float_lerp(player->walk_anim, 0.0f,
			speed * 2.5f);
		if (fabs(player->walk_anim) < 0.01f)
			player->walk_anim = 0.0f;
	}
}

static void		player_ground_anim(t_sdl *sdl, t_cam *cam, t_player *player)
{
	if (player->action_state & ACTION_CROUCHING)
	{
		if (cam->z_pos > cam->z_default / 2.0f)
			cam->z_pos -= ANIM_CROUCH_SPEED * sdl->deltatime;
	}
	else if (cam->z_pos < cam->z_default)
	{
		cam->z_pos += ANIM_CROUCH_SPEED * sdl->deltatime;
		if (cam->z_pos > cam->z_default - 0.001f)
			cam->z_pos = cam->z_default;
	}
}

void			player_set_anim(t_sdl *sdl, t_cam *cam, t_player *player,
					t_env *env)
{
	player_set_walk_anim(sdl, player);
	if (player->action_state & ACTION_GROUNDED)
		player_ground_anim(sdl, cam, player);
	else
	{
		if (player->action_state & ACTION_FALLING)
			player_fall(sdl, cam, player, env);
		else if (player->action_state & ACTION_JUMPING)
			player_jump(sdl, cam, player);
	}
}

void			player_set_dash(t_player *player)
{
	if (player->action_state & ACTION_DASHING)
		return ;
	player->action_state |= ACTION_DASHING;
	if (player->controller.x != 0.0f || player->controller.y != 0.0f)
		player->dash = player->controller;
	else
		player->dash = VEC2_LEFT;
	player->dash_time = DASH_LIFETIME;
}
