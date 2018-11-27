/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/27 15:19:44 by vparis           ###   ########.fr       */
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
