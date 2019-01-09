/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:45:12 by vparis            #+#    #+#             */
/*   Updated: 2019/01/02 16:22:12 by vparis           ###   ########.fr       */
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

static void		get_wall_xz(t_hit_infos *infos, t_vec2 dir, t_vec2 dist_step)
{
	t_float		wall_x;
	t_float		z;

	if (infos->side == 0)
	{
		z = (infos->map.x - infos->ray.pos.x
			+ (infos->is_thin == 0 ? (1.0 - dist_step.x) / 2.0 : 0)) / dir.x;
		wall_x = infos->ray.pos.y + z * dir.y;
	}
	else
	{
		z = (infos->map.y - infos->ray.pos.y
			+ (infos->is_thin == 0 ? (1.0 - dist_step.y) / 2.0 : 0)) / dir.y;
		wall_x = infos->ray.pos.x + z * dir.x;
	}
	infos->wall_x = wall_x - floor(wall_x);
	infos->z = z;
}

int				thin_wall_ew(t_vec2 dist[3], t_hit_infos *infos, t_map *map,
							t_doorz *door)
{
	t_ivec2	map_pos;
	t_vec2	dist_side;
	int		sens;
	int		side;
	t_vec2	map_tmp;
	t_vec2	map_save;
	int		side_save;

	dist_side = dist[SIDE];
	map_tmp = infos->map;
	if (dist_side.x < dist_side.y)
	{
		dist_side.x += dist[DELTA].x;
		map_tmp.x += dist[STEP].x;
		side = 0;
	}
	else
	{
		dist_side.y += dist[DELTA].y;
		map_tmp.y += dist[STEP].y;
		side = 1;
	}
	map_pos = IVEC2_INIT((int)map_tmp.x, (int)map_tmp.y);
	if (map_pos.x < 0 || map_pos.y < 0
		|| map_pos.x >= map->width || map_pos.y >= map->height)
		return (0);
	sens = dist[STEP].y < 0 ? -1 : 1;
	if (side == 0)
	{
		map_save = infos->map;
		side_save = infos->side;
		infos->map = map_tmp;
		infos->side = side;
		get_wall_xz(infos, infos->ray.dir, dist[STEP]);
		infos->map = map_save;
		infos->side = side_save;
		if ((sens == -1 && infos->wall_x > 0.5)
			|| (sens == 1 && infos->wall_x < 0.5))
			return (0);
	}
	//vérifier l'ouverture
	t_float t;
	t_float sol_x;
	t = ((infos->map.y + 0.5) - infos->ray.pos.y) / infos->ray.dir.y;
	sol_x = infos->ray.pos.x + infos->ray.dir.x * t;
	if (sol_x > infos->map.x + door->open_offset)
		return (0);
	infos->map.y += 0.5;
	infos->is_thin = 1;
	infos->tex_off_x = door->open_offset;
	return (1);
}

int				thin_wall_ns(t_vec2 dist[3], t_hit_infos *infos, t_map *map,
							t_doorz *door)
{
	t_ivec2	map_pos;
	t_vec2	dist_side;
	int		sens;
	int		side;
	t_vec2	map_tmp;
	t_vec2	map_save;
	int		side_save;

	dist_side = dist[SIDE];
	map_tmp = infos->map;
	if (dist_side.x < dist_side.y)
	{
		dist_side.x += dist[DELTA].x;
		map_tmp.x += dist[STEP].x;
		side = 0;
	}
	else
	{
		dist_side.y += dist[DELTA].y;
		map_tmp.y += dist[STEP].y;
		side = 1;
	}
	map_pos = IVEC2_INIT((int)map_tmp.x, (int)map_tmp.y);
	if (map_pos.x < 0 || map_pos.y < 0
		|| map_pos.x >= map->width || map_pos.y >= map->height)
		return (0);
	sens = dist[STEP].x < 0 ? -1 : 1;
	if (side == 1)
	{
		map_save = infos->map;
		side_save = infos->side;
		infos->map = map_tmp;
		infos->side = side;
		get_wall_xz(infos, infos->ray.dir, dist[STEP]);
		infos->map = map_save;
		infos->side = side_save;
		if ((sens == -1 && infos->wall_x > 0.5)
			|| (sens == 1 && infos->wall_x < 0.5))
		{
			return (0);
		}

	}
	//vérifier l'ouverture
	t_float t;
	t_float sol_y;
	t = ((infos->map.x + 0.5) - infos->ray.pos.x) / infos->ray.dir.x;
	sol_y = infos->ray.pos.y + infos->ray.dir.y * t;
	if (sol_y > infos->map.y + door->open_offset)
		return (0);
	infos->is_thin = 1;
	infos->map.x += 0.5;
	infos->tex_off_x = door->open_offset;
	return (1);
}

static int		get_hit_value(t_vec2 dist[3], t_hit_infos *infos, t_map *map,
								t_ivec2	map_pos)
{
	t_doorz	*door;
	int		hit;

	hit = 0;
	if (map->data[map_pos.y][map_pos.x] > 0)
	{
		door = &map->doors[map_pos.y][map_pos.x];
		if (door->is_door == False)
			hit = 1;
		else if (door->orientation == 0)
			hit = thin_wall_ew(dist, infos, map, door);
		else if (door->orientation == 1)
			hit = thin_wall_ns(dist, infos, map, door);
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
	infos->is_thin = 0;
	infos->tex_off_x = 0.0;
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
