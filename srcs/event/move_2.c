/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:46:07 by vparis            #+#    #+#             */
/*   Updated: 2019/01/13 12:59:48 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"

static void	player_set_walk_anim(t_player *player)
{
	if (!(player->action_state & ANIM_WALK))
		player->action_state |= ANIM_WALK_UP;
	if (player->action_state & ANIM_WALK_UP)
	{
		player->walk_anim += ANIM_WALK_SPEED;
		if (player->walk_anim > ANIM_WALK_HEIGHT)
			player->action_state = (player->action_state
						& ~ANIM_WALK_UP) | ANIM_WALK_DOWN;
	}
	else if (player->action_state & ANIM_WALK_DOWN)
	{
		player->walk_anim -= ANIM_WALK_SPEED * 3.0;
		if (player->walk_anim < -ANIM_WALK_HEIGHT)
			player->action_state = (player->action_state
						& ~ANIM_WALK_DOWN) | ANIM_WALK_UP;
	}
}

static void	player_disable_walk_anim(t_player *player)
{
	if (player->walk_anim < 0.0)
	{
		player->walk_anim += ANIM_WALK_SPEED;
		if (player->walk_anim > -0.001)
		{
			player->walk_anim = 0.0;
			player->action_state &= ~ANIM_WALK;
		}
	}
	else
	{
		player->walk_anim -= ANIM_WALK_SPEED;
		if (player->walk_anim < -0.001)
		{
			player->walk_anim = 0.0;
			player->action_state &= ~ANIM_WALK;
		}
	}
}

static void	player_ground_anim(t_cam *cam, t_player *player)
{
	if (player->action_state & ACTION_CROUCHING)
	{
		if (cam->z_pos > cam->z_default / 2.0)
			cam->z_pos -= ANIM_CROUCH_SPEED;
	}
	else if (cam->z < cam->z_default)
	{
		cam->z_pos += ANIM_CROUCH_SPEED;
		if (cam->z_pos > cam->z_default - 0.001)
			cam->z_pos = cam->z_default;
	}
}

void		player_set_anim(t_cam *cam, t_player *player)
{
	if (player->action_state & ACTION_WALKING)
		player_set_walk_anim(player);
	else if (player->walk_anim != 0.0)
		player_disable_walk_anim(player);
	if (player->action_state & ACTION_GROUNDED)
		player_ground_anim(cam, player);
	else
	{
		if (player->action_state & ACTION_FALLING)
			player_fall(cam, player);
		else if (player->action_state & ACTION_JUMPING)
			player_jump(cam, player);
	}
}

void		compute_player(t_env *env)
{
	player_set_acceleration(&env->player);
	player_set_anim(&env->cam, &env->player);
	player_set_z(&env->cam, &env->player);
}
