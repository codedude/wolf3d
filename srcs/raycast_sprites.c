/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:18:37 by vparis            #+#    #+#             */
/*   Updated: 2018/12/05 04:31:55 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "types.h"
#include "sdl_m.h"
#include "raycast.h"

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
			 + (p1.x - p0.x) * p.y) * sign of area
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

t_bool		vec_is_in_front(t_vec2 left, t_vec2 right, t_vec2 p)
{
	t_float	area;
    t_float	sign;
	t_float	s;
	t_float	t;

	area = (-left.y * right.x + left.x * right.y);
	sign = area < 0.0 ? -1.0 : 1.0;
	s = (right.y * p.x + -right.x * p.y) * sign;
	t = (-left.y * p.x + left.x * p.y) * sign;
	if (s > 0 && t > 0 && (s + t) < area * sign)
		return (True);
	return (False);
}

void		render_sprites(t_env *env)
{
	t_vec2	dir[2];
	t_vec2	obj_dir;
	int		i;

	dir[0] = vec_norm(env->cam.dir + -env->cam.plane) * 5;
	dir[1] = vec_norm(env->cam.dir + env->cam.plane) * 5;
	obj_dir = vec_norm(env->objects[0].pos - env->cam.pos);
	i = 0;
	while (i < env->objects_nb)
	{
		if (vec_is_in_front(dir[0], dir[1], obj_dir) == True)
			printf("obj[%d] (type: %d) : INSIDE\n");
		else
			printf("obj[%d] (type: %d) : NOT INSIDE\n");
		i++;
	}
}

// void		render_sprites(t_env *env)
// {
// 	t_vec2	range_dir[2];
// 	t_float	range_ang[2];
// 	t_float	tmp;
// 	t_vec2	object_dir;
// 	t_float	ang;
//
// 	range_dir[0] = vec_norm(env->cam.dir + -env->cam.plane);
// 	range_dir[1] = vec_norm(env->cam.dir + env->cam.plane);
// 	object_dir = vec_norm(env->objects[0].pos - env->cam.pos);
// 	range_ang[0] = atan2(range_dir[0].y, range_dir[0].x);
// 	range_ang[1] = atan2(range_dir[1].y, range_dir[1].x);
// 	ang = atan2(object_dir.y, object_dir.x);
// 	if (range_ang[0] < 0.0)
// 		range_ang[0] = fabs(range_ang[0]);
// 	else
// 		range_ang[0] = M_PI + (M_PI - range_ang[0]);
// 	if (range_ang[1] < 0.0)
// 		range_ang[1] = fabs(range_ang[1]);
// 	else
// 		range_ang[1] = M_PI + (M_PI - range_ang[1]);
// 	if (ang < 0.0)
// 		ang = fabs(ang);
// 	else
// 		ang = M_PI + (M_PI - ang);
// 	printf("ang-min: %f\nang-max: %f\nang-obj: %f\n", range_ang[0] / M_PI * 180.0, range_ang[1] / M_PI * 180.0, ang / M_PI * 180.0);
// 	if ((ang >= range_ang[0] && ang <= range_ang[1]))
// 		printf("INSIDE\n");
// 	else
// 		printf("NOT INSIDE\n");
// }
