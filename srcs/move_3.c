/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:51:38 by vparis            #+#    #+#             */
/*   Updated: 2018/12/04 11:52:41 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "raycast.h"

t_vec2		allow_move(t_map *map, t_vec2 from, t_vec2 to, t_vec2 calc)
{
	t_vec2	offset;

	calc = clamp_vec2(calc, VEC2_ZERO, \
				VEC2_INIT((t_float)map->width - 0.1,
					(t_float)map->height - 0.1));
	offset.x = ((to.x < 0) ? -0.1 : 0.1);
	offset.y = ((to.y < 0) ? -0.1 : 0.1);
	if (map->data[(int)from.x][(int)(calc.y + offset.y)] != 0)
		calc.y = from.y;
	if (map->data[(int)(calc.x + offset.x)][(int)from.y] != 0)
		calc.x = from.x;
	if (map->data[(int)(calc.x + offset.x)][(int)(calc.y + offset.y)] != 0)
		calc = from;
	return (calc);
}

t_vec2		move_forward(t_map *map, t_vec2 from, t_vec2 to, t_float speed)
{
	t_vec2	ret;

	if (speed < 0)
	{
		to = VEC2_INIT(-to.x, -to.y);
		speed = -speed;
	}
	ret = from + to * speed;
	return (allow_move(map, from, to, ret));
}

t_vec2		straf(t_map *map, t_vec2 from, t_vec2 to, t_float speed)
{
	to = VEC2_INIT(to.y, -to.x);
	return (move_forward(map, from, to, speed));
}

t_float		player_speed(int action_state, t_float speed,
					t_float acceleration, t_float factor)
{
	if (action_state & ACTION_CROUCHING)
		factor *= 0.6;
	return ((speed + acceleration) * factor);
}
