/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_plus_f2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 01:34:21 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 02:16:27 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "sdl_plus.h"
#include "types.h"

void		put_pixel_to_image(t_sdl *sdl, t_ivec2 pos, unsigned int color)
{
	t_color		col;

	col.rgba = color;
	if (pos.x >= 0 && pos.x < sdl->width
	&& pos.y >= 0 && pos.y < sdl->height)
		sdl_put_pixel(sdl, pos.x, pos.y, col);
}

t_bool		is_bounded(t_ivec2 pos, t_canvas canvas)
{
	if (pos.x >= canvas.pos.x && pos.x < canvas.pos.x + canvas.size.x
	&& pos.y >= canvas.pos.y && pos.y < canvas.pos.y + canvas.size.y)
		return (True);
	return (False);
}

void		put_pixel_inside_canvas(t_sdl *sdl, t_canvas canvas, t_ivec2 pos,
								unsigned int color)
{
	canvas.pos += 1;
	if (canvas.size.x > 1)
		canvas.size -= 2;
	if (canvas.size.x == 0 || is_bounded(pos, canvas))
		sdl_put_pixel_safe(sdl, pos, (t_color)color);
}
