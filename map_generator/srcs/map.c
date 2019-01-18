/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/18 16:54:24 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "algo.h"
#include "libft.h"

void 		clear_map(t_map *map)
{
	t_ivec2		i;

	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			map->data[i.y][i.x] = 0;
			i.x++;
		}
		i.y++;
	}
}

t_map		*map_new(t_ivec2 size)
{
	t_map	*map;
	int		i;

	if (!(map = (t_map*)malloc(sizeof(*map))))
		return (NULL);
	map->size = size;
	if (!(map->data = (int **)ft_memalloc(sizeof(int *) * MAX_SIZE_Y)))
		return (NULL);
	i = 0;
	while (i < MAX_SIZE_Y)
	{
		if (!(map->data[i] = (int *)ft_memalloc(sizeof(int) * MAX_SIZE_X)))
			return (NULL);
		i++;
	}
	return (map);
}

void		destroy_map(t_map *map)
{
	int		i;

	if (!map)
		return ;
	if (map->data)
	{
		i = 0;
		while (i < MAX_SIZE_Y)
		{
			if (map->data[i])
				free(map->data[i]);
			i++;
		}
		free(map->data);
	}
	free(map);
}

void		draw_on_map(t_env *env, int brush)
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
