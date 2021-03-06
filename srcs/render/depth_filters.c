/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth_filters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:37:23 by vparis            #+#    #+#             */
/*   Updated: 2019/01/28 13:43:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "types.h"

static t_float	compute_depth(t_float z)
{
	if (z > MAX_DEPTH)
		return (0.05f);
	else
		return (1.0f - (z / MAX_DEPTH));
}

t_vec3			depth_filter_depth(t_vec3 color, t_float depth)
{
	depth = compute_depth(depth);
	return (color * depth);
}

t_vec3			depth_filter_fog(t_vec3 color, t_float depth)
{
	depth = compute_depth(depth);
	return (color * depth + FOG_AMBIENT * (1.0f - depth));
}

t_vec3			depth_filter_water(t_vec3 color, t_float depth)
{
	depth = compute_depth(depth) / 2.0f;
	return (color * depth + WATER_AMBIENT * (1.0f - depth));
}
