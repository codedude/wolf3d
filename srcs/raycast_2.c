/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:45:12 by vparis            #+#    #+#             */
/*   Updated: 2018/12/11 18:29:21 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "raycast.h"
#include "types.h"

static void		raycast_init(t_vec2 dist[3], t_hit_infos *infos)
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

static int		raycast_compute(t_vec2 dist[3], t_hit_infos *infos, t_map *map,
					int **map_data)
{
	int		hit;
	t_ivec2	map_pos;

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
		map_pos = IVEC2_INIT((int)infos->map.x, (int)infos->map.y);
		if (map_pos.x < 0 || map_pos.y < 0
			|| map_pos.x >= map->width || map_pos.y >= map->height)
			break ;
		if (map_data[map_pos.y][map_pos.x] > 0)
			hit = 1;
	}
	return (hit);
}

static void		get_wall_xz(t_hit_infos *infos, t_vec2 dir, t_vec2 dist_step)
{
	t_float		wall_x;
	t_float		z;

	if (infos->side == 0)
	{
		z = (infos->map.x - infos->ray.pos.x
			+ (1.0 - dist_step.x) / 2.0) / dir.x;
		wall_x = infos->ray.pos.y + z * dir.y;
	}
	else
	{
		z = (infos->map.y - infos->ray.pos.y
			+ (1.0 - dist_step.y) / 2.0) / dir.y;
		wall_x = infos->ray.pos.x + z * dir.x;
	}
	infos->wall_x = wall_x - floor(wall_x);
	infos->z = z;
}

static t_ivec2	init_draw(int line_height, t_sdl *sdl, t_cam *cam,
							t_hit_infos *infos)
{
	t_ivec2	draw;

	draw.y = (int)(
		(line_height + sdl->height) / 2.0
		- (sdl->half_canvas_h - cam->z) / infos->z
		+ cam->height);
	draw.x = draw.y - line_height;
	return (clamp_ivec2(draw, 0, sdl->height));
}

int				raycast(t_hit_infos *infos, t_map *map, t_env *env, int x)
{
	t_vec2	dist[3];
	t_ivec2	draw;
	t_vec2	dir;

	dir = infos->ray.dir;
	dist[DELTA] = VEC2_INIT(fabs(1.0 / dir.x), fabs(1.0 / dir.y));
	raycast_init(dist, infos);
	infos->hit = raycast_compute(dist, infos, map, map->data);
	get_wall_xz(infos, dir, dist[STEP]);
	infos->line_height = (int)(env->sdl.canvas_h / infos->z);
	draw = init_draw(infos->line_height, &env->sdl, &env->cam, infos);
	env->sdl.z_buffer[x] = infos->z;
	infos->x = x;
	infos->draw_start = draw.x;
	infos->draw_end = draw.y;
	return (infos->hit);
}
