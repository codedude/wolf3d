/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:18:45 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "parser.h"
#include "algo.h"
#include "libft.h"

int			data_set_ids(t_map *map)
{
	int			x;
	int			y;

	y = 0;
	while (y < MAX_SZ_Y)
	{
		x = 0;
		while (x < MAX_SZ_X)
		{
			map->data[y][x].id = x + y * MAX_SZ_X;
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

void		clear_map(t_map_info *m_inf)
{
	t_ivec2		i;

	i.y = 0;
	while (i.y < m_inf->map->size.y)
	{
		i.x = 0;
		while (i.x < m_inf->map->size.x)
		{
			m_inf->tmp_data[i.y][i.x] = 0;
			i.x++;
		}
		i.y++;
	}
}

t_map		*map_new(t_ivec2 size)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(*map))))
		return (NULL);
	map->size = size;
	if ((map->data = new_map_data(MAX_SZ_X, MAX_SZ_Y)) == NULL)
	{
		destroy_map(map);
		return (NULL);
	}
	data_set_ids(map);
	return (map);
}

void		destroy_map(t_map *map)
{
	if (!map)
		return ;
	destroy_map_data(&map->data, MAX_SZ_X, MAX_SZ_Y);
	free(map);
}

void		map_usebrush(t_env *env, int brush)
{
	int			old_brush;
	t_u32		type;
	t_canvas	bounds;

	bounds = get_map_boundaries(env);
	if (is_bounded(env->mouse.pos, env->grid)
	&& is_bounded(env->mouse.pos, bounds))
	{
		type = toolset_get_type(&env->toolset);
		old_brush = env->palette.brush;
		env->palette.brush = type == Eraser ? -1 : brush;
		if (type == SpawnSetter)
			env->spawn = mpos_to_map_index(bounds, env);
		else
			env->palette.b_fx[env->inspector.b_select.type](env, bounds);
		env->palette.brush = old_brush;
	}
}
