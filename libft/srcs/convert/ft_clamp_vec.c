/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp_vec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 17:04:27 by vparis            #+#    #+#             */
/*   Updated: 2018/11/20 17:07:04 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"

t_float		clamp_float(t_float n, t_float min, t_float max)
{
	if (n < min)
		return (min);
	else if (n > max)
		return (max);
	return (n);
}

t_vec2		clamp_vec2(t_vec2 v, t_vec2 min, t_vec2 max)
{
	return (VEC2_INIT(
		clamp_float(v.x, min.x, max.x),
		clamp_float(v.y, min.y, max.y)
	));
}
