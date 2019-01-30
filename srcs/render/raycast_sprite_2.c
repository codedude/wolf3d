/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 16:40:37 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 13:05:35 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "types.h"
#include "sdl_m.h"
#include "raycast.h"
#include "list.h"

static void			s_put_color(t_color color, t_env *env, int it[2],
				t_float z_buffer)
{
	if (color.rgba > 0)
	{
		sdl_put_pixel(&env->sdl, it[0], it[1],
			dark_color(color, &env->cam, 0, z_buffer));
	}
}

static inline void	pre_calc_c(t_float pre_calc4_it[4], t_tex *text,
					t_entity *obj, t_object **o)
{
	*o = obj->e.object;
	pre_calc4_it[0] = text->w / (*o)->size.x;
	pre_calc4_it[1] = (text->h / (*o)->size.y);
	pre_calc4_it[2] = (*o)->x_offset - (*o)->x_start;
	pre_calc4_it[3] = (*o)->y_offset - (*o)->y_start;
}

void				draw_sprite(t_env *env, t_sdl *sdl, t_entity *obj)
{
	int			tex[2];
	int			it[3];
	t_float		pre_calc4_it[4];
	t_tex		*text;
	t_object	*o;

	text = tex_get_sprite(sdl, obj->tex_id);
	pre_calc_c(pre_calc4_it, text, obj, &o);
	it[0] = (o->x_start < 0 ? 0 : o->x_start) - 1;
	it[2] = o->y_start < 0 ? 0 : o->y_start;
	while (++it[0] < o->x_end)
		if (o->z_buffer < sdl->z_buffer[it[0]])
		{
			it[1] = it[2];
			tex[0] = (int)((it[0] + pre_calc4_it[2]) * pre_calc4_it[0]);
			while (it[1] < o->y_end)
			{
				tex[1] = (int)((it[1] + pre_calc4_it[3]) * pre_calc4_it[1]);
				if (o->z > 0 && env->map.show_ceil == False)
					tex[1] = abs((int)(tex[1] + text->h * o->z) + 1) % text->h;
				s_put_color(sdl_get_pixel(text, tex[0], tex[1], obj->tex_key),
					env, it, o->z_buffer);
				++it[1];
			}
		}
}
