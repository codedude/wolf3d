/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:18:37 by vparis            #+#    #+#             */
/*   Updated: 2019/01/18 15:18:26 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "types.h"
#include "sdl_m.h"
#include "raycast.h"
#include "list.h"

/*
** Sort asc
*/

static int		sort_object(t_entity *a, t_entity *b)
{
	if (a->e.object->z_buffer < b->e.object->z_buffer)
		return (-1);
	if (b->e.object->z_buffer < a->e.object->z_buffer)
		return (1);
	return (0);
}

static t_float	vec_is_in_front(t_vec2 left, t_vec2 right, t_vec2 p)
{
	t_float	s;
	t_float	t;

	s = (right.y * p.x + -right.x * p.y);
	t = (-left.y * p.x + left.x * p.y);
	return (s / (s + t));
}

int				prepare_sprite(t_env *env, t_klist **lst)
{
	t_vec2	dir[2];
	t_vec2	obj_dir;
	t_klist	*tmp;
	int		i;

	dir[0] = env->cam.dir - env->cam.plane;
	dir[1] = env->cam.dir + env->cam.plane;
	i = 0;
	while (i < env->objects_nb)
	{
		obj_dir = env->objects[i].e.object->pos - env->cam.pos;
		if (vec_is_in_front(-env->cam.plane, env->cam.plane, obj_dir) >= 0.0)
			if (prepare_object(env, i, obj_dir, vec_is_in_front(dir[0], dir[1],
				obj_dir)) == True)
			{
				if ((tmp = klist_new(env->objects + i)) == NULL)
				{
					klist_clear(lst);
					return (ERROR);
				}
				klist_add_sort(lst, tmp, sort_object);
			}
		i++;
	}
	return (SUCCESS);
}

void			compute_sprite(t_env *env)
{
	t_klist		*lst;
	t_klist		*iter;
	t_entity	*obj;

	lst = NULL;
	if (prepare_sprite(env, &lst) == ERROR)
		return ;
	iter = lst;
	while (iter != NULL)
	{
		obj = iter->value;
		draw_sprite(env, &env->sdl, obj);
		iter = iter->next;
	}
	klist_clear(&lst);
}
