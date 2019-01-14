/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_door_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 16:34:09 by vparis            #+#    #+#             */
/*   Updated: 2019/01/14 16:08:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "raycast.h"
#include "ft_type.h"
#include "types.h"

void			get_wall_xz(t_hit_infos *infos, t_vec2 dir, t_vec2 dist_step)
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

void			simu_wall_xz(t_hit_infos *infos, t_vec2 map_tmp,
					t_vec2 dist[3], int side)
{
	t_vec2	map_save;
	int		side_save;

	map_save = infos->map;
	side_save = infos->side;
	infos->map = map_tmp;
	infos->side = side;
	get_wall_xz(infos, infos->ray.dir, dist[STEP]);
	infos->map = map_save;
	infos->side = side_save;
}

/*
** Check map bounds
*/

t_bool			cmap(int x, int y, int max_x, int max_y)
{
	if (x < 0 || y < 0 || x >= max_x || y >= max_y)
		return (False);
	return (True);
}
