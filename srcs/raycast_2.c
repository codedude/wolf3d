/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:45:12 by vparis            #+#    #+#             */
/*   Updated: 2018/11/28 02:13:33 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "raycast.h"

static void	raycast_init(t_vec2 dist[3], t_hit_infos *infos)
{
	t_ray	ray;
	t_vec2	map_pos;

	ray = infos->ray;
	map_pos = infos->map;
	if (ray.dir.x < 0.0)
	{
		dist[STEP].x = -1.0;
		dist[SIDE].x = (ray.pos.x - map_pos.x) * dist[DELTA].x;
	}
	else
	{
		dist[STEP].x = 1.0;
		dist[SIDE].x = (map_pos.x + 1.0 - ray.pos.x) * dist[DELTA].x;
	}
	if (ray.dir.y < 0.0)
	{
		dist[STEP].y = -1.0;
		dist[SIDE].y = (ray.pos.y - map_pos.y) * dist[DELTA].y;
	}
	else
	{
		dist[STEP].y = 1.0;
		dist[SIDE].y = (map_pos.y + 1.0 - ray.pos.y) * dist[DELTA].y;
	}
}

static int	raycast_compute(t_vec2 dist[3], t_hit_infos *infos, t_map *map)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (dist[SIDE].x < dist[SIDE].y)
		{
			dist[SIDE].x += dist[DELTA].x;
			infos->map.x += dist[STEP].x;
			infos->side = 0;
		}
		else
		{
			dist[SIDE].y += dist[DELTA].y;
			infos->map.y += dist[STEP].y;
			infos->side = 1;
		}
		if (map->data[(int)infos->map.x][(int)infos->map.y] > 0)
			hit = 1;
	}
	return (hit);
}

static t_float	get_wall_x(t_hit_infos *infos)
{
	t_float		wall_x;

	if (infos->side == 0)
		wall_x = infos->ray.pos.y + infos->z * infos->ray.dir.y;
	else
		wall_x = infos->ray.pos.x + infos->z * infos->ray.dir.x;
	return (wall_x - floor(wall_x));
}

static t_ivec2	init_draw(int line_height, t_sdl *sdl, t_cam *cam)
{
	t_ivec2		draw;

	draw.x = (int)floor(((t_float)-line_height / 2.0 + (t_float)sdl->height / 2.0) + (t_float)cam->height);
	draw.y = (int)floor(((t_float)line_height / 2.0 + (t_float)sdl->height / 2.0) + (t_float)cam->height);
	if (draw.x < 0)
		draw.x = 0;
	else if (draw.x > (int)sdl->height)
		draw.x = (int)sdl->height;
	if (draw.y > (int)sdl->height)
		draw.y = sdl->height;
	else if (draw.y < 0)
		draw.y = 0;
	return (draw);
}

int				raycast(t_hit_infos *infos, t_map *map, t_env *env, int x)
{
	t_vec2	dist[3];
	t_ivec2	draw;

	dist[DELTA] = VEC2_INIT(fabs(1.0 / infos->ray.dir.x),
		fabs(1.0 / infos->ray.dir.y));
	raycast_init(dist, infos);
	infos->hit = raycast_compute(dist, infos, map);
	if (infos->side == 0)
		infos->z = (infos->map.x - infos->ray.pos.x +
				(1.0 - dist[STEP].x) / 2.0) / infos->ray.dir.x;
	else
		infos->z = (infos->map.y - infos->ray.pos.y +
				(1.0 - dist[STEP].y) / 2.0) / infos->ray.dir.y;
	env->sdl.z_buffer[x] = infos->z;
	infos->wall_x = get_wall_x(infos);
	infos->x = x;
	infos->line_height = (int)(env->sdl.height / infos->z);
	draw = init_draw(infos->line_height, &env->sdl, &env->cam);
	infos->draw_start = draw.x;
	infos->draw_end = draw.y;
	return (infos->hit);
}
