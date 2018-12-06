/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/06 12:58:14 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

void		pick_tile(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		mpos;

	mpos = get_mouse_pos();
	bounds = get_map_boundaries(env);
	if (is_bounded(mpos, env->grid) && is_bounded(mpos, bounds))
	{
		mpos = mpos_to_map_index(bounds, mpos, env);
		if ((int)env->map->data[mpos.y][mpos.x] > 0)
			env->brush = (int)env->map->data[mpos.y][mpos.x] - 1;
	}
}

void		update_actions(t_env *env)
{
	if (env->mouse2)
		return (draw_on_map(env, 0));
	if (!env->mouse1 || env->space)
		return ;
	if (env->alt)
		pick_tile(env);
	else
		draw_on_map(env, (int)(env->brush + 1));
}

void		loop(t_env *env)
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
			break ;
		update_actions(env);
		draw_grid(env, &env->sdl);
		sdl_render(&env->sdl);
	}
}

int			main(int ac, char **argv)
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
