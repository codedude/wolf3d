/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid_lines.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/29 04:05:23 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"
// 
// void			draw_grid_lines(t_env *env, t_sdl *sdl)
// {
// 	t_ivec2		i;
// 	t_vec2		factor;
// 	t_vec2		i_z;
//
// 	env->ns_zoom = (t_float)env->node_size * env->zoom;
// 	factor.x = (t_float)(env->map->size.x / 2.0) * env->ns_zoom;
// 	factor.y = (t_float)(env->map->size.y / 2.0) * env->ns_zoom;
// 	i.y = 0;
// 	i_z.y = 0;
// 	while (i.y < env->map->size.y)
// 	{
// 		i_z.x = 0;
// 		env->map_topleft.y = i_z.y - factor.y;
// 		i.x = 0;
// 		while (i.x < env->map->size.x)
// 		{
// 			env->map_topleft.x = i_z.x - factor.x;
// 			draw_node(env, sdl, i);
// 			i.x++;
// 			i_z.x += env->ns_zoom;
// 		}
// 		i.y++;
// 		i_z.y += env->ns_zoom;
// 	}
// }
