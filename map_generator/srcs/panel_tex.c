/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_tex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:30:56 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/18 02:21:23 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "libft.h"
#include "types.h"
#include "gen_env.h"

t_color			convert_pixel(t_color get)
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
			transpo.x = (int)((t_float)tex->w / 100.0
						* ((t_float)i.x * 100.0 / (t_float)size.x));
			transpo.y = (int)((t_float)tex->h / 100.0
						* ((t_float)i.y * 100.0 / (t_float)size.y));
			tdata[i.x + i.y * size.x] = convert_pixel(sdl_get_pixel(tex,
											transpo.x, transpo.y, 0));
			i.x++;
		}
		i.y++;
	}
	return (tdata);
}

void			destroy_panel_tex(t_color ***pbox_src, t_u32 nb)
{
	t_u32	i;
	t_color	**box;

	box = *pbox_src;
	if (!box)
		return ;
	i = 0;
	while (i < nb)
	{
		free(box[i]);
		i++;
	}
	free(box);
	*pbox_src = NULL;
}

t_color			**new_panel_tex(t_sdl *sdl, t_u32 nb, t_ivec2 size,
								t_tex *(*tex_src)(t_sdl*, int))
{
	t_color		**tex;
	t_u32		i;

	if (!(tex = (t_color**)ft_memalloc(sizeof(*tex) * nb)))
		return (NULL);
	i = 0;
	while (i < nb)
	{
		if (!(tex[i] = new_texdata(tex_src(sdl, (int)i), size)))
		{
			destroy_panel_tex(&tex, nb);
			return (NULL);
		}
		i++;
	}
	return (tex);
}
