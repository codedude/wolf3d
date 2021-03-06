/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 11:57:15 by vparis            #+#    #+#             */
/*   Updated: 2019/01/29 20:30:57 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "raycast.h"
#include "types.h"

void	draw_skybox(t_sdl *sdl, t_hit_infos *infos, t_cam *cam, t_map *map)
{
	int			y;
	t_float		lerp;
	t_color		color;
	t_ivec2		pos;
	t_tex		*text;

	text = &sdl->tex_skybox;
	y = infos->draw_start;
	while (y < infos->draw_end)
	{
		pos.x = ((int)((infos->x + map->skybox->tex_key) / sdl->canvas_w
			* text->w) + (map->skybox->id / 2)) % text->w;
		lerp = clamp_float(y - cam->height, 0.0f, sdl->canvas_h - 1.0f);
		pos.y = (int)(lerp / sdl->canvas_h * text->h);
		color = dark_color(sdl_get_pixel(text, pos.x, pos.y, 0),
			cam, 0, 0.0f);
		sdl_put_pixel(sdl, infos->x, y, color);
		y++;
	}
}

void	draw_floor(t_env *env, t_sdl *sdl, t_hit_infos *infos, t_vec2 texel)
{
	t_vec2		curr_cf;
	t_float		lookup;
	t_float		z_by_half_canvas;
	t_float		weight;
	int			y;

	z_by_half_canvas = sdl->canvas_h * env->cam.z / sdl->half_canvas_h;
	y = infos->draw_end;
	while (y < sdl->height)
	{
		if (env->cam.z > 0.0f)
		{
			lookup = z_by_half_canvas
				/ (2.0f * ((y + 1) - env->cam.height) - sdl->canvas_h);
			weight = lookup / infos->z;
			curr_cf.x = weight * texel.x + (1.0f - weight) * infos->ray.pos.x;
			curr_cf.y = weight * texel.y + (1.0f - weight) * infos->ray.pos.y;
			sdl_put_pixel(sdl, infos->x, y, get_cf_color(tex_get_wall(
				sdl, env->map.floor_id), curr_cf, &env->cam, lookup));
		}
		else
			sdl->image[infos->x + y * sdl->width] = 0;
		++y;
	}
}

void	draw_ceil(t_env *env, t_sdl *sdl, t_hit_infos *infos, t_vec2 texel)
{
	t_vec2		curr_cf;
	t_float		weight;
	t_float		lookup;
	t_float		z_by_half_canvas;
	int			y;

	z_by_half_canvas = sdl->canvas_h * (sdl->canvas_h - env->cam.z)
		/ sdl->half_canvas_h;
	y = 0;
	while (y < infos->draw_start)
	{
		if (env->cam.z < sdl->canvas_h)
		{
			lookup = z_by_half_canvas
				/ fabsf(2.0f * (y - env->cam.height) - sdl->canvas_h);
			weight = lookup / infos->z;
			curr_cf.x = weight * texel.x + (1.0f - weight) * infos->ray.pos.x;
			curr_cf.y = weight * texel.y + (1.0f - weight) * infos->ray.pos.y;
			sdl_put_pixel(sdl, infos->x, y, get_cf_color(tex_get_wall(
				sdl, env->map.ceil_id), curr_cf, &env->cam, lookup));
		}
		else
			sdl->image[infos->x + y * sdl->width] = 0x0;
		++y;
	}
}

void	draw_wall(t_sdl *sdl, t_hit_infos *infos, t_cam *cam)
{
	int				tex[2];
	int				y;
	t_color			color;
	t_float			half_height;
	t_tex			*text;

	text = infos->tex;
	tex[0] = (int)fmod(fabs(infos->wall_x - infos->tex_off_x) * text->w,
		text->w);
	if (infos->side == 0 && infos->ray.dir.x > 0)
		tex[0] = text->w - tex[0] - 1;
	else if (infos->side == 1 && infos->ray.dir.y < 0)
		tex[0] = text->w - tex[0] - 1;
	half_height = -sdl->half_canvas_h + infos->line_height / 2.0f
		+ ((sdl->half_canvas_h - cam->z) / infos->z);
	y = infos->draw_start;
	while (y < infos->draw_end)
	{
		tex[1] = (int)fabs(text->h * ((y - cam->height + half_height)
			/ (t_float)(infos->line_height)));
		color = dark_color(sdl_get_pixel(text, tex[0], tex[1], infos->tex_key),
			cam, infos->side & cam->side_filter, infos->z);
		sdl_put_pixel(sdl, infos->x, y, color);
		++y;
	}
}
