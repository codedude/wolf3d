/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_filters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 21:37:23 by vparis            #+#    #+#             */
/*   Updated: 2018/12/04 12:08:03 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "types.h"

t_vec3			color_filter_baw(t_vec3 c)
{
	c[0] = c[0] * 0.21 + c[1] * 0.72 + c[2] * 0.07;
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
		half_clamp_float(0.393 * c[0] + 0.769 * c[1] + 0.189 * c[2], 255.0),
		half_clamp_float(0.349 * c[0] + 0.686 * c[1] + 0.168 * c[2], 255.0),
		half_clamp_float(0.272 * c[0] + 0.534 * c[1] + 0.131 * c[2], 255.0));
	return (c);
}