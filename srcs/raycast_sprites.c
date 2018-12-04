/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:18:37 by vparis            #+#    #+#             */
/*   Updated: 2018/12/04 19:48:46 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "types.h"
#include "sdl_m.h"
#include "raycast.h"

void		render_sprites(t_env *env)
{
	t_vec2	range_dir[2];
	t_float	range_ang[2];
	t_float	tmp;
	t_vec2	object_dir;
	t_float	ang;

	range_dir[0] = env->cam.dir + -env->cam.plane;
	range_dir[1] = env->cam.dir + env->cam.plane;
	object_dir = env->objects[0].pos - env->cam.pos;
	range_ang[0] = atan2(range_dir[0].y, range_dir[0].x);
	range_ang[1] = atan2(range_dir[1].y, range_dir[1].x);
	ang = atan2(object_dir.y, object_dir.x);
	if (range_ang[0] < 0.0)
		range_ang[0] = fabs(range_ang[0]);
	else
		range_ang[0] = M_PI + (M_PI - range_ang[0]);
	if (range_ang[1] < 0.0)
		range_ang[1] = fabs(range_ang[1]);
	else
		range_ang[1] = M_PI + (M_PI - range_ang[1]);
	if (ang < 0.0)
		ang = fabs(ang);
	else
		ang = M_PI + (M_PI - ang);
	if (range_ang[1] < range_ang[0])
	{

		// if (range_ang[1] > 0)
			// ang += 2.0 * M_PI;
		//range_ang[1] += 2.0 * M_PI;
	}
	// range_ang[0] = fmod(range_ang[0] + M_PI, 2.0 * M_PI);
	// range_ang[1] = fmod(range_ang[1] + M_PI, 2.0 * M_PI);
	// ang = fmod(ang + M_PI, 2.0 * M_PI);
	printf("ang-min: %f\nang-max: %f\nang-obj: %f\n", range_ang[0] / M_PI * 180.0, range_ang[1] / M_PI * 180.0, ang / M_PI * 180.0);
	if ((ang >= range_ang[0] && ang <= range_ang[1]))
		printf("INSIDE\n");
	else
		printf("NOT INSIDE\n");
}
