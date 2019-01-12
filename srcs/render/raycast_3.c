/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/12 20:47:02 by vparis           ###   ########.fr       */
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
		if (infos->ray.dir.x > 0 || infos->is_thin == 1)
			texel = VEC2_INIT(infos->map.x, infos->map.y + infos->wall_x);
		else
			texel = VEC2_INIT(infos->map.x + 1.0, infos->map.y + infos->wall_x);
	}
	else
	{
		if (infos->ray.dir.y > 0 || infos->is_thin == 1)
			texel = VEC2_INIT(infos->map.x + infos->wall_x, infos->map.y);
		else
			texel = VEC2_INIT(infos->map.x + infos->wall_x, infos->map.y + 1.0);
	}
	return (texel);
}

void			draw_skybox(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
					t_map *map)
{
	int			y;
	t_float		lerp;
	t_color		color;
	t_ivec2		pos;
	t_tex		*text;

	text = tex_get_wall(sdl, map->skybox->tex_id);
	y = infos->draw_start;
	while (y < infos->draw_end)
	{
		pos.x = (int)((infos->x + map->skybox->tex_key) / sdl->canvas_w
			* text->w) + (map->skybox->id / 2);
		lerp = clamp_float(y - cam->height, 0.0, sdl->canvas_h - 1.0);
		pos.y = (int)(lerp / sdl->canvas_h * text->h);
		color = dark_color(sdl_get_pixel(text, pos.x % text->w, pos.y, 0),
			cam, 0, 0.0);
		sdl_put_pixel(sdl, infos->x, y, color);
		y++;
	}
}

void			rc_render(t_env *env, t_hit_infos *infos)
{
	t_tex		*text;
	int			text_id;
	t_vec2		texel;

	if (infos->hit == 1)
	{
		text_id = env->map.data[(int)infos->map.y][(int)infos->map.x].tex_id
			- 1;
		text = tex_get_wall(&env->sdl, text_id);
		draw_wall(&env->sdl, infos, &env->cam, text);
	}
	texel = get_wall_texel(infos);
	draw_floor(env, &env->sdl, infos, texel);
	if (env->map.show_ceil == 1)
		draw_ceil(env, &env->sdl, infos, texel);
	if (env->map.show_ceil == 1 && infos->hit == 0)
		draw_skybox(&env->sdl, infos, &env->cam, &env->map);
	else if (env->map.show_ceil == 0)
	{
		if (infos->hit == 1)
			infos->draw_end = infos->draw_start;
		infos->draw_start = 0;
		draw_skybox(&env->sdl, infos, &env->cam, &env->map);
	}
}
