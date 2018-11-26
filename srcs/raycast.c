/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:57:36 by vparis            #+#    #+#             */
/*   Updated: 2018/11/26 19:12:13 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"

t_vec2	allow_move(t_map *map, t_vec2 from, t_vec2 to, t_vec2 calc)
{
	t_vec2	offset;

	calc = clamp_vec2(calc, 0, \
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

void	draw_line(t_sdl *sdl, int x, t_ivec2 range, int color)
{
	int		i;

	i = range.x;
	while (i < range.y)
	{
		sdl->image[x + i * sdl->width] = color;
		i++;
	}
}

void	render(t_sdl *sdl, t_cam *cam, t_map *map, t_ivec2 range)
{
	int			x;
	t_hit_infos	infos;

	infos.ray.pos = cam->pos;
	x = range.x;
	while (x < range.y)
	{
		infos.map = VEC2_INIT(floor(cam->pos.x), floor(cam->pos.y));
		infos.ray.dir = cam->dir + cam->plane *
			(2.0 * x / (t_float)sdl->width - 1.0);
		raycast(&infos, map, sdl, x);
		rc_render(sdl, cam, map, &infos);
		x++;
	}
}

int			start_render(void *data)
{
	t_algo		*algo;
	t_env		*env;

	algo = (t_algo *)data;
	env = algo->env;
	render(&env->sdl, &env->cam, &env->map,
		IVEC2_INIT((int)algo->start, (int)algo->end));
	return (SUCCESS);
}
