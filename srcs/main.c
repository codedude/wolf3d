/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/09 23:22:44 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"
#include "texture.h"
#include "entity.h"

void	prepare_threads(t_env *env, t_algo **pack)
{
	int			i;
	int			tasks;

	tasks = th_getnbr_proc();
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

void	calc_player(t_env *env)
{
	env->map.skybox_anim = (env->map.skybox_anim + 1)
						% (env->map.skybox.w * 2);
	player_set_acceleration(&env->cam);
	player_set_anim(&env->cam);
	player_set_z(&env->cam);
}

void	update_door(t_door *door)
{
	t_u32		cmp;
	t_float		cmp_val;
	t_float		off;

	if (door->is_open == True)
	{
		cmp = (door->open_offset < 0.0);
		cmp_val = 0.0;
		off = -ANIM_DOOR_OFFSET;
	}
	else
	{
		cmp = (door->open_offset > 1.0);
		cmp_val = 1.0;
		off = ANIM_DOOR_OFFSET;
	}
	door->open_offset += off;
	if (cmp)
	{
		door->open_offset = cmp_val;
		door->is_active = False;
	}
}

void	calc_doors(t_env *env)
{
	t_ivec2		i;
	t_map		*map;

	map = &env->map;
	i.y = 0;
	while (i.y < map->height)
	{
		i.x = 0;
		while (i.x < map->width)
		{
			if (map->data[i.y][i.x].type == ENTITY_DOOR
				&& map->data[i.y][i.x].e.door->is_active)
				update_door(map->data[i.y][i.x].e.door);
			i.x++;
		}
		i.y++;
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
		calc_player(env);
		calc_doors(env);
		sdl_update_texture(&env->sdl);
		tp_wait_for_queue(env->tpool);
		compute_sprites(env);
		sdl_render(&env->sdl);
		sdl_get_fps(env->show_fps);
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
