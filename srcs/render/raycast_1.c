/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:45:12 by vparis            #+#    #+#             */
/*   Updated: 2019/01/29 20:25:20 by jbulant          ###   ########.fr       */
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

static t_ivec2	init_draw(int line_height, t_sdl *sdl, t_cam *cam,
							t_hit_infos *infos)
{
	t_ivec2	draw;

	draw.y = (int)((line_height + sdl->height) / 2.0f
		- (sdl->half_canvas_h - cam->z) / infos->z + cam->height);
	draw.x = draw.y - line_height;
	return (clamp_ivec2(draw, 0, sdl->height));
}

static int		get_hit_value(t_vec2 dist[3], t_hit_infos *infos, t_map *map,
					t_ivec2 map_pos)
{
	int		hit;

	hit = 0;
	if (map->data[map_pos.y][map_pos.x].type != ENTITY_VOID)
	{
		if (map->data[map_pos.y][map_pos.x].type != ENTITY_DOOR)
			return (1);
		infos->e_door = &map->data[map_pos.y][map_pos.x];
		if (infos->e_door->e.door->orientation == DOOR_EW)
			hit = thin_wall_ew(dist, infos, map, infos->e_door->e.door);
		else
			hit = thin_wall_ns(dist, infos, map, infos->e_door->e.door);
	}
	return (hit);
}

static int		raycast_compute(t_vec2 dist[3], t_hit_infos *infos, t_map *map)
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
		hit = get_hit_value(dist, infos, map, map_pos);
	}
	return (hit);
}

static void		raycast_init(t_vec2 dist[3], t_hit_infos *infos)
{
	t_ray	ray;
	t_vec2	map_pos;

	ray = infos->ray;
	map_pos = infos->map;
	if (ray.dir.x < 0.0f)
	{
		dist[STEP].x = -1.0f;
		dist[SIDE].x = (ray.pos.x - map_pos.x) * dist[DELTA].x;
	}
	else
	{
		dist[STEP].x = 1.0f;
		dist[SIDE].x = (map_pos.x + 1.0f - ray.pos.x) * dist[DELTA].x;
	}
	if (ray.dir.y < 0.0f)
	{
		dist[STEP].y = -1.0f;
		dist[SIDE].y = (ray.pos.y - map_pos.y) * dist[DELTA].y;
	}
	else
	{
		dist[STEP].y = 1.0f;
		dist[SIDE].y = (map_pos.y + 1.0f - ray.pos.y) * dist[DELTA].y;
	}
}

int				raycast(t_hit_infos *infos, t_map *map, t_env *env, int x)
{
	t_vec2	dist[3];
	t_ivec2	draw;
	t_vec2	dir;

	dir = infos->ray.dir;
	dist[DELTA] = VEC2_INIT(fabsf(1.0f / dir.x), fabsf(1.0f / dir.y));
	raycast_init(dist, infos);
	infos->is_thin = 0;
	infos->tex_off_x = 0.0f;
	infos->e_door = NULL;
	if (map->data[(int)env->cam.pos.y][(int)env->cam.pos.x].type == ENTITY_DOOR)
		infos->e_door = &map->data[(int)env->cam.pos.y][(int)env->cam.pos.x];
	infos->hit = raycast_compute(dist, infos, map);
	get_wall_xz(infos, dir, dist[STEP]);
	infos->line_height = (int)(env->sdl.canvas_h / infos->z);
	draw = init_draw(infos->line_height, &env->sdl, &env->cam, infos);
	env->sdl.z_buffer[x] = infos->z;
	infos->x = x;
	infos->draw_start = draw.x;
	infos->draw_end = draw.y;
	return (infos->hit);
}
