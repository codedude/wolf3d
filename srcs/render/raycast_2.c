/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2019/02/04 14:57:52 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "raycast.h"
#include "types.h"

static t_vec2	get_wall_texel(t_hit_infos *infos)
{
	t_vec2		texel;

	if (infos->side == 0)
	{
		if (infos->ray.dir.x > 0 || infos->is_thin == 1)
			texel = VEC2_INIT(infos->map.x, infos->map.y + infos->wall_x);
		else
			texel = VEC2_INIT(infos->map.x + 1.0f, infos->map.y
				+ infos->wall_x);
	}
	else
	{
		if (infos->ray.dir.y > 0 || infos->is_thin == 1)
			texel = VEC2_INIT(infos->map.x + infos->wall_x, infos->map.y);
		else
			texel = VEC2_INIT(infos->map.x + infos->wall_x,
				infos->map.y + 1.0f);
	}
	return (texel);
}

static t_bool	is_door_sides(t_env *env, t_hit_infos *infos, t_entity *ent)
{
	t_ivec2		dpos;
	int			ref;

	if (infos->e_door != NULL && infos->is_thin == 0)
	{
		dpos.x = infos->e_door->id % env->map.width;
		dpos.y = infos->e_door->id / env->map.width;
		if (infos->side == 0)
		{
			ref = infos->e_door->id;
			if (infos->e_door->e.door->orientation == DOOR_EW)
				if (ref + 1 == ent->id || ref - 1 == ent->id)
					return (True);
		}
		else
		{
			ref = infos->e_door->id;
			if (infos->e_door->e.door->orientation == DOOR_NS)
				if (ref + env->map.width == ent->id
					|| ref - env->map.width == ent->id)
					return (True);
		}
	}
	return (False);
}

void			set_wall_tex(t_env *env, t_hit_infos *infos)
{
	t_entity	*ent;

	ent = &env->map.data[(int)infos->map.y][(int)infos->map.x];
	if (is_door_sides(env, infos, ent) == True)
	{
		infos->tex_key = 0;
		infos->tex = tex_get_wall(&env->sdl,
			infos->e_door->e.door->tex_wall_id - 1);
	}
	else
	{
		infos->tex_key = ent->tex_key;
		infos->tex = tex_get_wall(&env->sdl, ent->tex_id - 1);
	}
}

void			rc_render(t_env *env, t_hit_infos *infos)
{
	t_vec2		texel;

	if (infos->hit == 1)
	{
		set_wall_tex(env, infos);
		draw_wall(&env->sdl, infos, &env->cam);
	}
	texel = get_wall_texel(infos);
	draw_floor(env, &env->sdl, infos, texel);
	if (env->map.show_ceil == 1)
		draw_ceil(env, &env->sdl, infos, texel);
	if (env->map.show_ceil == 1 && infos->hit == 0)
		draw_skybox(&env->sdl, infos, &env->cam, &env->map);
	else if (env->map.show_ceil == 0)
	{
		if (infos->hit == 1)
			infos->draw_end = infos->draw_start;
		infos->draw_start = 0;
		draw_skybox(&env->sdl, infos, &env->cam, &env->map);
	}
}
