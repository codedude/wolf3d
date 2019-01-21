/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/20 22:28:31 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
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

static t_u32	compute_color(t_bool erasing, t_tex *text, t_ivec2 px)
{
	t_color		c;
	t_color		raw_c;

	raw_c = sdl_get_pixel(text, px.x, px.y, 0);
	c.c.r = raw_c.c.b;
	c.c.g = raw_c.c.g;
	c.c.b = raw_c.c.r;
	c.c.a = raw_c.c.a;
	if (erasing)
	{
		c.c.r += 40;
		c.c.g = (t_u8)ipercent_of(c.c.g, 45);
		c.c.b = (t_u8)ipercent_of(c.c.b, 45);
	}
	return (c.rgba);
}

static void		draw_canvas_tex(t_sdl *sdl, t_env *env, t_canvas canvas)
{
	t_tex	*text;
	t_ivec2		i;
	t_ivec2		px;

	text = sdl->tex_walls + (env->ed_map_value - 1);
	i.y = 0;
	while (i.y < canvas.size.y)
	{
		px.y = (int)(text->h * (i.y / (t_float)canvas.size.y));
		i.x = 0;
		while (i.x < canvas.size.x)
		{
			px.x = (int)(text->w * (i.x / (t_float)canvas.size.x));
			put_pixel_inside_canvas(sdl, env->grid, canvas.pos + i,
							compute_color(env->erasing, text, px));
			i.x++;
		}
		i.y++;
	}
}

static void		draw_node_tex(t_sdl *sdl, t_env *env, t_canvas canvas,
							t_ivec2 mapi)
{
	env_update_map_value(env, mapi);
	if (env->spawn.x == mapi.x && env->spawn.y == mapi.y)
		draw_canvas_fill(sdl, &canvas, &env->grid, 0x30a530);
	else if (env->ed_map_value == 0)
		draw_canvas_fill(sdl, &canvas, &env->grid,
				env->erasing ? 0xa21010 : 0x303085);
	else
		draw_canvas_tex(sdl, env, canvas);
}

static int		get_side_wall(t_map *map, int x, int y)
{
	int			side;

	side = 0;
	if (x > 0 && x < (map->size.x - 1) && y > 0 && y < (map->size.y - 1))
	{
		if (map->data[y][x - 1].type == ENTITY_WALL)
			side |= 0b0001;
		if (map->data[y][x + 1].type == ENTITY_WALL)
			side |= 0b0010;
		if (map->data[y - 1][x].type == ENTITY_WALL)
			side |= 0b0100;
		if (map->data[y + 1][x].type == ENTITY_WALL)
			side |= 0b1000;
	}
	return (side);
}

t_bool			door_check_neighbour(t_map *map, t_entity *ent)
{
	int			side;
	int			x;
	int			y;

	x = ent->id % MAX_SIZE_X;
	y = ent->id / MAX_SIZE_X;
	side = get_side_wall(map, x, y);
	if ((side & 0b0011) == 0b0011)
	{
		if ((side & 0b1100) != 0b1100)
		{
			ent->e.door->orientation = Dir_Horizontal;
			return (True);
		}
	}
	else if ((side & 0b1100) == 0b1100)
	{
		ent->e.door->orientation = Dir_Vertical;
		return (True);
	}
	return (False);
}

void			draw_node_door(t_env *env, t_sdl *sdl, t_entity *ent,
					t_canvas rec_anch)
{
	int				rsize;
	t_u32			c;

	if (env->editor.mode == Door && ent == env->inspector.door_edit.selected)
		c = 0xffffff;
	else if (door_check_neighbour(env->map_info.map, ent) == False)
		c = 0xff0000;
	else
		c = 0xffff00;
	rsize = rec_anch.size.x / 5;
	while (rsize--)
	{
		rec_anch.size -= 2;
		rec_anch.pos += 1;
		draw_canvas_border(sdl, rec_anch, env->grid, c);
	}
	draw_canvas_border(sdl, rec_anch, env->grid, 0x00);
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
	draw_node_tex(sdl, env, tex_anch, i);
	ent = &minf->map->data[i.y][i.x];
	draw_canvas_border(sdl, rec_anch, env->grid, 0);
	if (ent->type == ENTITY_DOOR)
		draw_node_door(env, sdl, ent, rec_anch);
}
