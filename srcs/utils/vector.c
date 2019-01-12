/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:41:23 by vparis            #+#    #+#             */
/*   Updated: 2019/01/12 00:57:01 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "types.h"

t_vec2		vec_rotate(t_vec2 dir, t_float angle)
{
	t_float old_x;

	old_x = dir.x;
	dir.x = dir.x * cos(-angle) - dir.y * sin(-angle);
	dir.y = old_x * sin(-angle) + dir.y * cos(-angle);
	return (dir);
}

t_float		vec_dot(t_vec2 v1, t_vec2 v2)
{
	t_vec2	r;

	r = v1 * v2;
	return (r[0] + r[1]);
}

t_float		vec_len(t_vec2 v1)
{
	return (sqrt(vec_dot(v1, v1)));
}

t_vec2		vec_norm(t_vec2 v1)
{
	t_float	len;

	len = vec_len(v1);
	if (len > 0.0)
	{
		len = 1.0 / len;
		v1 *= len;
	}
	return (v1);
}
