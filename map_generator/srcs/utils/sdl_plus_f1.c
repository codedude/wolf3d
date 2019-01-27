/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_plus_f1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 01:34:21 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 02:16:07 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "sdl_plus.h"
#include "types.h"

t_color			compute_color(t_color_pick *cpick, t_color c)
{
	t_color			compute;

	if (cpick->use_col_mask == False)
		return (c);
	compute.c.r = (t_u8)(c.c.r * (1.0 - cpick->cmask_height)
		+ cpick->color_mask.c.r * cpick->cmask_height);
	compute.c.g = (t_u8)(c.c.g * (1.0 - cpick->cmask_height)
		+ cpick->color_mask.c.g * cpick->cmask_height);
	compute.c.b = (t_u8)(c.c.b * (1.0 - cpick->cmask_height)
		+ cpick->color_mask.c.b * cpick->cmask_height);
	compute.c.a = (t_u8)(c.c.a * (1.0 - cpick->cmask_height)
		+ cpick->color_mask.c.a * cpick->cmask_height);
	return (compute);
}

t_color			tex_px_getscaled(t_tex *tex, int kframe,
					t_ivec2 from, t_ivec2 scale)
{
	t_color		c;
	t_color		c_ret;
	int			convert;

	convert = tex->w * from.x / scale.x + tex->h * from.y / scale.y * tex->w;
	c.rgba = tex->pixels[kframe % tex->n_sprites][convert];
	c_ret.c.r = c.c.b;
	c_ret.c.g = c.c.g;
	c_ret.c.b = c.c.r;
	c_ret.c.a = c.c.a;
	return (c_ret);
}


t_color			sdl_pixel_pick_from_img(t_sdl *sdl, int x, int y)
{
	unsigned char	*img;
	int				pos;
	t_color			c;

	img = sdl->image;
	pos = x * sdl->bpp + y * sdl->pitch;
	c.c.r = img[pos];
	c.c.g = img[pos + 1];
	c.c.b = img[pos + 2];
	c.c.a = 0;
	return (c);
}

void			sdl_put_pixel_safe(t_sdl *sdl, t_ivec2 px, t_color c)
{
	if (px.x >= 0 && px.x < sdl->width
		&& px.y >= 0 && px.y < sdl->height)
		sdl_put_pixel(sdl, px.x, px.y, c);
}

int				sdl_clear_color(t_sdl *sdl, unsigned int color)
{
	t_ivec2		i;
	t_color		col;

	col.rgba = color;
	i.y = 0;
	while (i.y < sdl->height)
	{
		i.x = 0;
		while (i.x < sdl->width)
		{
			sdl_put_pixel(sdl, i.x, i.y, col);
			i.x++;
		}
		i.y++;
	}
	return (SUCCESS);
}
