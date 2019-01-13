/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:18:37 by vparis            #+#    #+#             */
/*   Updated: 2019/01/13 15:17:50 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_math.h"
#include "libft.h"
#include "env.h"
#include "types.h"
#include "sdl_m.h"
#include "raycast.h"
#include "list.h"

/*
**	based on Barycentric_coordinate_system
**	p = p0 + (p1 - p0) * s + (p2 - p0) * t
**	p is inside if 0 <= s <= 1 and 0 <= t <= 1 and s + 1 <= 1
**
**	area = 1.0 / 2.0 * (-p1.y * p2.x + p0.y * (-p1.x + p2.x)
**						+ p0.x * (p1.y - p2.y) + p1.x * p2.y)
**	s    =  (p0.y * p2.x - p0.x * p2.y
**			 + (p2.y - p0.y) * p.x + (p0.x - p2.x) * p.y)
**		   * sign of area
**	t    =  (p0.x * p1.y - p0.y * p1.x + (p0.y - p1.y) * p.x
**			 + (p1.x - p0.x) * p.y) * sign of area
**
**	if s and t are both > 0 AND a + t < 2 * area * sign of area
**	then p is inside the triangle
**	else p is outside
**	return s > 0 && t > 0 && (s + t) < 2 * A * sign;
**
**	as we use our position as a vertice of the triangle
**	we can use expanded directions to ensure a correct range
**	to simulate infinite cone as we normalize the position of
**	the object to us.
**	this way, we can save at launch the area and the sign
**	(because they are both fixed value as the triangle of
**	the fov doesn't change in any case), then use them
**	when needed during the coordinate process
**	By these points, we can skip a lot of calculation
**	like multiplication, addition or substraction when
**	the first vertice (our position, with vectors translated, so [0,0])
**	is used:
**		  v0.y * v2.x - v0.x * v2.y
**		= 0 * v2_x - 0 * v2_y
**		= 0 - 0
**		= 0
**		v0.x - v2.x
**		= -v2.x
*/

/*
**	OLD VERSION
**	the variable area was used to know if the point is inside
**	the triangle, if we don't use it, we just take
**	the product of perpendicular of left-right side
**	with the point's position in order to know if the point
**	is on the left or the right of the side
**	with this, we don't need more normalization of vectors
**	and we skip more computation
**
**	t_bool		vec_is_in_front(t_vec2 left, t_vec2 right, t_vec2 p)
**	{
**		t_float	area;
**	    t_float	sign;
**		t_float	s;
**		t_float	t;
**
**		area = (-left.y * right.x + left.x * right.y);
**		sign = area < 0.0 ? -1.0 : 1.0;
**		s = (right.y * p.x + -right.x * p.y) * sign;
**		t = (-left.y * p.x + left.x * p.y) * sign;
**		if (s > 0 && t > 0 && (s + t) < area * sign)
**			return (True);
**		return (False);
**	}
**
**
**	OPTI : s*t > 0 ? check perf
*/

/*
** Sort asc
*/

int				sort_object(t_entity *a, t_entity *b)
{
	if (a->e.object->z_buffer < b->e.object->z_buffer)
		return (-1);
	if (b->e.object->z_buffer < a->e.object->z_buffer)
		return (1);
	return (0);
}

static t_float	vec_is_in_front(t_vec2 left, t_vec2 right, t_vec2 p)
{
	t_float	s;
	t_float	t;

	s = (right.y * p.x + -right.x * p.y);
	t = (-left.y * p.x + left.x * p.y);
	return (s / (s + t));
}

static t_bool	prepare_object(t_env *env, int i, t_vec2 obj_dir,
					t_float obj_x)
{
	int			half_width;
	int			x;
	t_object	*obj;
	t_vec2		old_size;

	obj = env->objects[i].e.object;
	obj->z_buffer = vec_len(obj_dir) * vec_dot(vec_norm(obj_dir), env->cam.dir);
	x = (int)(obj_x * env->sdl.canvas_w);
	obj->size.y = env->sdl.canvas_h / obj->z_buffer;
	obj->size.x = obj->size.y / env->sdl.canvas_h * env->sdl.canvas_w / 2.0;
	old_size = obj->size;
	if (obj->scale != 1.0)
		obj->size *= obj->scale;
	obj->x_offset = (int)(obj_x - clamp_float(obj_x, 0.0, env->sdl.canvas_w));
	if (abs(obj->x_offset) >= obj->size.x)
		return (False);
	obj->y_offset = (int)(obj->size.y * obj->z);
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
	half_width = (int)obj->size.x;
	half_width = half_width & 0x01 ? (half_width - 1) / 2 : half_width / 2;
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
	return (True);
}

int				precompute_sprites(t_env *env, t_klist **lst)
{
	t_vec2	dir[2];
	t_vec2	obj_dir;
	t_klist	*tmp;
	int		i;

	dir[0] = env->cam.dir - env->cam.plane;
	dir[1] = env->cam.dir + env->cam.plane;
	i = 0;
	while (i < env->objects_nb)
	{
		obj_dir = env->objects[i].e.object->pos - env->cam.pos;
		if (vec_is_in_front(-env->cam.plane, env->cam.plane, obj_dir) >= 0.0)
		{
			if (prepare_object(env, i, obj_dir, vec_is_in_front(dir[0], dir[1],
				obj_dir)) == True)
			{
				if ((tmp = klist_new(env->objects + i)) == NULL)
				{
					klist_clear(lst);
					return (ERROR);
				}
				klist_add_sort(lst, tmp, sort_object);
			}
		}
		i++;
	}
	return (SUCCESS);
}

/*
** TODO : sprite du 1er au dernier, et modif le z buffer, + transparence
**
*/

void			render_sprite(t_sdl *sdl, t_cam *cam, t_entity *obj)
{
	t_ivec2		tex;
	t_color		color;
	t_ivec2		it;
	t_tex		*text;
	t_object	*o;

	o = obj->e.object;
	text = tex_get_sprite(sdl, obj->tex_id);
	it.x = o->x_start < 0 ? 0 : o->x_start;
	while (it.x < o->x_end)
	{
		if (o->z_buffer < sdl->z_buffer[it.x])
		{
			it.y = o->y_start < 0 ? 0 : o->y_start;
			tex.x = (int)((it.x - o->x_start + o->x_offset)
				/ o->size.x * text->w);
			while (it.y < o->y_end)
			{
				tex.y = (int)((it.y - o->y_start + o->y_offset)
					/ o->size.y * text->h);
				if (tex.y >= 0 && tex.y < text->h)
				{
					color = sdl_get_pixel(text, tex.x, tex.y, obj->tex_key);
					if (color.rgba > 0)
						sdl_put_pixel(sdl, it.x, it.y,
							dark_color(color, cam, 0, o->z_buffer));
				}
				it.y++;
			}
		}
		it.x++;
	}
}

void			compute_sprites(t_env *env)
{
	t_klist		*lst;
	t_klist		*iter;
	t_entity	*obj;

	lst = NULL;
	if (precompute_sprites(env, &lst) == ERROR)
		return ;
	iter = lst;
	while (iter != NULL)
	{
		obj = iter->value;
		render_sprite(&env->sdl, &env->cam, obj);
		iter = iter->next;
	}
	klist_clear(&lst);
}
