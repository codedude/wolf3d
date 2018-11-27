/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/27 16:09:34 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"

t_color		dark_color(t_color c, t_float step)
{
	t_color		r;
	t_color		g;
	t_color		b;

	if (step < 0.0)
		return (c);
	r = c & 0xff;
	g = (c & (0xff << 8)) >> 8;
	b = (c & (0xff << 16)) >> 16;
	r *= step;
	g *= step;
	b *= step;
	return ((t_color)(r | (g << 8) | (b << 16)));
}

static void		draw_tex_line(t_sdl *sdl, t_hit_infos *infos,
					SDL_Surface * text)
{
	t_ivec2				tex;
	int					y;
	t_color 			color;
	int					d;

	tex.x = (int)(infos->wall_x * (double)text->w);
	if(infos->side == 0 && infos->ray.dir.x > 0)
		tex.x = text->w - tex.x - 1;
	if(infos->side == 1 && infos->ray.dir.y < 0)
		tex.x = text->w - tex.x - 1;
	y = infos->draw_start;
	while (y < infos->draw_end)
	{
		d = y * 256 - sdl->height * 128 + infos->line_height * 128;  //256 and 128 factors to avoid floats
		// TODO: avoid the division to speed this up
		tex.y = ((d * text->w) / infos->line_height) / 256;
		color = sdl_get_pixel(text, tex.x, tex.y);
		color = dark_color(color, infos->depth_effect);
		sdl->image[infos->x + y * sdl->width] = color;
		y++;
	}
}

static void		render_wall(t_sdl *sdl, t_map *map, t_hit_infos *infos)
{
	SDL_Surface			*text;
	int					text_id;

	text_id = map->data[(int)infos->map.x][(int)infos->map.y] - 1;
	text = sdl_get_texture(text_id);
	draw_tex_line(sdl, infos, text);
	//x coordinate on the texture
}

static t_vec2	get_wall_texel(t_hit_infos *infos)
{
	t_vec2		texel;

	if(infos->side == 0 && infos->ray.dir.x > 0)
	{
		texel.x = infos->map.x;
		texel.y = infos->map.y + infos->wall_x;
	}
	else if(infos->side == 0 && infos->ray.dir.x < 0)
	{
		texel.x = infos->map.x + 1.0;
		texel.y = infos->map.y + infos->wall_x;
	}
	else if(infos->side == 1 && infos->ray.dir.y > 0)
	{
		texel.x = infos->map.x + infos->wall_x;
		texel.y = infos->map.y;
	}
	else
	{
		texel.x = infos->map.x + infos->wall_x;
		texel.y = infos->map.y + 1.0;
	}
	return (texel);
}

static t_color	get_cf_color(int text_id, t_vec2 curr_cf, t_hit_infos *infos)
{
	SDL_Surface *text;
	t_ivec2		tex;
	t_color		color;

	text = sdl_get_texture(text_id);
	tex.x = (int)(curr_cf.x * text->w) % text->w;
	tex.y = (int)(curr_cf.y * text->h) % text->h;
	color = sdl_get_pixel(text, tex.x, tex.y);
	return (color);
}

static void		draw_cf_line(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
					t_vec2 texel)
{
	t_vec2		curr_cf;
	double		weight;
	int			y;
	t_color		color;

	y = infos->draw_end;
	while (y < (int)sdl->height)
	{
		weight = cam->lookup_table[y] / infos->z;
		curr_cf.x = weight * texel.x + (1.0 - weight) * infos->ray.pos.x;
		curr_cf.y = weight * texel.y + (1.0 - weight) * infos->ray.pos.y;
		color = get_cf_color(3, curr_cf, infos);
		sdl->image[infos->x + y * sdl->width] = color;
		color = get_cf_color(5, curr_cf, infos);
		sdl->image[infos->x + ((int)sdl->height - y) * sdl->width] = color;

		y++;
	}
}

static void		render_floor(t_sdl *sdl, t_cam *cam, t_hit_infos *infos)
{
	t_vec2		texel;

	texel = get_wall_texel(infos);
	draw_cf_line(sdl, cam, infos, texel);
}

void		rc_render(t_sdl *sdl, t_cam *cam, t_map *map, t_hit_infos *infos)
{
	render_wall(sdl, map, infos);
	render_floor(sdl, cam, infos);
}
