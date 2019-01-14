/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 16:37:09 by vparis            #+#    #+#             */
/*   Updated: 2019/01/14 16:07:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"
#include "types.h"

t_color				dark_color(t_color color, t_cam *cam, int side, t_float z)
{
	t_vec3		c;

	c = VEC3_INIT((t_float)color.c.r, (t_float)color.c.g, (t_float)color.c.b);
	if (side)
		c *= 0.80;
	if (cam->depth_filter)
		c = cam->depth_filter(c, z);
	if (cam->color_filter)
		c = cam->color_filter(c);
	color.rgba = (unsigned int)c[0] | (unsigned int)c[1] << 8
		| (unsigned int)c[2] << 16;
	return (color);
}

t_color				get_cf_color(t_tex *text, t_vec2 curr_cf, t_cam *cam,
						t_float z)
{
	t_ivec2			tex;
	t_color			color;

	tex.x = (int)fabs(curr_cf.x * text->w) % text->w;
	tex.y = (int)fabs(curr_cf.y * text->h) % text->h;
	color = dark_color(sdl_get_pixel(text, tex.x, tex.y, 0),
		cam, 0, z);
	return (color);
}
