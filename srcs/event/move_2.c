/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:46:07 by vparis            #+#    #+#             */
/*   Updated: 2019/01/16 21:21:39 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"

t_float		float_lerp(t_float from, t_float to, t_float t)
{
	if (t == 0.0)
		return (0.0);
	return (from + (to - from) / t);
}

t_vec2		vec_lerp(t_vec2 from, t_vec2 to, t_float t)
{
	if (t == 0.0)
		return (VEC2_ZERO);
	return (from + (to - from) / t);
}

static void	player_set_walk_anim(t_sdl *sdl, t_player *player)
{
	t_float		speed;

	speed = WALKANIM_SPEED * sdl->deltatime;
	if ((player->controller.x != 0.0 || player->controller.y != 0.0)
	&& !(player->action_state & ACTION_DASHING))
	{
		if (player->wanim_towards == 0.0)
			player->wanim_towards = 1.0;
		player->walk_anim += player->wanim_towards * speed;
		if (fabs(player->walk_anim) >= WALKANIM_MAXHEIGHT)
		{
			player->walk_anim = WALKANIM_MAXHEIGHT * player->wanim_towards;
			player->wanim_towards = -player->wanim_towards;
		}
	}
	else if (player->walk_anim != 0.0)
	{
		player->wanim_towards = 0.0;
		player->walk_anim = float_lerp(player->walk_anim, 0.0,
			speed * 2.5);
		if (fabs(player->walk_anim) < 0.01)
			player->walk_anim = 0.0;
	}
}

static void	player_ground_anim(t_sdl *sdl, t_cam *cam, t_player *player)
{
	if (player->action_state & ACTION_CROUCHING)
	{
		if (cam->z_pos > cam->z_default / 2.0)
			cam->z_pos -= ANIM_CROUCH_SPEED * sdl->deltatime;
	}
	else if (cam->z_pos < cam->z_default)
	{
		cam->z_pos += ANIM_CROUCH_SPEED * sdl->deltatime;
		if (cam->z_pos > cam->z_default - 0.001)
			cam->z_pos = cam->z_default;
	}
}

void		player_set_anim(t_sdl *sdl, t_cam *cam, t_player *player)
{
	player_set_walk_anim(sdl, player);
	if (player->action_state & ACTION_GROUNDED)
		player_ground_anim(sdl, cam, player);
	else
	{
		if (player->action_state & ACTION_FALLING)
			player_fall(sdl, cam, player);
		else if (player->action_state & ACTION_JUMPING)
			player_jump(sdl, cam, player);
	}
}

void		player_set_dash(t_player *player)
{
	if (player->action_state & ACTION_DASHING)
		return ;
	player->action_state |= ACTION_DASHING;
	if (player->controller.x != 0.0 || player->controller.y != 0.0)
		player->dash = player->controller;
	else
		player->dash = VEC2_LEFT;
	player->dash_time = DASH_LIFETIME;
}

t_float		calc_velocity(t_float old_val, t_axis_state axis, int direction)
{
	if (axis & direction)
	{
		old_val += (axis & direction) & Axis_Neg ? 0.1 : -0.1;
		old_val = clamp_float(old_val, -1.0, 1.0);
	}
	else if (old_val != 0.0)
	{
		old_val = float_lerp(old_val, 0.0, PLAYER_DECEL);
		if (fabs(old_val) < PLAYER_STOP_TRESHOLD)
			old_val = 0.0;
	}
	return (old_val);
}

t_float		set_accel_dim(t_float controller_v, t_float old_v, int is_grounded)
{
	t_float		new_v;

	if (is_grounded && controller_v != 0.0)
		new_v = controller_v * PLAYER_ACCEL;
	else if (old_v != 0.0)
	{
		new_v = -old_v;
		if (fabs(old_v) > PLAYER_STOP_TRESHOLD)
			new_v /= PLAYER_DECEL * (is_grounded ? 1.0 : 7.0);
	}
	else
		new_v = 0.0;
	return (new_v);
}

void		player_set_velocity(t_sdl *sdl, t_player *player)
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
			player->velocity *=  PLAYER_MAXSPEED / max_v;
	}
	else
	{
		player->velocity = player->dash * DASH_SPEED * (player->dash_time
				+ (0.1));
		player->dash_time -= sdl->deltatime;
		if (player->dash_time <= 0.0)
		{
			player->action_state &= ~ACTION_DASHING;
		}
	}
}

void		player_calc_controller(t_player *player)
{
	if (player->axis_state & Axis_Vertical)
		player->controller.x = player->axis_state & Axis_Down ? 1.0 : -1.0;
	else
		player->controller.x = 0.0;
	if (player->axis_state & Axis_Horizontal)
		player->controller.y = player->axis_state & Axis_Left ? 1.0 : -1.0;
	else
		player->controller.y = 0.0;
}

void		compute_player(t_env *env)
{
	t_vec2		dir;
	t_player	*player;
	t_float		speed;

	player = &env->player;
	player_calc_controller(player);
	player_set_velocity(&env->sdl, player);
	// player_set_acceleration(player);
	speed = 1.0;
	if (player->velocity.y != 0.0 || player->velocity.x > 0.0)
		speed *= 0.75;
	if (player->action_state & ACTION_CROUCHING)
		speed *= 0.5;
	dir = vec_rotate(player->velocity, env->cam.rot);
	env->cam.pos = move_forward(env, env->cam.pos, dir, speed * env->sdl.deltatime);
	player_set_anim(&env->sdl, &env->cam, player);
	player_set_z(&env->sdl, &env->cam, player);
}
