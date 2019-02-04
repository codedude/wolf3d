/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 13:02:07 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 14:30:16 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "types.h"

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
		clamp_float(v.y, min.y, max.y)));
}

t_ivec2		clamp_ivec2(t_ivec2 v, t_ivec2 min, t_ivec2 max)
{
	return (IVEC2_INIT(
		clamp_int(v.x, min.x, max.x),
		clamp_int(v.y, min.y, max.y)));
}

char		*concat_path_file(char *path, char *filename)
{
	return (ft_strjoin(path, filename));
}
