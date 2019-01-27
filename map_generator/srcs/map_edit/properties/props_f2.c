/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_f2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:01:59 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:02:05 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void				mprops_act_size_x_up(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;

	env = (t_env*)v_env;
	minf = &env->map_info;
	if (minf->map->size.x < MAX_SZ_X)
	{
		minf->map->size.x++;
		map_update_center(env);
	}
}

void				mprops_act_size_x_down(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;

	env = (t_env*)v_env;
	minf = &env->map_info;
	if (minf->map->size.x > MIN_SZ_X)
	{
		minf->map->size.x--;
		map_update_center(env);
	}
}

void				mprops_act_size_y_up(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;

	env = (t_env*)v_env;
	minf = &env->map_info;
	if (minf->map->size.y < MAX_SZ_Y)
	{
		minf->map->size.y++;
		map_update_center(env);
	}
}

void				mprops_act_size_y_down(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;

	env = (t_env*)v_env;
	minf = &env->map_info;
	if (minf->map->size.y > MIN_SZ_Y)
	{
		minf->map->size.y--;
		map_update_center(env);
	}
}
