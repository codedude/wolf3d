/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/19 19:14:31 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

t_map		*create_new_map(t_ivec2 size)
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
	t_canvas	bounds;
	t_ivec2		mpos;

	mpos = get_mouse_pos();
	bounds = get_map_boundaries(env);
	if (is_bounded(mpos, env->grid) && is_bounded(mpos, bounds))
	{
		mpos = mpos_to_map_index(bounds, mpos, env);
		if (env->user_action == Set_Spawn)
			env->spawn = mpos;
		else if (env->user_action == Draw_Wall)
			env->map->data[mpos.y][mpos.x] = brush;
		else if (env->user_action == Erase_Wall)
			env->map->data[mpos.y][mpos.x] = 0;
		env->saved = False;
	}
}
