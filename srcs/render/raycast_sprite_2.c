/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprite_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 16:40:37 by vparis            #+#    #+#             */
/*   Updated: 2019/01/13 17:10:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "env.h"
#include "types.h"
#include "sdl_m.h"
#include "raycast.h"
#include "list.h"

static void		prepare_object_x_and_opti(t_env *env, t_object *obj,
					t_float obj_x)
{
	int		half_width;
	int		x;

	half_width = (int)obj->size.x;
	half_width = half_width & 0x01 ? (half_width - 1) / 2 : half_width / 2;
	x = (int)(obj_x * env->sdl.canvas_w);
	obj->x_start = x - half_width;
	if (obj->x_offset < 0)
		obj->x_end = x + half_width + obj->x_offset;
	else
		obj->x_end = x + half_width - obj->x_offset;

	if (obj->x_end >= env->sdl.width)
		obj->x_end = env->sdl.width - 1;
	if (obj->y_end >= env->sdl.height)
		obj->y_end = env->sdl.height - 1;
	obj->x_offset = obj->x_offset < 0 ? -obj->x_offset : 0;
	obj->y_offset = obj->z > 0 ? obj->y_offset : 0;
}

static void		prepare_object_y(t_env *env, t_object *obj, t_vec2 old_size)
{
	obj->y_start = (int)((env->sdl.half_canvas_h - obj->size.y / 2.0)
		- ((env->sdl.half_canvas_h - env->cam.z) / obj->z_buffer)
		+ env->cam.height);
	if (obj->scale != 1.0)
		obj->y_start += (old_size.y - obj->size.y) / 2.0;
	obj->y_end = obj->y_start + (int)obj->size.y;
	if (obj->z > 0)
		obj->y_end -= obj->y_offset;
	else
		obj->y_start -= obj->y_offset;
}

t_bool			prepare_object(t_env *env, int i, t_vec2 obj_dir,
					t_float obj_x)
{
	t_object	*obj;
	t_vec2		old_size;

	obj = env->objects[i].e.object;
	obj->z_buffer = vec_len(obj_dir) * vec_dot(vec_norm(obj_dir), env->cam.dir);
	obj->size.y = env->sdl.canvas_h / obj->z_buffer;
	obj->size.x = obj->size.y / env->sdl.canvas_h * env->sdl.canvas_w / 2.0;
	old_size = obj->size;
	if (obj->scale != 1.0)
		obj->size *= obj->scale;
	obj->x_offset = (int)(obj_x - clamp_float(obj_x, 0.0, env->sdl.canvas_w));
	if (abs(obj->x_offset) >= obj->size.x)
		return (False);
	obj->y_offset = (int)(obj->size.y * obj->z);
	prepare_object_y(env, obj, old_size);
	prepare_object_x_and_opti(env, obj, obj_x);
	return (True);
}

static void		s_put_color(t_color color, t_env *env, t_ivec2 it,
				t_float z_buffer)
{
	if (color.rgba > 0)
		sdl_put_pixel(&env->sdl, it.x, it.y,
			dark_color(color, &env->cam, 0, z_buffer));
}

void			draw_sprite(t_env *env, t_sdl *sdl, t_entity *obj)
{
	t_ivec2		tex;
	t_ivec2		it;
	t_tex		*text;
	t_object	*o;

	o = obj->e.object;
	text = tex_get_sprite(sdl, obj->tex_id);
	it.x = o->x_start < 0 ? -1 : o->x_start;
	while (++it.x < o->x_end)
		if (o->z_buffer < sdl->z_buffer[it.x])
		{
			it.y = o->y_start < 0 ? -1 : o->y_start;
			tex.x = (int)((it.x - o->x_start + o->x_offset)
				/ o->size.x * text->w);
			while (++it.y < o->y_end)
			{
				tex.y = (int)((it.y - o->y_start + o->y_offset)
					/ o->size.y * text->h);
				if (tex.y >= 0 && tex.y < text->h)
					s_put_color(sdl_get_pixel(text, tex.x, tex.y, obj->tex_key),
						env, it, o->z_buffer);
			}
		}
}