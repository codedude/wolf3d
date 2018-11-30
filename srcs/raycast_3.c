/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/30 17:30:54 by vparis           ###   ########.fr       */
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

t_float			compute_depth(t_float z)
{
	if (z > MAX_DEPTH)
		return (0.0);
	else
		return (1.0 - (z / MAX_DEPTH));
}

t_vec3			set_depth_effect(t_vec3 c, t_float depth)
{
	if (depth == 0.0)
		return (VEC3_ZERO);
	else
		return (c * depth);
}
t_vec3			set_ambient_effect(t_vec3 c, t_float depth, t_vec3 ambient)
{
	if (depth == 0.0)
		return (ambient);
	else
		return (c * depth + ambient * (1.0 - depth));
}

t_vec3			set_color_effect(t_vec3 c, int effect)
{
	if (effect & EFFECT_BAW)
	{
		c[0] = c[0] * 0.21 + c[1] * 0.72 + c[2] * 0.07;
		c[1] = c[0];
		c[2] = c[0];
	}
	else if (effect & EFFECT_SEPIA)
	{
		c = VEC3_INIT(
			clamp_float(0.393 * c[0] + 0.769 * c[1] + 0.189 * c[2], 0.0, 255.0),
			clamp_float(0.349 * c[0] + 0.686 * c[1] + 0.168 * c[2], 0.0, 255.0),
			clamp_float(0.272 * c[0] + 0.534 * c[1] + 0.131 * c[2], 0.0, 255.0)
		);
	}
	return (c);
}

t_color			dark_color(t_color color, int effect, int side, t_float z)
{
	t_vec3		c;
	t_float		depth;

	c[0] = (t_float)(color & 0xff);
	c[1] = (t_float)((color & 0xff00) >> 8);
	c[2] = (t_float)((color & 0xff0000) >> 16);
	depth = compute_depth(z);
	if (side == 1 && effect & EFFECT_SIDE)
		c *= 0.66;
	if (effect & EFFECT_DEPTH)
		c = set_depth_effect(c, depth);
	else if (effect & EFFECT_FOG)
		c = set_ambient_effect(c, depth, VEC3_INIT(153.0, 211.0, 137.0));
	else if (effect & EFFECT_WATER)
		c = set_ambient_effect(c, depth / 2.0, VEC3_INIT(136.0, 210.0, 208.0));
	if (effect & EFFECT_MASK_FILTERS)
 		c = set_color_effect(c, effect);
	return (((t_color)c[0] | ((t_color)c[1] << 8) | ((t_color)c[2] << 16)));
}

static t_vec2	get_wall_texel(t_hit_infos *infos)
{
	t_vec2		texel;

	if(infos->side == 0)
		if (infos->ray.dir.x > 0)
		{
			texel.x = infos->map.x;
			texel.y = infos->map.y + infos->wall_x;
		}
		else
		{
			texel.x = infos->map.x + 1.0;
			texel.y = infos->map.y + infos->wall_x;
		}
	else
		if(infos->ray.dir.y > 0)
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

static t_color	get_cf_color(int text_id, t_vec2 curr_cf, int effect,
					t_float z)
{
	SDL_Surface *text;
	t_ivec2		tex;
	t_color		color;

	text = sdl_get_texture(text_id);
	tex.x = (int)(curr_cf.x * text->w) % text->w;
	tex.y = (int)(curr_cf.y * text->h) % text->h;
	color = dark_color(sdl_get_pixel(text, tex.x, tex.y), effect, 0, z);
	return (color);
}

/*
** Enelver le check le check cam->z
*/

static void		draw_floor_line(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
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
				/ (2.0 * (y - cam->height) - sdl->canvas_h);
			weight = lookup / infos->z;
			curr_cf.x = weight * texel.x + (1.0 - weight) * infos->ray.pos.x;
			curr_cf.y = weight * texel.y + (1.0 - weight) * infos->ray.pos.y;
			sdl->image[infos->x + y * sdl->width] = get_cf_color(
				DEFAULT_FLOOR, curr_cf, infos->effect, lookup);
		}
		else
			sdl->image[infos->x + y * sdl->width] = 0;
		y++;
	}
}

static void		draw_ceil_line(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
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
			sdl->image[infos->x + y * sdl->width] = get_cf_color(
				DEFAULT_CEIL, curr_cf, infos->effect, lookup);
		}
		else
			sdl->image[infos->x + y * sdl->width] = 0x0;
		y++;
	}
}

static void		draw_tex_line(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
					SDL_Surface *text)
{
	t_ivec2		tex;
	int			y;
	t_color 	color;
	t_float		half_height;

	tex.x = (int)(infos->wall_x * text->w);
	if(infos->side == 0 && infos->ray.dir.x > 0)
		tex.x = text->w - tex.x - 1;
	else if(infos->side == 1 && infos->ray.dir.y < 0)
		tex.x = text->w - tex.x - 1;
	half_height = -sdl->half_canvas_h + infos->line_height / 2.0
		+ ((sdl->half_canvas_h - cam->z) / infos->z);
	y = infos->draw_start;
	while (y < infos->draw_end)
	{
		tex.y = (int)fabs(text->h * ((y - cam->height + half_height)
			/ (t_float)(infos->line_height)));
		color = dark_color(sdl_get_pixel(text, tex.x, tex.y),
			infos->effect, infos->side, infos->z);
		sdl->image[infos->x + y * sdl->width] = color;
		y++;
	}
}

static void		render_wall(t_sdl *sdl, int **map, t_cam *cam,
					t_hit_infos *infos)
{
	SDL_Surface		*text;
	int				text_id;

	text_id = map[(int)infos->map.x][(int)infos->map.y] - 1;
	text = sdl_get_texture(text_id);
	draw_tex_line(sdl, infos, cam, text);
}

void			rc_render(t_sdl *sdl, t_cam *cam, t_map *map,
					t_hit_infos *infos)
{
	t_vec2	texel;

	render_wall(sdl, map->data, cam, infos);
	texel = get_wall_texel(infos);
	draw_floor_line(sdl, cam, infos, texel);
	draw_ceil_line(sdl, cam, infos, texel);
}
