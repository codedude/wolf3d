/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:14:38 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static int			env_init2(t_env *env, char *filename)
{
	t_map		*map;

	map = env->map_info.map;
	env->save_file = filename;
	env->space = 0;
	env->alt = 0;
	if (env->loaded == False)
	{
		env->spawn = IVEC2_INIT(map->size.x / 2, map->size.y / 2);
		env->spawn_rotation = 0;
	}
	env->cpick.kframe = 0;
	env->saved = True;
	button_setactive(env->editor.switch_b[Painter], True);
	mouse_track_init(env);
	palette_init(env);
	init_toolset(&env->toolset);
	return (SUCCESS);
}


int					env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(*env));
	if (is_valid_mapfile(filename) == False)
		return (ERROR);
	if (sdl_init(&env->sdl, MAP_GEN_NAME, WIN_X, WIN_Y) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if (init_map_info(env, &env->map_info, filename) == ERROR
	|| init_rpanels(&env->sdl, &env->rpan) == ERROR
	|| env_create_inspect(env) == ERROR
	|| editor_init(env, &env->sdl, &env->editor) == ERROR)
	{
		perror("W3dEditor");
		return (ERROR);
	}
	return (env_init2(env, filename));
}
