/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/20 17:12:19 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

void			sdl_put_pixel_safe(t_sdl *sdl, t_ivec2 px, t_color c)
{
	if (px.x >= 0 && px.x < sdl->width
		&& px.y >= 0 && px.y < sdl->height)
		sdl_put_pixel(sdl, px.x, px.y, c);
}

int				sdl_clear_color(t_sdl *sdl, unsigned int color)
{
	t_ivec2		i;
	t_color		col;

	col.rgba = color;
	i.y = 0;
	while (i.y < sdl->height)
	{
		i.x = 0;
		while (i.x < sdl->width)
		{
			sdl_put_pixel(sdl, i.x, i.y, col);
			i.x++;
		}
		i.y++;
	}
	return (SUCCESS);
}

t_ivec2		map_to_center(t_env *env)
{
	t_ivec2		offset;
	t_ivec2		center;

	center = env->grid.pos + (env->grid.size / 2);
	// offset.x = (int)(((t_float)env->map->size.x
	// 				* (t_float)env->node_size * env->zoom) / 2.0);
	// offset.y = (int)(((t_float)env->map->size.y
	// 				* (t_float)env->node_size * env->zoom) / 2.0);
	// center -= offset;
	return (center);
}

int		ipercent_of(int of, int percent)
{
	return (of * percent / 100);
}

void		put_pixel_to_image(t_sdl *sdl, t_ivec2 pos, unsigned int color)
{
	t_color		col;

	col.rgba = color;
	if (pos.x >= 0 && pos.x < sdl->width
	&& pos.y >= 0 && pos.y < sdl->height)
		sdl_put_pixel(sdl, pos.x, pos.y, col);
}

t_bool		is_bounded(t_ivec2 pos, t_canvas canvas)
{
	if (pos.x >= canvas.pos.x && pos.x < canvas.pos.x + canvas.size.x
	&& pos.y >= canvas.pos.y && pos.y < canvas.pos.y + canvas.size.y)
		return (True);
	return (False);
}

void		put_pixel_inside_canvas(t_sdl *sdl, t_canvas canvas, t_ivec2 pos,
								unsigned int color)
{
	canvas.pos += 1;
	if (canvas.size.x > 1)
		canvas.size -= 2;
	if (canvas.size.x == 0 || is_bounded(pos, canvas))
		sdl_put_pixel_safe(sdl, pos, (t_color)color);
}

void		draw_canvas_border(t_sdl *sdl, t_canvas canvas, t_canvas parent,
							unsigned int color)
{
	t_ivec2		pos;
	t_ivec2		end;

	pos = canvas.pos;
	end = pos + canvas.size;
	while (pos.x < end.x)
	{
		put_pixel_inside_canvas(sdl, parent, pos, color);
		put_pixel_inside_canvas(sdl, parent, IVEC2_INIT(pos.x, end.y), color);
		pos.x++;
	}
	pos = canvas.pos;
	while (pos.y < end.y)
	{
		put_pixel_inside_canvas(sdl, parent, pos, color);
		put_pixel_inside_canvas(sdl, parent, IVEC2_INIT(end.x, pos.y), color);
		pos.y++;
	}
}


void		draw_canvas_fill(t_sdl *sdl, t_canvas canvas, t_canvas parent,
							unsigned int color)
{
	t_ivec2		pos;
	t_ivec2		end;

	pos.x = canvas.pos.x;
	end = pos + (canvas.size);
	while (pos.x < end.x)
	{
		pos.y = canvas.pos.y;
		while (pos.y < end.y)
		{
			put_pixel_inside_canvas(sdl, parent, pos, color);
			pos.y++;
		}
		pos.x++;
	}
}

t_canvas	get_map_boundaries(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		offset;

	offset.x = (int)-(floor(((t_float)env->map->size.x) / 2)
						* env->node_size * env->zoom);
	offset.y = (int)-((floor(((t_float)env->map->size.y) / 2) + 0.5)
						* env->node_size * env->zoom);
	bounds.pos = env->map_pos + offset;
	bounds.size = env->map->size * env->node_size;
	bounds.size.x = (int)(bounds.size.x * env->zoom);
	bounds.size.y = (int)(bounds.size.y * env->zoom);
	return (bounds);
}

t_ivec2		mpos_to_map_index(t_canvas bounds, t_ivec2 mpos, t_env *env)
{
	draw_canvas_fill(&env->sdl, bounds, CANVAS_INIT(0, 0), 0x220060);
	mpos -= bounds.pos;
	mpos.x = (int)(mpos.x / (env->node_size * env->zoom));
	mpos.y = (int)(mpos.y / (env->node_size * env->zoom));
	return (mpos);
}

t_ivec2		get_mouse_pos(void)
{
	int			x;
	int			y;

	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	return (IVEC2_INIT(x, y));
}
