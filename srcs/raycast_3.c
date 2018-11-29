/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/29 19:30:49 by vparis           ###   ########.fr       */
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

t_float		compute_depth(t_float z)
{
	if (z >= MAX_DEPTH)
		return (0.0);
	else
		return (1.0 - (z / MAX_DEPTH));
}

t_color		dark_color(t_color color, int effect, int side, t_float z)
{
	t_vec3		c;
	t_vec3		c_tmp;
	t_float		depth;


	c[0] = (t_float)(color & 0xff);
	c[1] = (t_float)((color & 0xff00) >> 8);
	c[2] = (t_float)((color & 0xff0000) >> 16);
	depth = compute_depth(z);
	if (side == 1 && effect & EFFECT_SIDE)
		c *= 0.66;
	if (effect & EFFECT_DEPTH)
	{
		if (depth == 0.0)
			c = VEC3_ZERO;
		else
			c *= depth;
	}
	else if (effect & EFFECT_FOG)
	{
		c_tmp = VEC3_INIT(153.0, 211.0, 137.0);
		if (depth == 0.0)
			c = c_tmp;
		else
			c = c * depth + c_tmp * (1.0 - depth);
	}
	else if (effect & EFFECT_WATER)
	{
		c_tmp = VEC3_INIT(136.0, 210.0, 208.0);
		if (depth == 0.0)
			c = c_tmp;
		else
		{
			depth /= 2.0;
			c = c * depth + c_tmp * (1.0 - depth);
		}
	}
 	if (effect & EFFECT_BAW)
	{
		c = c * VEC3_INIT(0.21, 0.72, 0.07);
		c[0] = c[0] + c[1] + c[2];
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
	return ((t_color)(
		(t_color)c[0] | ((t_color)c[1] << 8) | ((t_color)c[2] << 16))
	);
}

static void		draw_tex_line(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
								SDL_Surface * text)
{
	t_ivec2				tex;
	int					y;
	t_color 			color;
	t_float				half_height;

	tex.x = (int)(infos->wall_x * (t_float)text->w);
	if(infos->side == 0 && infos->ray.dir.x > 0)
		tex.x = text->w - tex.x - 1;
	if(infos->side == 1 && infos->ray.dir.y < 0)
		tex.x = text->w - tex.x - 1;
	y = infos->draw_start;
	half_height = -(sdl->height / 2.0) + infos->line_height / 2.0 + ((HALF_HEIGHT - cam->z) / infos->z);
	while (y < infos->draw_end)
	{
		tex.y = (int)fabs(text->h * (((t_float)y - cam->height + half_height)
			/ (t_float)(infos->line_height)));
		color = dark_color(sdl_get_pixel(text, tex.x, tex.y),
			infos->effect, infos->side, infos->z);
		sdl->image[infos->x + y * sdl->width] = color;
		y++;
	}
}

static void		render_wall(t_sdl *sdl, t_map *map, t_cam *cam, t_hit_infos *infos)
{
	SDL_Surface			*text;
	int					text_id;

	text_id = map->data[(int)infos->map.x][(int)infos->map.y] - 1;
	text = sdl_get_texture(text_id);
	draw_tex_line(sdl, infos, cam, text);
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

static void		draw_floor_line(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
					t_vec2 texel)
{
	t_vec2		curr_cf;
	t_float		weight_x;
	t_float		weight_y;
	t_float		lookup_x;
	t_float		lookup_y;
	int			y;

	y = infos->draw_end;
	while (y < (int)sdl->height)
	{
		lookup_x = sdl->height / (
			(2.0 *
			((y + 1) - cam->height)
			- sdl->height
			)
		);
		lookup_y = sdl->height / (
			(2.0 *
			((y + 1) - cam->height)
			- sdl->height
			)
		);
		// printf("%f\n", lookup_x);
		// weight * factor = zoom texture
		weight_x = (lookup_x / infos->z);
		weight_y = (lookup_y / infos->z);
		curr_cf.x = weight_x * texel.x + (1.0 - weight_x) * infos->ray.pos.x;
		curr_cf.y = weight_y * texel.y + (1.0 - weight_y) * infos->ray.pos.y;
		sdl->image[infos->x + y * sdl->width] = get_cf_color(
			DEFAULT_FLOOR, curr_cf, infos->effect, lookup_x);
		y++;
	}
}

static void		draw_ceil_line(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
					t_vec2 texel)
{
	t_vec2		curr_cf;
	t_float		weight;
	t_float		lookup;
	int			y;

	y = 0;
	while (y < infos->draw_start)
	{
		lookup = sdl->height / fabs(2.0 * (y - cam->height) - sdl->height
			+ (HALF_HEIGHT - cam->z));
		weight = lookup / infos->z;
		curr_cf.x = weight * texel.x + (1.0 - weight) * infos->ray.pos.x;
		curr_cf.y = weight * texel.y + (1.0 - weight) * infos->ray.pos.y;
		sdl->image[infos->x + y * sdl->width] = get_cf_color(
			DEFAULT_CEIL, curr_cf, infos->effect, lookup);
		y++;
	}
}

static void		render_floor(t_sdl *sdl, t_cam *cam, t_hit_infos *infos)
{
	t_vec2		texel;

	texel = get_wall_texel(infos);
	draw_floor_line(sdl, cam, infos, texel);
	//draw_ceil_line(sdl, cam, infos, texel);
}

void		rc_render(t_sdl *sdl, t_cam *cam, t_map *map, t_hit_infos *infos)
{
	render_wall(sdl, map, cam, infos);
	render_floor(sdl, cam, infos);
}
