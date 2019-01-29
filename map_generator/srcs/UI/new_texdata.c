/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_texdata.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:30:56 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 03:02:51 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "libft.h"
#include "types.h"

static t_color	convert_pixel(t_color get)
{
	t_color		c;

	c.c.r = get.c.b;
	c.c.g = get.c.g;
	c.c.b = get.c.r;
	c.c.a = get.c.a;
	return (c);
}

t_color			*new_texdata(t_tex *tex, t_ivec2 size)
{
	t_color		*tdata;
	t_ivec2		i;
	t_ivec2		transpo;
	size_t		msize;

	msize = sizeof(t_color) * (size_t)size.x * (size_t)size.y;
	if (!(tdata = (t_color*)ft_memalloc(msize)))
		return (NULL);
	i.y = 0;
	while (i.y < size.y)
	{
		i.x = 0;
		while (i.x < size.x)
		{
			transpo.x = tex->w * i.x / size.x;
			transpo.y = tex->h * i.y / size.y;
			tdata[i.x + i.y * size.x] = convert_pixel(sdl_get_pixel(tex,
											transpo.x, transpo.y, 0));
			i.x++;
		}
		i.y++;
	}
	return (tdata);
}
