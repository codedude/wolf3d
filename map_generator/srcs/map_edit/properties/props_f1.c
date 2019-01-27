/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   props_f1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 23:57:30 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:02:09 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void				mprops_act_scale_up(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;
	t_float		factor;

	env = (t_env*)v_env;
	minf = &env->map_info;
	factor = 1.0 + (env->map_properties.tick / 60.0 * 0.05);
	if (factor != 0.0)
		minf->zoom *= factor;
	if (minf->zoom > minf->zoom_max)
		minf->zoom = minf->zoom_max;
}

void				mprops_act_scale_down(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;
	t_float		factor;

	env = (t_env*)v_env;
	minf = &env->map_info;
	factor = 1.0 + (env->map_properties.tick / 60.0 * 0.05);
	if (factor != 0.0)
		minf->zoom /= factor;
	if (minf->zoom < minf->zoom_min)
		minf->zoom = minf->zoom_min;
}

void				mprops_act_recenter(void *v_env)
{
	t_env		*env;

	env = (t_env*)v_env;
	env->map_info.pos = 0;
	map_scale2grid(env);
}
