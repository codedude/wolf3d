/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/21 17:15:05 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"
#include "entity.h"
#include "anim.h"
#include "event.h"

static void	test(t_env *env)
{
	t_anim *anim;

	if (env->objects_nb == 0)
		return ;
	anim = anim_new(&env->objects[0], ANIM_TEXTURE | ANIM_LOOP, False, 1);
	alist_push(&env->anims, anim);
}

void		draw_interface(t_env *env)
{
	char	fps[16];

	ft_itoa_to_buffer(env->sdl.fps, fps);
	text_write(env, env->sdl.width - 40, env->sdl.height - 32,
		fps);
}

static int	loop(t_env *env)
{
	if (render_prepare(env) == ERROR)
		return (ERROR);
	test(env);
	while (compute_event(env) == True)
	{
		sdl_get_fps(&env->sdl);
		compute_player(env);
		compute_anim(env, &env->anims);
		sdl_update_texture(&env->sdl);
		tp_wait_for_queue(env->tpool);
		compute_sprite(env);
		draw_interface(env);
		sdl_render(&env->sdl);
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
