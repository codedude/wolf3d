/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:51:38 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 14:52:53 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "env.h"
#include "event.h"
#include "entity.h"

static int		player_collect(t_env *env, t_entity *ent)
{
	t_klist		*list;

	if ((list = klist_new(ent)) == NULL)
		return (ERROR);
	klist_append(&env->player.inventory, list);
	ent->e.object->collectable = -1;
	sound_play(&env->audio, SOUND_PICKUP);
	return (SUCCESS);
}

static int		is_close_objects(t_env *env, t_vec2 pos)
{
	t_float		t;
	int			i;

	i = 0;
	while (i < env->objects_nb)
	{
		t = vec_len(env->objects[i].e.object->pos - pos);
		if (env->objects[i].e.object->collectable == 1)
		{
			if (t < 0.5)
				player_collect(env, &env->objects[i]);
		}
		else if (env->objects[i].e.object->collectable == 0
			&& env->objects[i].crossable == 0)
		{
			if (t < 0.5f)
				return (True);
		}
		i++;
	}
	return (False);
}

static t_bool	intersect_smth(t_env *env, t_vec2 pos, t_entity *entity)
{
	if ((entity->type != ENTITY_VOID && (entity->type != ENTITY_DOOR
		|| !entity->e.door->is_open || entity->e.door->open_offset != 0.0f))
		|| is_close_objects(env, pos))
		return (False);
	return (True);
}

static t_vec2	allow_move(t_env *env, t_vec2 from, t_vec2 to, t_vec2 calc)
{
	t_vec2		offset;
	t_map		*map;

	map = &env->map;
	offset.x = ((to.x < 0) ? -0.1f : 0.1f);
	offset.y = ((to.y < 0) ? -0.1f : 0.1f);
	calc = clamp_vec2(calc, VEC2_ZERO + 0.1f,
		VEC2_INIT((t_float)map->width - 0.2f, (t_float)map->height - 0.2f));
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
