/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_keyup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:25:39 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 23:07:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "render.h"
#include "bmp.h"

static int	manage_binds_up_4(SDL_Event *event, t_env *env, int *update)
{
	if (event->key.keysym.sym == KEY_RELOAD)
	{
		if (rt_reload(&env->rt) == SUCCESS)
		{
			if (sdl_resize(&env->sdl, env->rt.canvas.width,
				env->rt.canvas.height) == ERROR)
				return (-1);
			ft_putendl("Scene reloaded");
		}
	}
	else if (event->key.keysym.sym == KEY_MODE)
	{
		env->mode = !env->mode;
		if (env->mode)
			ft_putendl("Edition mode activated");
		else
		{
			env->obj_edit = NULL;
			ft_putendl("Edition mode deactivated");
		}
		*update = 0;
	}
	else
		*update = 1;
	return (1);
}

static int	manage_binds_up_3(SDL_Event *event, t_env *env, int *update)
{
	if (event->key.keysym.sym == KEY_SEPIA)
	{
		env->rt.blackwhite = 0;
		if ((env->rt.sepia = !env->rt.sepia))
			ft_putendl("Sepia mode activated");
		else
			ft_putendl("Sepia mode deactivated");
	}
	else if (event->key.keysym.sym == KEY_BW)
	{
		env->rt.sepia = 0;
		if ((env->rt.blackwhite = !env->rt.blackwhite))
			ft_putendl("Black&White mode activated");
		else
			ft_putendl("Black&White mode deactivated");
	}
	else
		return (manage_binds_up_4(event, env, update));
	return (1);
}

static int	manage_binds_up_2(SDL_Event *event, t_env *env, int *update)
{
	if (event->key.keysym.sym == KEY_SPEED)
	{
		if (env->speed_pos < 5.0)
		{
			ft_putendl("Speed mode activated");
			env->speed_ang = 4.0;
			env->speed_pos = 16.0;
		}
		else
		{
			ft_putendl("Speed mode deactivated");
			env->speed_ang = 1.0;
			env->speed_pos = 2.0;
		}
	}
	else
		return (manage_binds_up_3(event, env, update));
	return (1);
}

int			manage_binds_up(SDL_Event *event, t_env *env, int *update)
{
	*update = 1;
	if (event->key.keysym.sym == KEY_ESCAPE)
	{
		ft_putendl("Exiting...");
		return ((*update = 0));
	}
	else if (event->key.keysym.sym == KEY_FPS)
	{
		env->show_fps = !env->show_fps;
		if (env->show_fps)
			ft_putendl("FPS activated");
		else
			ft_putendl("FPS deactivated");
		*update = 0;
	}
	else if (event->key.keysym.sym == KEY_SAVE)
	{
		if (save_img(env->sdl.image, env->rt.canvas.width,
				env->rt.canvas.height) == ERROR)
			ft_putstr("Error : can't save image\n");
		*update = 0;
	}
	else
		return (manage_binds_up_2(event, env, update));
	return (1);
}
