/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_canvas.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:32:27 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

void		draw_canvas_border(t_sdl *sdl, t_canvas canvas, t_canvas parent,
							unsigned int color)
{
	t_ivec2		pos;
	t_ivec2		end;

	pos = canvas.pos;
	end = pos + canvas.size;
	while (pos.x <= end.x)
	{
		put_pixel_inside_canvas(sdl, parent, pos, color);
		put_pixel_inside_canvas(sdl, parent, IVEC2_INIT(pos.x, end.y), color);
		pos.x++;
	}
	pos = canvas.pos;
	while (pos.y <= end.y)
	{
		put_pixel_inside_canvas(sdl, parent, pos, color);
		put_pixel_inside_canvas(sdl, parent, IVEC2_INIT(end.x, pos.y), color);
		pos.y++;
	}
}

void		draw_canvas_fill(t_sdl *sdl, t_canvas *canvas, t_canvas *parent,
							unsigned int color)
{
	t_ivec2		pos;
	t_ivec2		end;

	end.x = canvas->pos.x + (canvas->size.x);
	end.y = canvas->pos.y + (canvas->size.y);
	pos.x = canvas->pos.x;
	while (pos.x < end.x)
	{
		pos.y = canvas->pos.y;
		while (pos.y < end.y)
		{
			put_pixel_inside_canvas(sdl, *parent, pos, color);
			pos.y++;
		}
		pos.x++;
	}
}
