/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 00:33:30 by vparis            #+#    #+#             */
/*   Updated: 2019/01/12 00:40:56 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "sdl_m.h"
#include "ft_type.h"
#include "event.h"

t_bool		compute_event(t_env *env)
{
	SDL_Event	event;
	const Uint8	*state;
	t_bool		ret;

	ret = True;
	SDL_PumpEvents();
	state = SDL_GetKeyboardState(NULL);
	event_kb_state(state, env);
	while (SDL_PollEvent(&event))
	{
		ret = event_kb_poll(&event, env);
		if (ret == False)
			break ;
	}
	return (ret);
}
