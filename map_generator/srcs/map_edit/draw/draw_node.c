/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/28 15:12:42 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "map_edit.h"
#include "gen_env.h"
#include "types.h"

static void		env_update_map_value(t_env *env, t_ivec2 mapi)
{
	t_map_info	*m_inf;
	t_entity	*ent;
	int			value;
	int			tmp_value;

	m_inf = &env->map_info;
	ent = &m_inf->map->data[mapi.y][mapi.x];
	tmp_value = m_inf->tmp_data[mapi.y][mapi.x];
	value = ent->type == ENTITY_VOID ? 0 : ent->tex_id + 1;
	if (env->mouse.is_editing == False || tmp_value == 0)
		tmp_value = value;
	env->erasing = (tmp_value == -1);
	if (!env->erasing)
		value = tmp_value;
	env->ed_map_value = value;
}

static void		draw_node_tex(t_sdl *sdl, t_env *env, t_canvas canvas,
							t_ivec2 mapi)
{
	env_update_map_value(env, mapi);
	if (env->erasing)
		cpick_set_color_mask(&env->cpick, 0xFF0000, 0.70f);
	if (env->spawn.x == mapi.x && env->spawn.y == mapi.y)
		draw_canvas_fill(sdl, &canvas, &env->grid, 0x30a530);
	else if (env->ed_map_value == 0)
		draw_canvas_fill(sdl, &canvas, &env->grid,
				env->erasing ? 0xa21010 : 0x303085);
	else
		draw_tex(sdl, &env->cpick,
			&sdl->tex_walls[env->ed_map_value - 1], canvas);
	cpick_unset_color_mask(&env->cpick);
}


static void		draw_node_door(t_env *env, t_sdl *sdl, t_entity *ent,
					t_canvas *rec_anch)
{
	int				rsize;
	t_u32			c;

	if (env->editor.mode == Door && ent == env->inspector.door_edit.selected)
		c = 0xffffff;
	else if (door_check_neighbour(env->map_info.map, ent) == False)
		c = 0xff0000;
	else
		c = 0xffff00;
	rsize = (int)(rec_anch->size.x * 0.15f);
	while (rsize--)
	{
		rec_anch->size -= 2;
		rec_anch->pos += 1;
		draw_canvas_border(sdl, *rec_anch, env->grid, c);
	}
	draw_canvas_border(sdl, *rec_anch, env->grid, 0x00);
}

void			draw_node(t_env *env, t_sdl *sdl, t_map_info *minf, t_ivec2 i)
{
	t_canvas		tex_anch;
	t_canvas		rec_anch;
	t_entity		*ent;

	rec_anch.pos = IVEC2_INIT(minf->x_draw[i.x], minf->y_draw[i.y]);
	rec_anch.size = IVEC2_INIT(minf->x_draw[i.x + 1],
						minf->y_draw[i.y + 1]) - rec_anch.pos;
	tex_anch.pos = rec_anch.pos + 1;
	tex_anch.size = rec_anch.size - 1;
	ent = &minf->map->data[i.y][i.x];
	draw_canvas_border(sdl, rec_anch, env->grid, 0);
	if (ent->type == ENTITY_DOOR)
	{
		draw_node_door(env, sdl, ent, &rec_anch);
		draw_node_tex(sdl, env, rec_anch, i);
	}
	else
		draw_node_tex(sdl, env, tex_anch, i);
}
