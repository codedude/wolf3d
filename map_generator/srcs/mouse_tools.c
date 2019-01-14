/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:20:05 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/31 00:39:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

t_ivec2		get_mouse_pos(void)
{
	int			x;
	int			y;

	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	return (IVEC2_INIT(x, y));
}

void		update_mouse_pos(t_env *env)
{
	int			x;
	int			y;

	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	env->mouse.last_pos = env->mouse.pos;
	env->mouse.pos = IVEC2_INIT(x, y);
	env->mouse.rel_pos = env->mouse.pos - env->mouse.last_pos;
}
