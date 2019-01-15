/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:51:38 by vparis            #+#    #+#             */
/*   Updated: 2019/01/15 19:27:50 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"

static t_bool	intersect_smth(t_env *env, t_vec2 pos, t_entity *entity)
{
	if ((entity->type != ENTITY_VOID && (entity->type != ENTITY_DOOR
		|| !entity->e.door->is_open || entity->e.door->open_offset != 0.0))
		|| is_close_objects(env, pos))
		return (False);
	return (True);
}

static t_vec2	allow_move(t_env *env, t_vec2 from, t_vec2 to, t_vec2 calc)
{
	t_vec2		offset;
	t_map		*map;

	map = &env->map;
	offset.x = ((to.x < 0) ? -0.1 : 0.1);
	offset.y = ((to.y < 0) ? -0.1 : 0.1);
	calc = clamp_vec2(calc, VEC2_ZERO + 0.1,
		VEC2_INIT((t_float)map->width - 0.2, (t_float)map->height - 0.2));
	if (intersect_smth(env, VEC2_INIT(calc.x + offset.x, from.y),
		&map->data[(int)from.y][(int)(calc.x + offset.x)]) == False)
		calc.x = from.x;
	if (intersect_smth(env, VEC2_INIT(from.x, calc.y + offset.y),
		&map->data[(int)(calc.y + offset.y)][(int)from.x]) == False)
		calc.y = from.y;
	if (intersect_smth(env, VEC2_INIT(calc.x + offset.x, calc.y + offset.y),
		&map->data[(int)(calc.y + offset.y)][(int)(calc.x + offset.x)])
		== False)
		calc = from;
	return (calc);
}

t_vec2			move_forward(t_env *env, t_vec2 from, t_vec2 to, t_float speed)
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

t_vec2			straf(t_env *env, t_vec2 from, t_vec2 to, t_float speed)
{
	to = VEC2_INIT(to.y, -to.x);
	return (move_forward(env, from, to, speed));
}
