/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/29 01:03:07 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/20 22:25:32 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"

static void		precalc_xy_draw(t_env *env, t_map_info *minf)
{
	t_map		*map;
	t_vec2		pos;
	t_vec2		size;
	t_ivec2		i;

	map = minf->map;
	pos = (minf->pos - minf->map_center) * minf->zoom;
	size = VEC2_INIT((t_float)map->size.x, (t_float)map->size.y) * minf->zoom;
	i.y = 0;
	while (i.y < map->size.y + 1)
	{
		minf->y_draw[i.y] = (int)round(pos.y + (i.y /
				(t_float)map->size.y) * size.y + minf->grid_center.y);
		minf->y_draw[i.y] += env->grid.pos.y;
		i.y++;
	}
	i.x = 0;
	while (i.x < map->size.x + 1)
	{
		minf->x_draw[i.x] = (int)round(pos.x + (i.x /
				(t_float)map->size.x) * size.x + minf->grid_center.x);
		minf->x_draw[i.x] += env->grid.pos.x;
		i.x++;
	}
}

static void		get_start_end(t_env *env, t_map_info *minf,
								t_ivec2 *start, t_ivec2 *end)
{
	t_map		*map;
	int			cmp;
	t_ivec2		i;

	map = minf->map;
	cmp = env->grid.pos.y + env->grid.size.y;
	i.y = 0;
	while (i.y < map->size.y)
	{
		if (start->y > i.y && minf->y_draw[i.y + 1] >= 0)
			start->y = i.y;
		if (end->y <= i.y && minf->y_draw[i.y] < cmp)
			end->y = i.y + 1;
		i.y++;
	}
	cmp = env->grid.pos.x + env->grid.size.x;
	i.x = 0;
	while (i.x < map->size.x)
	{
		if (start->x > i.x && minf->x_draw[i.x + 1] >= 0)
			start->x = i.x;
		if (end->x <= i.x && minf->x_draw[i.x] < cmp)
			end->x = i.x + 1;
		i.x++;
	}
}

void			draw_map(t_env *env, t_sdl *sdl)
{
	t_ivec2		start;
	t_ivec2		i;
	t_ivec2		end;
	t_map_info	*minf;

	minf = &env->map_info;
	start = minf->map->size;
	end = -1;
	precalc_xy_draw(env, minf);
	get_start_end(env, minf, &start, &end);
	i.y = start.y;
	while (i.y < end.y)
	{
		i.x = start.x;
		while (i.x < end.x)
		{
			draw_node(env, sdl, minf, i);
			i.x++;
		}
		i.y++;
	}
}
