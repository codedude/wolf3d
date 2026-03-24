/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:50:06 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 14:53:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "player.h"
#include "sdl_m.h"
#include "types.h"

// t = [0,1], clamp the result due to float precision error
t_float float_lerp(t_float from, t_float to, t_float t) {
	return (from + t * (to - from));
}

static void player_set_walk_anim(t_sdl *sdl, t_player *player) {
	t_float speed;
	if (player->action_state & ACTION_DASHING)
		return;
	speed = WALKANIM_SPEED * sdl->deltatime;
	if (player->controller.x != 0.0f || player->controller.y != 0.0f) {
		if (player->wanim_towards == 0.0f)
			player->wanim_towards = 1.0f;
		player->walk_anim += player->wanim_towards * speed;
		if (fabs(player->walk_anim) >= WALKANIM_MAXHEIGHT) {
			player->walk_anim = WALKANIM_MAXHEIGHT * player->wanim_towards;
			player->wanim_towards = -player->wanim_towards;
		}
	} else if (player->walk_anim != 0.0f) {
		player->wanim_towards = 0.0f;
		player->walk_anim = float_lerp(
		    player->walk_anim < 0.f ? -WALKANIM_MAXHEIGHT : WALKANIM_MAXHEIGHT,
		    0.f,
		    1.f - clamp_float(fabs(player->walk_anim) / WALKANIM_MAXHEIGHT *
		                          speed,
		                      0.f, 1.0f));
		player->walk_anim = clamp_float(player->walk_anim, -WALKANIM_MAXHEIGHT,
		                                WALKANIM_MAXHEIGHT);
		if (fabs(player->walk_anim) < 0.01f) {
			player->walk_anim = 0.0f;
		}
	}
}

static void player_ground_anim(t_sdl *sdl, t_cam *cam, t_player *player) {
	if (player->action_state & ACTION_CROUCHING) {
		if (cam->z_pos > cam->z_default / 2.0f)
			cam->z_pos -= ANIM_CROUCH_SPEED * sdl->deltatime;
	} else if (cam->z_pos < cam->z_default) {
		cam->z_pos += ANIM_CROUCH_SPEED * sdl->deltatime;
		if (cam->z_pos > cam->z_default - 0.001f)
			cam->z_pos = cam->z_default;
	}
}

void player_set_anim(t_sdl *sdl, t_cam *cam, t_player *player, t_env *env) {
	player_set_walk_anim(sdl, player);
	if (player->action_state & ACTION_GROUNDED)
		player_ground_anim(sdl, cam, player);
	else {
		if (player->action_state & ACTION_FALLING)
			player_fall(sdl, cam, player, env);
		else if (player->action_state & ACTION_JUMPING)
			player_jump(sdl, cam, player);
	}
}

void player_set_dash(t_player *player) {
	if (player->action_state & ACTION_DASHING)
		return;
	player->action_state |= ACTION_DASHING;
	if (player->controller.x != 0.0f || player->controller.y != 0.0f)
		player->dash = player->controller;
	else
		player->dash = VEC2_LEFT;
	player->dash_time = DASH_LIFETIME;
}
