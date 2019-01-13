/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/13 16:49:04 by vparis           ###   ########.fr       */
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

static int	loop(t_env *env)
{
	if (render_prepare(env) == ERROR)
		return (ERROR);
	while (compute_event(env) == True)
	{
		compute_player(env);
		compute_anim(&env->sdl, &env->anims);
		sdl_update_texture(&env->sdl);
		tp_wait_for_queue(env->tpool);
		compute_sprite(env);
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
		//sdl_print_infos(&env.sdl);
		SDL_SetRelativeMouseMode(SDL_TRUE);
		loop(&env);
	}
	env_destroy(&env);
	return (0);
}
