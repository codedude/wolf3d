/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/30 12:55:59 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"

t_vec2		vec_rotate(t_vec2 dir, t_float speed)
{
    t_float old_x;

	old_x = dir.x;
	dir.x = dir.x * cos(-speed) - dir.y * sin(-speed);
	dir.y = old_x * sin(-speed) + dir.y * cos(-speed);
	return (dir);
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

void	player_set_walk_anim(t_cam *player)
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
		player->walk_anim -= ANIM_WALK_SPEED;
		if (player->walk_anim < -ANIM_WALK_HEIGHT)
			player->action_state = (player->action_state
						& ~ANIM_WALK_DOWN) | ANIM_WALK_UP;
	}
}

void	player_disable_walk_anim(t_cam *player)
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

void	player_set_anim(t_cam *player, t_sdl *sdl)
{
	if (player->action_state & ACTION_WALKING)
		player_set_walk_anim(player);
	else if (player->walk_anim != 0.0)
		player_disable_walk_anim(player);
	if (player->action_state & ACTION_CROUCHING)
	{
		if (player->z_pos > sdl->height / 4.0)
			player->z_pos -= ANIM_CROUCH_SPEED;
	}
	else if (player->z_pos < sdl->height / 2.0)
	{
		player->z_pos += ANIM_CROUCH_SPEED;
		if (player->z_pos > (sdl->height / 2.0) - 0.001)
			player->z_pos = sdl->height / 2.0;
	}
}

void	player_set_z(t_cam *player)
{
	player->z = player->walk_anim + player->z_pos;
}

void	compute(t_env *env)
{
	t_algo		pack[TASKS];
	int			n_div;
	int			n_mod;
	int			i;
	int			tasks;

	i = 0;
	tasks = TASKS;
	n_div = env->sdl.width / tasks;
	n_mod = env->sdl.width % tasks;
	while (i < tasks)
	{
		pack[i].env = env;
		pack[i].start = i * n_div;
		pack[i].end = i < tasks - 1 ? n_div : n_div + n_mod;
		pack[i].end += pack[i].start;
		tp_add_task(env->tpool, &start_render, &pack[i]);
		i++;
	}
	tp_wait_for_queue(env->tpool);
}

void	loop(t_env *env)
{
	int			loop;
	SDL_Event	event;
	const Uint8	*state;

	loop = 1;
	while (loop == 1)
	{
		SDL_PumpEvents();
		state = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event))
			loop = manage_binds(&event, env);
		manage_down(state, env);
		if (loop != 1)
		{
			break ;
		}
		sdl_clear(&env->sdl);
		compute(env);
		sdl_render(&env->sdl);
		player_set_acceleration(&env->cam);
		player_set_anim(&env->cam, &env->sdl);
		player_set_z(&env->cam);
		get_fps(env->show_fps);
	}
}

int		main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
	{
		ft_putstr_fd(ac == 1 ? "Wolf3d: not enough argument\n" : "Wolf3d: too many arguments\n", 2);
		return (1);
	}
	if (env_init(&env, av[1]) == ERROR)
	{
		exit(1);
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	loop(&env);

	env_destroy(&env);
	return (0);
}
