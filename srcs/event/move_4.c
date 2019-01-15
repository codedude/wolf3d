/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 14:50:06 by vparis            #+#    #+#             */
/*   Updated: 2019/01/15 14:54:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"

int			is_inside(t_float x, t_float min, t_float max)
{
	return (x >= min && x < max);
}

int			is_close_objects(t_env *env, t_vec2 pos)
{
	t_float		t;
	int			i;

	i = 0;
	while (i < env->objects_nb)
	{
		if (env->objects[i].crossable == 0)
		{
			t = vec_len(env->objects[i].e.object->pos - pos);
			if (t < 0.3)
				return (True);
		}
		i++;
	}
	return (False);
}
