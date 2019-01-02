/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texdata_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 23:02:05 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/26 22:47:12 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"

void				texdata_draw_circle_filled(t_color *tex, t_canvas anchor,
										t_float radius, t_u32 color)
{
	t_ivec2		i;
	t_ivec2		px;

	radius *= radius;
	i.y = -(anchor.size.y / 2);
	while (i.y <= anchor.size.y / 2)
	{
		i.x = -(anchor.size.x / 2);
		while (i.x <= anchor.size.x / 2)
		{
			px = i + anchor.pos;
			if (i.x * i.x + i.y * i.y < radius)
				tex[px.x + px.y * anchor.size.x].rgba = color;
			i.x++;
		}
		i.y++;
	}
}

void			sdl_draw_circle(t_sdl *sdl, t_ivec2 pos, t_float radius,
						t_u32 color)
{
	int			i;
	t_ivec2		px;

	i = 0;
	while(i <= 360 * radius)
	{
		px = pos;
		px.x += (int)(sin((t_float)i) * radius);
		px.y += (int)(cos((t_float)i) * radius);
		sdl_put_pixel_safe(sdl, px, (t_color)color);
		i++;
	}
}

void				texdata_fill_rect(t_color *tex, t_ivec2 t_size,
										t_canvas rect, t_u32 color)
{
	t_ivec2		i;
	t_ivec2		px;

	i.y = 0;
	while (i.y < rect.size.y && i.y + rect.pos.y < t_size.y)
	{
		i.x = 0;
		while (i.x < rect.size.x && i.x + rect.pos.x < t_size.x)
		{
			px = i + rect.pos;
			tex[px.x + px.y * t_size.x].rgba = color;
			i.x++;
		}
		i.y++;
	}
}

void				texdata_draw_rect(t_color *tex, t_ivec2 t_size,
										t_canvas rect, t_u32 color)
{
	t_ivec2		i;
	t_ivec2		px;

	i.y = 0;
	while (i.y < rect.size.y)
	{
		px.y = i.y + rect.pos.y;
		px.x = rect.pos.x;
		if (px.x < t_size.x)
			tex[px.x + px.y * t_size.x].rgba = color;
		px.x += rect.size.x;
		if (rect.pos.x + rect.size.x < t_size.x)
			tex[px.x + px.y * t_size.x].rgba = color;
		i.y++;
	}
	i.x = 0;
	while (i.x < rect.size.x)
	{
		px.x = i.x + rect.pos.x;
		px.y = rect.pos.y;
		if (px.y < t_size.y)
			tex[px.x + px.y * t_size.x].rgba = color;
		px.y += rect.size.y;
		if (rect.pos.y + rect.size.y < t_size.y)
			tex[px.x + px.y * t_size.x].rgba = color;
		i.x++;
	}
}
