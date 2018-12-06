/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/06 18:53:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"

void	prepare_threads(t_env *env, t_algo **pack)
{
	int			i;
	int			tasks;

	tasks = tp_getnbr_proc(env->tpool);
	if ((*pack = (t_algo *)malloc((size_t)(tasks) * sizeof(t_algo)))
		== NULL)
		return ;
	i = 0;
	while (i < tasks)
	{
		(*pack)[i].env = env;
		(*pack)[i].start = i;
		(*pack)[i].end = env->sdl.width;
		(*pack)[i].step = tasks;
		tp_add_task(env->tpool, &start_render, &(*pack)[i]);
		i++;
	}
}

void	loop(t_env *env)
{
	int			loop;
	SDL_Event	event;
	const Uint8	*state;
	t_algo		*pack;

	prepare_threads(env, &pack);
	loop = 1;
	while (loop == 1)
	{
		SDL_PumpEvents();
		state = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event))
			loop = manage_binds(&event, env);
		manage_down(state, env);
		if (loop != 1)
			break ;
		// sdl_render and computation in parallel ? make sure data copy is safe
		// only SDL_UpdateTexture need to be protected
		// step thread or cut screen ?
		tp_wait_for_queue(env->tpool);
		compute_sprites(env);
		sdl_render(&env->sdl);
		get_fps(env->show_fps);
		player_set_acceleration(&env->cam);
		player_set_anim(&env->cam);
		player_set_z(&env->cam);
	}
	free(pack);
}

int		main(int ac, char **av)
{
	t_env	env;

	if (ac != 2)
	{
		ft_putstr_fd(ac == 1 ?
			"Wolf3d: not enough argument\n" : "Wolf3d: too many arguments\n",
			2);
		return (1);
	}
	if (env_init(&env, av[1]) == SUCCESS)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		loop(&env);
	}
	env_destroy(&env);
	return (0);
}
