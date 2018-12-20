/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/20 16:32:30 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static int		get_min_index(t_env *env, int pos[2], int max, int g_size)
{
	int		min;

	if (pos[0] >= pos[1] + g_size)
		min = max;
	else if (pos[0] > pos[1])
		min = 0;
	else
	{
		min = pos[1] - pos[0];
		min = (int)((t_float)min / ((t_float)env->node_size * env->zoom));
	}
	return (min);
}

static t_ivec2	get_node_min(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		i;

	i = 0;
	bounds = get_map_boundaries(env);
	i.x = get_min_index(env, (int[2]){bounds.pos.x, env->grid.pos.x},
						env->map->size.x, env->grid.size.x);
	i.y = get_min_index(env, (int[2]){bounds.pos.y, env->grid.pos.y},
						env->map->size.y, env->grid.size.y);
	return (i);
}

static int		get_max_index(t_env *env, int pos[2], int size[2])
{
	int		factor;
	int		max;

	factor = (int)((t_float)size[0] * ((t_float)env->node_size * env->zoom));
	if (pos[0] + factor <= pos[1])
		max = 0;
	else if (pos[0] + factor < pos[1] + size[1])
		max = size[0];
	else
	{
		max = (pos[0] + factor) - (pos[1] + size[1]);
		max = (int)((t_float)max / ((t_float)env->node_size * env->zoom));
		max = size[0] - max;
	}
	return (max);
}

static t_ivec2	get_node_max(t_env *env, t_map *map)
{
	t_ivec2		i;

	i.x = get_max_index(env, (int[2]){env->map_pos.x, env->grid.pos.x},
							(int[2]){env->map->size.x, env->grid.size.x});
	i.y = get_max_index(env, (int[2]){env->map_pos.y, env->grid.pos.y},
							(int[2]){env->map->size.y, env->grid.size.y});
	return (IVEC2_INIT(map->size.x, map->size.y));
}

void			draw_grid_lines(t_env *env, t_sdl *sdl)
{
	t_ivec2		i;
	t_ivec2		i_min;
	t_ivec2		i_max;

	i_min = get_node_min(env);
	i_max = get_node_max(env, env->map);
	env->ns_zoom = (t_float)env->node_size * env->zoom;
	i.y = i_min.y;
	while (i.y < i_max.y)
	{
		env->map_topleft.y = ((t_float)i.y - ((t_float)env->map->size.y / 2.0))
						* env->ns_zoom;
		i.x = i_min.x;
		while (i.x < i_max.x)
		{
			env->map_topleft.x = ((t_float)i.x
						- ((t_float)env->map->size.x / 2.0)) * env->ns_zoom;
			draw_node(env, sdl, i);
			i.x++;
		}
		i.y++;
	}
}
