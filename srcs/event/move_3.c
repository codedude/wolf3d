/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:51:38 by vparis            #+#    #+#             */
/*   Updated: 2019/01/14 16:42:56 by vparis           ###   ########.fr       */
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

t_vec2		allow_move(t_env *env, t_vec2 from, t_vec2 to, t_vec2 calc)
{
	t_vec2		offset;
	t_map		*map;
	t_entity	*entity;

	map = &env->map;
	offset.x = ((to.x < 0) ? -0.1 : 0.1);
	offset.y = ((to.y < 0) ? -0.1 : 0.1);
	calc = clamp_vec2(calc, VEC2_ZERO + 0.1, \
		VEC2_INIT((t_float)map->width - 0.2, (t_float)map->height - 0.2));
	entity = &map->data[(int)from.y][(int)(calc.x + offset.x)];
	if ((entity->type != ENTITY_VOID && (entity->type != ENTITY_DOOR
		|| !entity->e.door->is_open || entity->e.door->open_offset != 0.0))
	|| is_close_objects(env, VEC2_INIT(calc.x + offset.x, from.y)))
		calc.x = from.x;
	entity = &map->data[(int)(calc.y + offset.y)][(int)from.x];
	if ((entity->type != ENTITY_VOID && (entity->type != ENTITY_DOOR
		|| !entity->e.door->is_open || entity->e.door->open_offset != 0.0))
		|| is_close_objects(env, VEC2_INIT(from.x, calc.y + offset.y)))
		calc.y = from.y;
	entity = &map->data[(int)(calc.y + offset.y)][(int)(calc.x + offset.x)];
	if ((entity->type != ENTITY_VOID && (entity->type != ENTITY_DOOR
		|| !entity->e.door->is_open || entity->e.door->open_offset != 0.0))
		|| is_close_objects(env,
			VEC2_INIT(calc.x + offset.x, calc.y + offset.y)))
		calc = from;
	return (calc);
}

t_vec2		move_forward(t_env *env, t_vec2 from, t_vec2 to, t_float speed)
{
	t_vec2	ret;

	if (speed < 0)
	{
		to = VEC2_INIT(-to.x, -to.y);
		speed = -speed;
	}
	ret = from + to * speed;
	return (allow_move(env, from, to, ret));
}

t_vec2		straf(t_env *env, t_vec2 from, t_vec2 to, t_float speed)
{
	to = VEC2_INIT(to.y, -to.x);
	return (move_forward(env, from, to, speed));
}