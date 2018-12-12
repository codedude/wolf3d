/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/12 18:55:01 by vparis           ###   ########.fr       */
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

static t_vec2	get_wall_texel(t_hit_infos *infos)
{
	t_vec2		texel;

	if (infos->side == 0)
	{
		if (infos->ray.dir.x > 0)
			texel = VEC2_INIT(infos->map.x, infos->map.y + infos->wall_x);
		else
			texel = VEC2_INIT(infos->map.x + 1.0, infos->map.y + infos->wall_x);
	}
	else
	{
		if (infos->ray.dir.y > 0)
			texel = VEC2_INIT(infos->map.x + infos->wall_x, infos->map.y);
		else
			texel = VEC2_INIT(infos->map.x + infos->wall_x, infos->map.y + 1.0);
	}
	return (texel);
}

/*
void			draw_skybox(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
					t_map *map)
{
	int		y;
	t_float	lerp;
	t_float	ratio;
	t_color	color;

	color.rgba = 0x00;
	y = infos->draw_start;
	while (y < infos->draw_end)
	{
		lerp = clamp_float(y - cam->height, 0.0, sdl->canvas_h);
		ratio = 1.0 - (lerp / sdl->canvas_h);
		color.c.r = (unsigned char)(255.0 * ratio);
		color.c.g = (unsigned char)(255.0 * ratio);
		color.c.b = (unsigned char)(255.0 * ratio);
		sdl_put_pixel(sdl, infos->x, y, color);
		y++;
	}
}
*/

void			draw_skybox(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
					t_map *map)
{
	int			y;
	t_float		lerp;
	t_color		color;
	t_ivec2		pos;
	t_texture	*text;

	text = &map->skybox;
	y = infos->draw_start;
	while (y < infos->draw_end)
	{
		pos.x = (int)((infos->x + map->skybox_offset) / sdl->canvas_w
			* text->w);
		lerp = clamp_float(y - cam->height, 0.0, sdl->canvas_h - 1.0);
		pos.y = (int)(lerp / sdl->canvas_h * text->h);
		color = sdl_get_pixel(text, pos.x % text->w, pos.y);
		sdl_put_pixel(sdl, infos->x, y, color);
		y++;
	}
}

void			rc_render(t_sdl *sdl, t_cam *cam, t_map *map,
					t_hit_infos *infos)
{
	t_texture	*text;
	int			text_id;
	t_vec2		texel;

	if (infos->hit == 1)
	{
		text_id = map->data[(int)infos->map.y][(int)infos->map.x] - 1;
		text = sdl->textures + text_id;
		draw_wall(sdl, infos, cam, text);
	}
	texel = get_wall_texel(infos);
	draw_floor(sdl, cam, infos, texel);
	if (map->is_skybox == 0)
		draw_ceil(sdl, cam, infos, texel);
	if (map->is_skybox == 0 && infos->hit == 0)
		draw_skybox(sdl, infos, cam, map);
	else if (map->is_skybox == 1)
	{
		if (infos->hit == 1)
			infos->draw_end = infos->draw_start;
		infos->draw_start = 0;
		draw_skybox(sdl, infos, cam, map);
	}

}
