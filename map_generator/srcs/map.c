/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/21 04:08:04 by jbulant          ###   ########.fr       */
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
	while (y < MAX_SIZE_Y)
	{
		x = 0;
		while (x < MAX_SIZE_X)
		{
			map->data[y][x].id = x + y * MAX_SIZE_X;
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

void 		clear_map(t_map_info *m_inf)
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

void		free_ar_data(void **tab, size_t size)
{
	size_t		i;

	if (!tab)
		return ;
	i = 0;
	while (i < size)
	{
		free(tab[i]);
		++i;
	}
	free(tab);
}

void		**new_ar_data(size_t height, size_t width)
{
	void	**data;
	int		i;

	if (!(data = (void **)ft_memalloc(sizeof(void *) * height)))
		return (NULL);
	i = 0;
	while (i < MAX_SIZE_Y)
	{
		if (!(data[i] = ft_memalloc(width)))
		{
			free_ar_data(data, height);
			return (NULL);
		}
		++i;
	}
	return (data);
}

t_map		*map_new(t_ivec2 size)
{
	t_map	*map;

	if (!(map = (t_map*)malloc(sizeof(*map))))
		return (NULL);
	map->size = size;
	if ((map->data = new_map_data(MAX_SIZE_X, MAX_SIZE_Y)) == NULL)
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
	// free_ar_data((void **)map->data, MAX_SIZE_Y);
	destroy_map_data(&map->data, MAX_SIZE_X, MAX_SIZE_Y);
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
