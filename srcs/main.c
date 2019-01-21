/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/20 23:16:09 by jbulant          ###   ########.fr       */
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

static void	test_text(t_env *env)
{
	int		i;
	char	*texte = "Hello world !";
	t_tex	*tex;
	t_color	color;
	int		x_pad;

	tex = &(env->text.font_little);
	i = 0;
	x_pad = 10;
	while (texte[i] != 0)
	{
		int	key = texte[i] - 32;
		int	it_x, it_y;
		it_x = 0;
		while (it_x < tex->w)
		{
			it_y = 0;
			while (it_y < tex->h)
			{
				color = sdl_get_pixel(tex, it_x, it_y, key);
				if (color.rgba > 0)
					sdl_put_pixel(&env->sdl, it_x + i * tex->w + x_pad,
						10 + it_y, color);
				++it_y;
			}
			++it_x;
		}
		x_pad += 2;
		++i;
	}
}

static void	test(t_env *env)
{
	t_anim *anim;

	if (env->objects_nb == 0)
		return ;
	anim = anim_new(&env->objects[0], ANIM_TEXTURE | ANIM_LOOP, False, 1);
	alist_push(&env->anims, anim);
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
		compute_anim(&env->sdl, &env->anims);
		sdl_update_texture(&env->sdl);
		tp_wait_for_queue(env->tpool);
		compute_sprite(env);
		test_text(env);
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
