/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:57:15 by vparis            #+#    #+#             */
/*   Updated: 2019/01/08 22:58:36 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"
#include "types.h"

t_color				dark_color(t_color color, t_cam *cam, int side, t_float z)
{
	t_vec3		c;

	c = VEC3_INIT((t_float)color.c.r, (t_float)color.c.g, (t_float)color.c.b);
	if (side)
		c *= 0.66;
	if (cam->depth_filter)
		c = cam->depth_filter(c, z);
	if (cam->color_filter)
		c = cam->color_filter(c);
	color.rgba = (unsigned int)c[0] | (unsigned int)c[1] << 8
		| (unsigned int)c[2] << 16;
	return (color);
}

static t_color		get_cf_color(t_tex *text, t_vec2 curr_cf, t_cam *cam,
					t_float z)
{
	t_ivec2			tex;
	t_color			color;

	tex.x = (int)fabs(curr_cf.x * text->w) % text->w;
	tex.y = (int)fabs(curr_cf.y * text->h) % text->h;
	color = dark_color(sdl_get_pixel(text, tex.x, tex.y), cam, 0, z);
	return (color);
}

/*
** Enelver le check le check cam->z
*/

void				draw_floor(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
					t_vec2 texel)
{
	t_vec2		curr_cf;
	t_float		lookup;
	t_float		z_by_half_canvas;
	t_float		weight;
	int			y;

	z_by_half_canvas = sdl->canvas_h * cam->z / sdl->half_canvas_h;
	y = infos->draw_end;
	while (y < sdl->height)
	{
		if (cam->z > 0.0)
		{
			lookup = z_by_half_canvas
				/ (2.0 * ((y + 1) - cam->height) - sdl->canvas_h);
			weight = lookup / infos->z;
			curr_cf.x = weight * texel.x + (1.0 - weight) * infos->ray.pos.x;
			curr_cf.y = weight * texel.y + (1.0 - weight) * infos->ray.pos.y;
			sdl_put_pixel(sdl, infos->x, y, get_cf_color(
				tex_get_wall(sdl, DEFAULT_FLOOR), curr_cf, cam, lookup));
		}
		else
			sdl->image[infos->x + y * sdl->width] = 0;
		y++;
	}
}

void				draw_ceil(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
					t_vec2 texel)
{
	t_vec2		curr_cf;
	t_float		weight;
	t_float		lookup;
	t_float		z_by_half_canvas;
	int			y;

	z_by_half_canvas = sdl->canvas_h * (sdl->canvas_h - cam->z)
		/ sdl->half_canvas_h;
	y = 0;
	while (y < infos->draw_start)
	{
		if (cam->z < sdl->canvas_h)
		{
			lookup = z_by_half_canvas
				/ fabs(2.0 * (y - cam->height) - sdl->canvas_h);
			weight = lookup / infos->z;
			curr_cf.x = weight * texel.x + (1.0 - weight) * infos->ray.pos.x;
			curr_cf.y = weight * texel.y + (1.0 - weight) * infos->ray.pos.y;
			sdl_put_pixel(sdl, infos->x, y, get_cf_color(
				tex_get_wall(sdl, DEFAULT_CEIL), curr_cf, cam, lookup));
		}
		else
			sdl->image[infos->x + y * sdl->width] = 0x0;
		y++;
	}
}

void				draw_wall(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
					t_tex *text)
{
	t_ivec2			tex;
	int				y;
	t_color			color;
	t_float			half_height;

	// if (infos->tex_off_x > infos->wall_x)
	// 	infos->tex_off_x = infos->wall_x;
	tex.x = (int)fmod((fabs(infos->wall_x - infos->tex_off_x) * text->w), text->w);
	if (infos->side == 0 && infos->ray.dir.x > 0)
		tex.x = text->w - tex.x - 1;
	else if (infos->side == 1 && infos->ray.dir.y < 0)
		tex.x = text->w - tex.x - 1;
	half_height = -sdl->half_canvas_h + infos->line_height / 2.0
		+ ((sdl->half_canvas_h - cam->z) / infos->z);
	y = infos->draw_start;
	while (y < infos->draw_end)
	{
		tex.y = (int)fabs(text->h * ((y - cam->height + half_height)
			/ (t_float)(infos->line_height)));
		color = dark_color(sdl_get_pixel(text, tex.x, tex.y),
			cam, infos->side & cam->side_filter, infos->z);
		sdl_put_pixel(sdl, infos->x, y, color);
		y++;
	}
}
