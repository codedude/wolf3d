/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/11 14:50:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"
#include "texture.h"
#include "entity.h"
#include "anim.h"
#include "event.h"

void		new_explo(t_env *env)
{
	t_anim	*anim;

	anim = anim_new(&env->objects[0], ANIM_LOOP, 2);
	if (alist_push(&env->anims, anim) == ERROR)
		return ;
}

static int	loop(t_env *env)
{
	int			loop;
	SDL_Event	event;
	const Uint8	*state;

	new_explo(env);
	if (render_prepare(env) == ERROR)
		return (ERROR);
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
		update_player(env);
		anim_compute(&env->sdl, &env->anims);
		sdl_update_texture(&env->sdl);
		tp_wait_for_queue(env->tpool);
		compute_sprites(env);
		sdl_render(&env->sdl);
		sdl_get_fps(env->show_fps);
	}
	render_clean(env);
	return (SUCCESS);
}

int			main(int ac, char **av)
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
