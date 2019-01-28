/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_filters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:37:23 by vparis            #+#    #+#             */
/*   Updated: 2019/01/28 13:42:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "types.h"

t_vec3			color_filter_baw(t_vec3 c)
{
	c[0] = c[2] * 0.21f + c[1] * 0.72f + c[0] * 0.07f;
	c[1] = c[0];
	c[2] = c[0];
	return (c);
}

static t_float	half_clamp_float(t_float f, t_float max)
{
	if (f > max)
		return (max);
	else
		return (f);
}

t_vec3			color_filter_sepia(t_vec3 c)
{
	c = VEC3_INIT(
		half_clamp_float(0.272f * c[0] + 0.534f * c[1] + 0.131f * c[2], 255.0f),
		half_clamp_float(0.349f * c[0] + 0.686f * c[1] + 0.168f * c[2], 255.0f),
		half_clamp_float(
			0.393f * c[0] + 0.769f * c[1] + 0.189f * c[2], 255.0f));
	return (c);
}
