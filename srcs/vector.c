/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:41:23 by vparis            #+#    #+#             */
/*   Updated: 2018/12/04 18:11:30 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "types.h"

t_vec2		vec_rotate(t_vec2 dir, t_float speed)
{
	t_float old_x;

	old_x = dir.x;
	dir.x = dir.x * cos(-speed) - dir.y * sin(-speed);
	dir.y = old_x * sin(-speed) + dir.y * cos(-speed);
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

t_float		vec_ang(t_vec2 v1, t_vec2 v2)
{
	return (vec_dot(v1, v2) / (vec_len(v1) * vec_len(v2)));
}

t_vec2		vec_cross(t_vec2 v1, t_vec2 v2)
{
	return (VEC2_INIT(v1.x * v2.y - v1.y * v2.x,
					v2.x * v1.y - v2.y * v1.x));
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