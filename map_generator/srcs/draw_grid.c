/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/05 17:43:14 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static unsigned int	get_brush_px(t_tex_pbox *box, t_ivec2 i, t_float size_x,
							int brush)
{
	t_color		color;

	color = box->tex_data[(int)(i.x + i.y * size_x)];
	if (brush != box->tex_id)
		color.rgba = (color.rgba >> 2) & 0x3f3f3f;
	return (color.rgba);
}

static void			draw_brushes(t_tex_pbox *box, t_canvas parent, t_sdl *sdl,
							t_env *env)
{
	t_ivec2		i;
	t_canvas	current;

	if (!box)
		return ;
	draw_brushes(box->next, parent, sdl, env);
	current = box->canvas;
	current.pos.y -= env->brush_c_offset;
	if (current.pos.y >= parent.pos.y + parent.size.y
	|| current.pos.y + current.size.y < parent.pos.y)
		return ;
	i.y = 0;
	while (i.y < current.size.y)
	{
		i.x = 0;
		while (i.x < current.size.x)
		{
			put_pixel_inside_canvas(sdl, parent, current.pos + i,
						get_brush_px(box, i, current.size.x, (int)env->brush));
			i.x++;
		}
		i.y++;
	}
}

static void			draw_brush_texture(t_env *env, t_sdl *sdl)
{
	t_ivec2		px;
	t_canvas	canvas;
	t_ivec2		i;
	t_texture	*text;

	text = sdl->textures + env->brush;
	canvas = env->brush_prev;
	canvas.size -= 1;
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
			put_pixel_inside_canvas(sdl, CANVAS_INIT(0, 0), canvas.pos + i + 1,
									sdl_get_pixel(text, px.x, px.y).rgba);
			i.x++;
		}
		i.y++;
	}
}

static void			draw_brush_preview(t_env *env, t_sdl *sdl)
{
	draw_canvas_border(sdl, env->grid, CANVAS_INIT(0, 0), 0x777777);
	if (env->brush == env->spawner_id)
		draw_canvas_fill(sdl, env->brush_prev, CANVAS_INIT(0, 0),
						0x303080);
	else
		draw_brush_texture(env, sdl);
}

void				draw_grid(t_env *env, t_sdl *sdl)
{
	t_ivec2		g_pos;

	sdl_clear_color(sdl, 0x101010);
	g_pos = IVEC2_INIT(ipercent_of(sdl->width, GRID_OFF_X),
					ipercent_of(sdl->height, GRID_OFF_Y));
	draw_canvas_fill(sdl, env->grid, CANVAS_INIT(0, 0), 0x252525);
	draw_grid_lines(env, sdl);
	draw_brush_preview(env, sdl);
	draw_canvas_border(sdl, env->brush_prev, CANVAS_INIT(0, 0), 0x777777);
	draw_canvas_fill(sdl, env->brush_canvas, CANVAS_INIT(0, 0), 0x252525);
	draw_canvas_border(sdl, env->brush_canvas, CANVAS_INIT(0, 0), 0x777777);
	draw_brushes(env->brush_box, env->brush_canvas, sdl, env);
}
