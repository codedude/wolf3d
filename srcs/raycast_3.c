/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/28 03:46:26 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"

t_float		compute_depth(int effect, int side, t_float z)
{
	t_float	depth_effect;

	if (effect > 0)
	{
		if (z >= MAX_DEPTH)
			depth_effect = 0.0;
		else
			depth_effect = 1.0 - (z / MAX_DEPTH);
	}
	else if (side == 1)
		depth_effect = 0.5;
	else
		depth_effect = -1.0;
	return (depth_effect);
}

t_color		dark_color(t_color color, int effect, int side, t_float z)
{
	t_color		c[3];
	t_color		tmp[3];
	t_float		step;

	step = compute_depth(effect, side, z);
	if (step < 0.0)
		return (color);
	c[0] = color & 0xff;
	c[1] = (color & 0xff00) >> 8;
	c[2] = (color & 0xff0000) >> 16;
	if (effect == EFFECT_NONE)
	{
		c[0] *= step;
		c[1] *= step;
		c[2] *= step;
	}
	else if (effect == EFFECT_DEPTH)
	{
		c[0] *= step;
		c[1] *= step;
		c[2] *= step;
	}
	else if (effect == EFFECT_FOG)
	{
		if (step == 0.0)
		{
			c[0] = 153;
			c[1] = 211;
			c[2] = 137;
		}
		else
		{
			c[0] = c[0] * step + 153 * (1.0 - step);
			c[1] = c[1] * step + 211 * (1.0 - step);
			c[2] = c[2] * step + 137 * (1.0 - step);
		}
	}
	else if (effect == EFFECT_UNDERWATER)
	{
		if (step == 0.0)
		{
			c[0] = 136;
			c[1] = 210;
			c[2] = 208;
		}
		else
		{
			c[0] = c[0] * (step / 2.0) + 136 * (1.0 - (step / 2.0));
			c[1] = c[1] * (step / 2.0) + 210 * (1.0 - (step / 2.0));
			c[2] = c[2] * (step / 2.0) + 208 * (1.0 - (step / 2.0));
		}
	}
	else if (effect == EFFECT_BLACKWHITE)
	{
		c[0] = 0.21 * c[0] + 0.72 * c[1] + 0.07 * c[2];
		c[1] = c[0];
		c[2] = c[0];
	}
	else if (effect == EFFECT_SEPIA)
	{
		tmp[0] = c[0];
		tmp[1] = c[1];
		tmp[2] = c[2];
		c[0] = clamp_i32(0.393 * tmp[0] + 0.769 * tmp[1] + 0.189 * tmp[2],
			0, 255);
		c[1] = clamp_i32(0.349 * tmp[0] + 0.686 * tmp[1] + 0.168 * tmp[2],
			0, 255);
		c[2] = clamp_i32(0.272 * tmp[0] + 0.534 * tmp[1] + 0.131 * tmp[2],
			0, 255);
	}
	return ((t_color)(c[0] | (c[1] << 8) | (c[2] << 16)));
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
	half_height = -(sdl->height / 2.0) + infos->line_height / 2.0;
	while (y < infos->draw_end)
	{
		tex.y = text->h * ((t_float)((t_float)(y - cam->height) + half_height)
			/ (t_float)(infos->line_height));
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

/*
** TODO : lookup table depth effect ?
*/

static void		draw_floor_line(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
					t_vec2 texel)
{
	t_vec2		curr_cf;
	double		weight;
	int			y;
	t_float		lookup;

	y = infos->draw_end;
	while (y < (int)sdl->height)
	{
		lookup = sdl->height / (2.0 * ((y + 1) - cam->height) - sdl->height);
		weight = lookup / infos->z;
		curr_cf.x = weight * texel.x + (1.0 - weight) * infos->ray.pos.x;
		curr_cf.y = weight * texel.y + (1.0 - weight) * infos->ray.pos.y;
		sdl->image[infos->x + y * sdl->width] = get_cf_color(
			3, curr_cf, infos->effect, lookup);
		y++;
	}
}

static void		draw_ceil_line(t_sdl *sdl, t_cam *cam, t_hit_infos *infos,
					t_vec2 texel)
{
	t_vec2		curr_cf;
	double		weight;
	int			y;
	t_float		lookup;

	y = 0;
	while (y < infos->draw_start)
	{
		lookup = sdl->height / fabs(2.0 * (y - cam->height) - sdl->height);
		weight = lookup / infos->z;
		curr_cf.x = weight * texel.x + (1.0 - weight) * infos->ray.pos.x;
		curr_cf.y = weight * texel.y + (1.0 - weight) * infos->ray.pos.y;
		sdl->image[infos->x + y * sdl->width] = get_cf_color(
			5, curr_cf, infos->effect, lookup);
		y++;
	}
}

static void		render_floor(t_sdl *sdl, t_cam *cam, t_hit_infos *infos)
{
	t_vec2		texel;

	texel = get_wall_texel(infos);
	draw_floor_line(sdl, cam, infos, texel);
	draw_ceil_line(sdl, cam, infos, texel);
}

void		rc_render(t_sdl *sdl, t_cam *cam, t_map *map, t_hit_infos *infos)
{
	render_wall(sdl, map, cam, infos);
	render_floor(sdl, cam, infos);
}
