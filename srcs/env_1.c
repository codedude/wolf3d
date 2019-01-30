/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:00:41 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:16:23 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_math.h"
#include "libtpool.h"
#include "sdl_m.h"
#include "audio.h"
#include "env.h"
#include "types.h"
#include "raycast.h"
#include "event.h"
#include "parser.h"
#include "camera.h"
#include "player.h"

static int	env_init_sdl(t_env *env)
{
	if (sdl_init(&env->sdl, WINDOW_NAME, WINDOW_WIDTH, WINDOW_HEIGHT) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if (audio_init(&env->audio) == ERROR)
	{
		ft_putstr_fd("Sound system can't start\n", 2);
		return (ERROR);
	}
	if (text_init(&env->sdl.text) == ERROR)
	{
		ft_putstr_fd("Text system can't start\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

int			env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(*env));
	if (env_init_sdl(env) == ERROR)
		return (ERROR);
	if ((env->tpool = tp_create(THREADS, TP_FPS_MODE)) == NULL)
	{
		ft_putstr_fd("Thread pool can't start\n", 2);
		return (ERROR);
	}
	if (wolf_init(env, filename) == ERROR)
	{
		ft_putstr_fd("Can't init wolf\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

void		env_destroy(t_env *env)
{
	tp_destroy(&env->tpool);
	audio_destroy(&env->audio);
	text_destroy(&env->sdl.text);
	klist_clear(&env->player.inventory);
	wolf_destroy(env, &env->map);
	sdl_destroy(&env->sdl);
}
