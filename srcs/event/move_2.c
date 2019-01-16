/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:46:07 by vparis            #+#    #+#             */
/*   Updated: 2019/01/16 05:08:27 by jbulant          ###   ########.fr       */
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

# define WALKANIM_MAXHEIGHT		15.0
# define WALKANIM_SPEED			75.0

static void	player_set_walk_anim(t_sdl *sdl, t_player *player)
{
	t_float		speed;

	speed = WALKANIM_SPEED * sdl->deltatime;
	if (player->velocity.x != 0.0 || player->velocity.y != 0.0)
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

void		player_set_anim(t_sdl *sdl, t_cam *cam, t_player *player)
{
	player_set_walk_anim(sdl, player);
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

# define PLAYER_SPEED			3.5
# define PLAYER_DECEL			3.0
# define PLAYER_STOP_TRESHOLD	0.01

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

// # define DASH_LIFETIME			0.20
// # define DASH_ACCELTIME			(DASH_LIFETIME * 0.2)
// # define DASH_SPEED				10.0
//
// void		player_calc_dash(t_sdl *sdl, t_player *player)
// {
// 	if (player->action_state & ACTION_DASHING)
// 	{
// 		printf("%f\n",vec_len(player->velocity));
// 		player->dash_time += sdl->deltatime;
// 		if (player->dash_time < DASH_LIFETIME
// 		&& vec_len(player->dash) > 0.1)
// 		{
// 			printf("%f // %f %f\n", player->dash_time, player->dash.x, player->dash.y);
// 			if (player->dash_time < DASH_ACCELTIME)
// 				player->velocity += player->dash * player->dash_time * DASH_SPEED;
// 			else
// 			{
// 				player->dash = vec_lerp(player->dash, VEC2_ZERO,
// 							10.0);
// 				player->velocity += player->dash * DASH_SPEED;
// 			}
// 			printf("%f // %f %f\n", player->dash_time, player->dash.x, player->dash.y);
// 			// player->velocity += player->dash;
// 		}
// 		else
// 			player->action_state &= ~ACTION_DASHING;
// 	}
// 	else
// 		player->dash_time = 0.0;
// }

void		player_set_velocity(t_sdl *sdl, t_player *player)
{
	if ((player->action_state & ACTION_DASHING) == 0)
	{
		player->velocity.x = calc_velocity(
			player->velocity.x,
			player->axis_state,
			Axis_Vertical
		);
		player->velocity.y = calc_velocity(
			player->velocity.y,
			player->axis_state,
			Axis_Horizontal
		);
	}
	// player_calc_dash(sdl, player);
}

void		compute_player(t_env *env)
{
	t_vec2		dir;
	t_player	*player;
	t_float		speed;

	player = &env->player;
	player_set_velocity(&env->sdl, player);
	// player_set_acceleration(player);
	speed = env->sdl.deltatime * PLAYER_SPEED;
	if (player->velocity.y != 0.0 || player->velocity.x > 0.0)
		speed *= 0.75;
	if (player->action_state & ACTION_CROUCHING)
		speed *= 0.5;
	dir = vec_rotate(player->velocity, env->cam.rot);
	env->cam.pos = move_forward(env, env->cam.pos, dir, speed);
	player_set_anim(&env->sdl, &env->cam, player);
	player_set_z(&env->cam, player);
}
