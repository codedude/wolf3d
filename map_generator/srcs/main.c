/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 02:17:10 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "entity.h"
#include "libft.h"

static void		update_zoom(t_env *env)
{
	t_map_info	*inf;
	t_float		factor;

	inf = &env->map_info;
	if (inf->zoom > inf->zoom_max)
	{
		factor = (inf->zoom - inf->zoom_max) * 0.04;
		inf->zoom = (factor < 0.002) ? inf->zoom_max : inf->zoom - factor;
	}
	else if (inf->zoom < inf->zoom_min)
	{
		factor = (inf->zoom_min - inf->zoom) * 0.04;
		inf->zoom = (factor < 0.002) ? inf->zoom_min : inf->zoom + factor;
	}
}

static void		update_actions(t_env *env)
{
	t_u32		area;

	area = env->mouse.area;
	if (env->mouse.b1 == False || area == Not_On_Window)
	{
		entity_destroy(&env->map_info.map->data[env->spawn.y][env->spawn.x],
			True);
		return ;
	}
	update_mouse_pos(env);
	env->mouse.b1_status = Mouse_Hold;
	env->mouse.update[area](env);
}

static int		get_events(t_env *env)
{
	SDL_Event	event;
	const Uint8	*state;

	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&event))
		if (manage_binds(&event, env) == 0)
			return (0);
	manage_down(state, env);
	return (1);
}

static void		loop(t_env *env)
{
	int		i;

	i = 0;
	while (get_events(env) == 1)
	{
		sdl_update_texture(&env->sdl);
		update_actions(env);
		update_zoom(env);
		draw_update(env, &env->sdl);
		sdl_render(&env->sdl);
		i++;
		if (i == 3)
		{
			env->cpick.kframe = (env->cpick.kframe + 1) % 60;
			i = 0;
		}
	}
}

int				main(int ac, char **argv)
{
	t_env	env;

	if (ac != 2)
	{
		ft_putstr_fd(EDIT_USAGE, 2);
		return (EXIT_FAILURE);
	}
	if (env_init(&env, argv[1]) == ERROR)
		return (EXIT_FAILURE);
	loop(&env);
	env_destroy(&env);
	return (EXIT_SUCCESS);
}
