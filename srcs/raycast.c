/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:57:36 by vparis            #+#    #+#             */
/*   Updated: 2018/12/06 19:09:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"
#include "types.h"

/*
** TODO: lookup table infos.ray.dir
*/

void	render(t_env *env, int start, int end, int step)
{
	int			x;
	t_cam		*cam;
	t_hit_infos	infos;

	cam = &env->cam;
	infos.ray.pos = cam->pos;
	x = start;
	while (x < end)
	{
		infos.map = VEC2_INIT(floor(cam->pos.x), floor(cam->pos.y));
		infos.ray.dir = cam->dir + -cam->plane *
			((t_float)(x << 1) / env->sdl.canvas_w - 1.0);
		raycast(&infos, &env->map, env, x);
		rc_render(&env->sdl, &env->cam, &env->map, &infos);
		x += step;
	}
}

int		start_render(void *data)
{
	t_algo		*algo;

	algo = (t_algo *)data;
	render(algo->env, algo->start, algo->end, algo->step);
	return (SUCCESS);
}
