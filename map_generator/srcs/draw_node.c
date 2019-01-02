/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/29 05:58:04 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"
#include "types.h"

static void		env_update_map_value(t_env *env, t_ivec2 mapi)
{
	int			value;

	if (env->mouse.is_editing == False
	|| (value = env->map_info.map_mask->data[mapi.y][mapi.x]) == 0)
		value = env->map_info.map->data[mapi.y][mapi.x];
	env->erasing = (value == -1);
	if (env->erasing)
		value = env->map_info.map->data[mapi.y][mapi.x];
	env->ed_map_value = value;
}

static t_u32	compute_color(t_bool erasing, t_texture *text, t_ivec2 px)
{
	t_color		c;

	c = sdl_get_pixel(text, px.x, px.y);
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
	t_texture	*text;
	t_ivec2		i;
	t_ivec2		px;

	text = sdl->textures + (env->ed_map_value - 1);
	i.y = 0;
	while (i.y < canvas.size.y)
	{
		px.y = (int)((t_float)text->h
			* ((t_float)i.y / (t_float)canvas.size.y));
		i.x = 0;
		while (i.x < canvas.size.x)
		{
			px.x = (int)((t_float)text->w
				* ((t_float)i.x / (t_float)canvas.size.x));
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
		draw_canvas_fill(sdl, canvas, env->grid, 0x30a530);
	else if (env->ed_map_value == 0)
		draw_canvas_fill(sdl, canvas, env->grid,
				env->erasing ? 0x1010a2 : 0x853030);
	else
		draw_canvas_tex(sdl, env, canvas);
}

void			draw_node(t_env *env, t_sdl *sdl, t_map_info *minf, t_ivec2 i)
{
	t_canvas		canvas;

	canvas.pos = IVEC2_INIT(minf->x_draw[i.x], minf->y_draw[i.y]);
	canvas.size = IVEC2_INIT(minf->x_draw[i.x + 1],
						minf->y_draw[i.y + 1]) - canvas.pos;
	draw_node_tex(sdl, env, canvas, i);
	draw_canvas_border(sdl, canvas, env->grid, 0);
}
