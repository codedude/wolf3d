/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/06 19:04:13 by vparis           ###   ########.fr       */
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

void			rc_render(t_sdl *sdl, t_cam *cam, t_map *map,
					t_hit_infos *infos)
{
	t_texture	*text;
	int			text_id;
	t_vec2		texel;

	text_id = map->data[(int)infos->map.y][(int)infos->map.x] - 1;
	text = sdl->textures + text_id;
	draw_wall(sdl, infos, cam, text);
	texel = get_wall_texel(infos);
	draw_floor(sdl, cam, infos, texel);
	draw_ceil(sdl, cam, infos, texel);
}
