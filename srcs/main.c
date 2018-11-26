/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/26 16:14:01 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"

void		get_fps(int show_fps, int refresh)
{
	static struct timeval	last = {0, 0};
	double					fps;
	struct timeval			new;

	if (show_fps == 0)
		return ;
	gettimeofday(&new, NULL);
	if (refresh == 1)
	{
		fps = (new.tv_sec - last.tv_sec) * 1000 + (new.tv_usec - last.tv_usec)
			/ 1000.;
		ft_putchar('\r');
		ft_putstr("FPS : ");
		ft_putnbr((int)(1000. / fps));
	}
	last.tv_usec = new.tv_usec;
	last.tv_sec = new.tv_sec;
}

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
			loop = manage_binds(&event, &env->cam);
		manage_down(state, &env->cam, &env->map);
		if (loop != 1)
		{
			break ;
		}

		sdl_clear(&env->sdl);
		compute(env);
		sdl_render(&env->sdl);
		player_set_acceleration(&env->cam);
		// get_fps(1, 1);
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
