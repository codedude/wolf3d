/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/20 19:08:28 by vparis           ###   ########.fr       */
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

void	manage_down(const Uint8	*state, t_cam *player, t_map *map)
{
	if (state[SDL_SCANCODE_W])
	{
		player->pos = move_forward(map, player->pos, player->dir,
			player->mov_speed);
	}
	if (state[SDL_SCANCODE_A])
	{
		player->pos = straf(map, player->pos, player->dir,
			-player->mov_speed);
	}
	if (state[SDL_SCANCODE_S])
	{
		player->pos = move_forward(map, player->pos, player->dir,
			-player->mov_speed);
	}
	if (state[SDL_SCANCODE_D])
	{
		player->pos = straf(map, player->pos, player->dir,
			player->mov_speed);
	}
	if (state[SDL_SCANCODE_Q])
	{
      player->dir = vec_rotate(player->dir, -player->rot_speed);
      player->plane = vec_rotate(player->plane, -player->rot_speed);
	}
	if (state[SDL_SCANCODE_E])
	{
      player->dir = vec_rotate(player->dir, player->rot_speed);
      player->plane = vec_rotate(player->plane, player->rot_speed);
	}
}

int		manage_binds(SDL_Event *event)
{
	int		r;

	r = 1;
	if (event->type == SDL_QUIT)
		r = 0;
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			r = 0;
	}
	return (r);
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
		tp_add_task(env->tpool, &compute_raycast, &pack[i]);
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
			loop = manage_binds(&event);
		manage_down(state, &env->cam, &env->map);
		if (loop != 1)
		{
			break ;
		}

		sdl_clear(&env->sdl);
		compute(env);
		sdl_render(&env->sdl);
		get_fps(1, 1);
	}
}

int		main(void)
{
	t_env	env;

	if (env_init(&env) == ERROR)
	{
		exit(1);
	}

	loop(&env);

	env_destroy(&env);
	return (0);
}
