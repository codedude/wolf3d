/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_f1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:59:58 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 23:39:55 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void			draw_ds_prev(t_env *env, t_door_edit *dedit, t_entity *ent)
{
	t_color_pick	*cpick;
	t_sdl			*sdl;
	int				id;

	cpick = &env->cpick;
	sdl = &env->sdl;
	id = ent->tex_id;
	draw_tex(sdl, cpick, &env->sdl.tex_walls[id], dedit->prev[Door_Tex]);
	id = ent->e.door->tex_wall_id;
	draw_tex(sdl, cpick, &env->sdl.tex_walls[id], dedit->prev[Side_Tex]);
	id = ent->e.door->item_id;
	if (id != -1)
		draw_tex(sdl, cpick, &env->sdl.tex_sprites[env->obj.list[id]->id],
			dedit->prev[Item_Prev]);
}

static void			draw_door_centerl(t_env *env, t_canvas anch, int dim,
					void (*drawline_ptr)(t_sdl *, t_color_pick *, t_ivec2, int))
{
	t_ivec2		pos;
	int			to;
	int			p2;
	int			other_dim;

	other_dim = dim == 1 ? 0 : 1;
	to = ipercent_of(anch.size[dim], 5);
	pos[dim] = anch.pos[dim] + (anch.size[dim] - to) / 2;
	pos[other_dim] = anch.pos[other_dim];
	p2 = anch.pos[other_dim] + anch.size[other_dim];
	to = pos[dim] + to;
	while (pos[dim] < to)
	{
		drawline_ptr(&env->sdl, &env->cpick, pos, p2);
		pos[dim]++;
	}
}

static void			draw_door_prev(t_env *env, t_door_edit *dedit,
						t_entity *ent)
{
	t_canvas	anch;

	anch = dedit->prev[Door_Prev];
	if (door_check_neighbour(env->map_info.map, ent))
		cpick_set_color(&env->cpick, 0xFFFFFF);
	else
		cpick_set_color(&env->cpick, 0xFF0000);
	if (ent->e.door->orientation == Dir_Horizontal)
		draw_door_centerl(env, anch, 1, draw_hline);
	else
		draw_door_centerl(env, anch, 0, draw_vline);
}

void				inspector_draw_door(t_env *env)
{
	t_door_edit		*dedit;
	t_entity		*ent;
	t_canvas		anch;
	int				i;

	dedit = &env->inspector.door_edit;
	ent = dedit->selected;
	if (ent == NULL)
		return ;
	draw_ds_prev(env, dedit, ent);
	draw_door_prev(env, dedit, ent);
	if (dedit->mode == Object_Select)
	{
		anch = dedit->prev[Item_Prev];
		i = ipercent_of(anch.size.x, 5);
		while (i--)
		{
			draw_canvas_border(&env->sdl, anch, CANVAS_INIT(0, 0), 0xFFFFFF);
			anch.pos += 1;
			anch.size -= 2;
		}
	}
}
