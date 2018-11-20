/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_mouse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:30:32 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 14:57:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include <stdio.h>
#include "libft.h"
#include "env.h"
#include "rt.h"
#include "objects.h"
#include "render.h"
#include "bmp.h"

int		manage_binds_mouse(SDL_Event *event, t_env *env)
{
	t_object	*obj;

	if (!env->mode)
		return (1);
	if (event->button.button == SDL_BUTTON_LEFT)
	{
		if ((obj = get_hit_object(&env->rt, (int)event->button.x,
			(int)event->button.y)) != NULL)
			env->obj_edit = obj;
	}
	return (1);
}
