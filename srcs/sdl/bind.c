/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 18:19:44 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 11:59:50 by vparis           ###   ########.fr       */
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

int		manage_binds(SDL_Event *event, t_env *env, int *update)
{
	const Uint8	*state;
	int			r;

	r = 1;
	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(event))
	{
		if (event->type == SDL_QUIT)
			r = 0;
		else if (event->type == SDL_KEYUP)
			r = manage_binds_up(event, env, update);
		else if (event->type == SDL_MOUSEBUTTONUP)
			r = manage_binds_mouse(event, env);
		if (r != 1)
			return (r);
	}
	r = manage_binds_down(env, update, state);
	return (r);
}
