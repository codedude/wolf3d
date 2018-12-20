/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/20 16:47:06 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"
#include "types.h"

static void		draw_canvas_tex(t_sdl *sdl, t_env *env,
							t_canvas canvas, t_ivec2 mapi)
{
	t_texture	*text;
	t_ivec2		i;
	t_ivec2		px;

	text = sdl->textures + (env->map->data[mapi.y][mapi.x] - 1);
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
							sdl_get_pixel(text, px.x, px.y).rgba);
			i.x++;
		}
		i.y++;
	}
}

static void		draw_node_tex(t_sdl *sdl, t_env *env, t_canvas canvas,
							t_ivec2 mapi)
{
	if (env->spawn.x == mapi.x && env->spawn.y == mapi.y)
		draw_canvas_fill(sdl, canvas, env->grid, 0x303085);
	else if (env->map->data[mapi.y][mapi.x] == 0)
		draw_canvas_fill(sdl, canvas, env->grid, 0x853030);
	else
		draw_canvas_tex(sdl, env, canvas, mapi);
}

void			draw_node(t_env *env, t_sdl *sdl, t_ivec2 i)
{
	t_canvas		canvas;
	t_ivec2			node_size;
	t_ivec2			coef;

	canvas.pos.x = env->map_pos.x + (int)(env->map_topleft.x);
	canvas.pos.y = env->map_pos.y + (int)(env->map_topleft.y);
	canvas.size = (int)(env->ns_zoom);
	// node_size = (int)((t_float)env->node_size * env->zoom);
	// coef = (env->map->size / 2) * node_size;
	// canvas.pos = env->map_pos + (i * node_size) - coef;
	// canvas.size = node_size;
	draw_node_tex(sdl, env, canvas, i);
	draw_canvas_border(sdl, canvas, env->grid, 0);
}

t_bool			drawing_node(t_env *env, t_ivec2 mpos, t_ivec2 node)
{
	t_canvas	canvas;

	canvas.size = (int)((t_float)env->node_size * env->zoom);
	canvas.pos = env->map_pos + node * canvas.size;
	if (is_bounded(mpos, canvas))
		return (True);
	return (False);
}
