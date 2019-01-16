/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_door_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 15:45:07 by vparis            #+#    #+#             */
/*   Updated: 2019/01/16 10:47:21 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "raycast.h"
#include "ft_type.h"
#include "types.h"

static t_bool	check_door_open_ew(t_hit_infos *infos, t_door *door)
{
	t_float t;
	t_float sol;

	t = ((infos->map.y + 0.5) - infos->ray.pos.y) / infos->ray.dir.y;
	sol = infos->ray.pos.x + infos->ray.dir.x * t;
	if (sol > infos->map.x + door->open_offset)
		return (True);
	return (False);
}

static t_bool	check_door_open_ns(t_hit_infos *infos, t_door *door)
{
	t_float t;
	t_float sol;

	t = ((infos->map.x + 0.5) - infos->ray.pos.x) / infos->ray.dir.x;
	sol = infos->ray.pos.y + infos->ray.dir.y * t;
	if (sol > infos->map.y + door->open_offset)
		return (True);
	return (False);
}

static int		ray_step(t_vec2 dist[3], t_vec2 *map_tmp)
{
	if (dist[SIDE].x < dist[SIDE].y)
	{
		map_tmp->x += dist[STEP].x;
		return (0);
	}
	else
	{
		map_tmp->y += dist[STEP].y;
		return (1);
	}
}

int				thin_wall_ew(t_vec2 dist[3], t_hit_infos *infos, t_map *map,
					t_door *door)
{
	int		sens;
	int		side;
	t_vec2	map_tmp;

	map_tmp = infos->map;
	side = ray_step(dist, &map_tmp);
	if (cmap((int)map_tmp.x, (int)map_tmp.y, map->width, map->height) == False)
		return (0);
	sens = dist[STEP].y < 0 ? -1 : 1;
	if (side == 0)
	{
		simu_wall_xz(infos, map_tmp, dist, side);
		if ((sens == -1 && infos->wall_x > 0.5)
			|| (sens == 1 && infos->wall_x < 0.5))
			return (0);
	}
	if (check_door_open_ew(infos, door) == True)
		return (0);
	infos->is_thin = 1;
	infos->map.y += 0.5;
	infos->tex_off_x = door->open_offset;
	return (1);
}

int				thin_wall_ns(t_vec2 dist[3], t_hit_infos *infos, t_map *map,
					t_door *door)
{
	int		sens;
	int		side;
	t_vec2	map_tmp;

	map_tmp = infos->map;
	side = ray_step(dist, &map_tmp);
	if (cmap((int)map_tmp.x, (int)map_tmp.y, map->width, map->height) == False)
		return (0);
	sens = dist[STEP].x < 0 ? -1 : 1;
	if (side == 1)
	{
		simu_wall_xz(infos, map_tmp, dist, side);
		if ((sens == -1 && infos->wall_x > 0.5)
			|| (sens == 1 && infos->wall_x < 0.5))
			return (0);
	}
	if (check_door_open_ns(infos, door) == True)
		return (0);
	infos->is_thin = 1;
	infos->map.x += 0.5;
	infos->tex_off_x = door->open_offset;
	return (1);
}
