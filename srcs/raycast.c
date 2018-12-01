/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:57:36 by vparis            #+#    #+#             */
/*   Updated: 2018/12/01 16:48:04 by vparis           ###   ########.fr       */
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

t_vec2	allow_move(t_map *map, t_vec2 from, t_vec2 to, t_vec2 calc)
{
	t_vec2	offset;

	calc = clamp_vec2(calc, VEC2_ZERO, \
				VEC2_INIT((t_float)map->width - 0.1,
					(t_float)map->height - 0.1));
	offset.x = ((to.x < 0) ? -0.1 : 0.1);
	offset.y = ((to.y < 0) ? -0.1 : 0.1);
	if (map->data[(int)from.x][(int)(calc.y + offset.y)] != 0)
		calc.y = from.y;
	if (map->data[(int)(calc.x + offset.x)][(int)from.y] != 0)
		calc.x = from.x;
	if (map->data[(int)(calc.x + offset.x)][(int)(calc.y + offset.y)] != 0)
		calc = from;
	return (calc);
}

t_vec2	move_forward(t_map *map, t_vec2 from, t_vec2 to, t_float speed)
{
	t_vec2	ret;

	if (speed < 0)
	{
		to = VEC2_INIT(-to.x, -to.y);
		speed = -speed;
	}
	ret = from + to * speed;
	return (allow_move(map, from, to, ret));
}

t_vec2	straf(t_map *map, t_vec2 from, t_vec2 to, t_float speed)
{
	to = VEC2_INIT(to.y, -to.x);
	return (move_forward(map, from, to, speed));
}

void	render(t_env *env, t_ivec2 range)
{
	int			x;
	t_cam		*cam;
	t_hit_infos	infos;

	cam = &env->cam;
	infos.ray.pos = cam->pos;
	x = range.x;
	while (x < range.y)
	{
		infos.map = VEC2_INIT(floor(cam->pos.x), floor(cam->pos.y));
		infos.ray.dir = cam->dir + cam->plane *
			((x << 1) / env->sdl.canvas_w - 1.0);
		//no hit = skybox
		raycast(&infos, &env->map, env, x);
		rc_render(&env->sdl, &env->cam, &env->map, &infos);
		x++;
	}
}

int			start_render(void *data)
{
	t_algo		*algo;

	algo = (t_algo *)data;
	render(algo->env, IVEC2_INIT((int)algo->start, (int)algo->end));
	return (SUCCESS);
}
