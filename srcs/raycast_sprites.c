/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:18:37 by vparis            #+#    #+#             */
/*   Updated: 2018/12/10 17:46:53 by vparis           ###   ########.fr       */
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

x = ((angp - ang) * 100.0 / (1.0 - ang)) * 1280

*/
t_float		vec_is_in_front(t_vec2 left, t_vec2 right, t_vec2 p)
{
	t_float	s;
	t_float	t;

	s = (right.y * p.x + -right.x * p.y);
	t = (-left.y * p.x + left.x * p.y);
	if (s <= 0 && t <= 0)
		return (s / (s + t));
	return (-1.0);
}

int			sort_object(t_object *a, t_object *b)
{
	if (a->z < b->z)
		return (-1);
	if (b->z < a->z)
		return (1);
	return (0);
}

static t_float		get_z(t_vec2 obj_dir, t_vec2 dir)
{
	t_float		z;

	z = vec_len(obj_dir) * vec_dot(vec_norm(obj_dir), dir);
	return (z);
}

int			precompute_sprites(t_env *env, t_klist **lst)
{
	t_vec2	dir[2];
	t_vec2	obj_dir;
	t_klist	*tmp;
	t_float	obj_x;
	int		i;

	dir[0] = env->cam.dir - env->cam.plane;
	dir[1] = env->cam.dir + env->cam.plane;
	i = 0;
	while (i < env->objects_nb)
	{
		obj_dir = env->objects[i].pos - env->cam.pos;
		if ((obj_x = vec_is_in_front(dir[0], dir[1], obj_dir)) >= 0.0)
		{
			env->objects[i].z = get_z(obj_dir, env->cam.dir);
			env->objects[i].x = clamp_int(
				(int)(obj_x * env->sdl.canvas_w), 0, env->sdl.width);
			if ((tmp = list_new(env->objects + i)) == NULL)
			{
				list_clear(lst);
				return (ERROR);
			}
			list_add_sort(lst, tmp, sort_object);
		}
		i++;
	}
	return (SUCCESS);
}

void		render_sprite(t_env *env, t_object *obj)
{
	t_ivec2	y;
	t_vec2	sprite;
	t_ivec2	tex;
	int		tmp;
	int		i;
	int		j;
	t_color	color;

	sprite.y = floor(env->sdl.canvas_h / obj->z);
	sprite.x = floor(sprite.y / env->sdl.canvas_h * env->sdl.canvas_w / 2.0);
	y.x = (int)((env->sdl.half_canvas_h - sprite.y / 2.0) - ((env->sdl.half_canvas_h - env->cam.z) / obj->z) + env->cam.height);
	y.y = y.x + (int)sprite.y;
	tmp = obj->x - (int)(sprite.x / 2.0);
	j = tmp < 0 ? 0 : tmp;
	//TODO : what if odd ?
	//TODO : objects are shaking ?
	while (j < obj->x + (int)(sprite.x / 2.0) && j < env->sdl.width)
	{
		if (obj->z >= env->sdl.z_buffer[j])
		{
			j++;
			continue ;
		}
		i = y.x < 0 ? 0 : y.x;
		tex.x = (int)((j - tmp)
			/ sprite.x * obj->sprite->texture.w);
		while (i < y.y && i < env->sdl.height)
		{
			tex.y = (int)((i - y.x)
				/ sprite.y * obj->sprite->texture.h);
			color = sdl_get_pixel(&obj->sprite->texture, tex.x, tex.y);
			if (color.rgba > 0)
				env->sdl.image[j + i * env->sdl.width] = dark_color(
					color, &env->cam, 0, obj->z);
			i++;
		}
		j++;
	}
}

void		compute_sprites(t_env *env)
{
	t_klist		*lst;
	t_klist		*iter;
	t_object	*obj;

	lst = NULL;
	if (precompute_sprites(env, &lst) == ERROR)
		return ;
	iter = lst;
	while (iter != NULL)
	{
		obj = iter->value;
		render_sprite(env, obj);
		iter = iter->next;
	}
	list_clear(&lst);
}
