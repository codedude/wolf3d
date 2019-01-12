/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/11 05:42:39 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

t_vec2			vec_rotate(t_vec2 dir, t_float radian)
{
	t_float old_x;

	old_x = dir.x;
	dir.x = dir.x * cos(-radian) - dir.y * sin(-radian);
	dir.y = old_x * sin(-radian) + dir.y * cos(-radian);
	return (dir);
}

t_color			sdl_pixel_pick_from_img(t_sdl *sdl, int x, int y)
{
	unsigned char	*img;
	int				pos;
	t_color			c;

	img = sdl->image;
	pos = x * sdl->bpp + y * sdl->pitch;
	c.c.b = img[pos];
	c.c.g = img[pos + 1];
	c.c.r = img[pos + 2];
	c.c.a = 0;
	return (c);
}

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

t_vec2		map_to_center(t_env *env)
{
	t_vec2		center;

	center.x = (t_float)env->grid.pos.x + ((t_float)env->grid.size.x / 2.0);
	center.y = (t_float)env->grid.pos.y + ((t_float)env->grid.size.y / 2.0);
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

// t_canvas	get_map_boundaries(t_env *env)
// {
// 	t_canvas	bounds;
// 	t_vec2		offset;
//
// 	offset.x = -(((env->map->size.x) / 2.0)
// 						* env->node_size * env->zoom);
// 	offset.y = -((((env->map->size.y) / 2.0))
// 						* env->node_size * env->zoom);
// 	bounds.pos.x = (int)round(env->map_pos.x + offset.x);
// 	bounds.pos.y = (int)round(env->map_pos.y + offset.y);
// 	bounds.size.x = (int)round((t_float)env->map->size.x
// 					* (t_float)env->node_size * env->zoom);
// 	bounds.size.y = (int)round((t_float)env->map->size.y
// 					* (t_float)env->node_size * env->zoom);
// 	return (bounds);
// }

t_vec2 get_intersect_line(t_vec2 l1from, t_vec2 l1to,
							t_vec2 l2from, t_vec2 l2to)
{
	t_vec2		i;
	t_vec2		j;
	t_float		m;
	t_float		k;
	t_float		div;

	i = l1to - l1from;
	j = l2to - l2from;
	m = 0;
	k = 0;
	div = i.x * j.y - i.y * j.x;
    if(div != 0.0)
    {
        m = (i.x * l1from.y - i.x * l2from.y
			- i.y * l1from.x + i.y * l2from.x) / div;
        k = (j.x * l1from.y - j.x * l2from.y
            - j.y * l1from.x + j.y * l2from.x) / div;
    }
	return (l2from + m * j);
    //return (l1from + k * i);
}

t_canvas	get_map_boundaries(t_env *env)
{
	t_canvas	bounds;
	t_vec2		pos;

	pos = (env->map_info.pos - env->map_info.map_center) * env->map_info.zoom
		+ env->map_info.grid_center;
	bounds.pos = IVEC2_INIT((int)pos.x, (int)pos.y) + env->grid.pos;
	bounds.size.x = (int)(env->map_info.map->size.x * env->map_info.zoom);
	bounds.size.y = (int)(env->map_info.map->size.y * env->map_info.zoom);
	return (bounds);
}

// t_vec2		mpos_to_map_coord(t_canvas bounds, t_ivec2 mpos, t_env *env)
// {
// 	t_vec2		v2;
//
// 	mpos -= bounds.pos;
// 	v2.x = ((t_float)mpos.x / ((t_float)env->node_size * env->zoom));
// 	v2.y = ((t_float)mpos.y / ((t_float)env->node_size * env->zoom));
// 	return (v2);
// }

t_vec2		mpos_to_map_coord(t_canvas bounds, t_ivec2 mpos, t_env *env)
{
	t_vec2		v2;

	mpos -= bounds.pos;
	v2 = VEC2_INIT((t_float)mpos.x, (t_float)mpos.y) / env->map_info.zoom;
	return (v2);
}

t_ivec2		mpos_to_map_index(t_canvas bounds, t_ivec2 mpos, t_env *env)
{
	t_vec2		v2;

	v2 = mpos_to_map_coord(bounds, mpos, env);
	return (IVEC2_INIT((int)v2.x, (int)v2.y));
}
