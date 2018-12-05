/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_previewbox.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 17:30:56 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/05 16:55:33 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "libft.h"
#include "types.h"
#include "gen_env.h"

static t_color	*new_texdata(t_texture *tex, t_ivec2 size)
{
	t_color		*tdata;
	t_ivec2		i;
	t_ivec2		transpo;
	size_t		msize;

	msize = sizeof(t_color) * (size_t)size.y * (size_t)size.y;
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
			tdata[i.x + i.y * size.x] = sdl_get_pixel(tex,
											transpo.x, transpo.y);
			i.x++;
		}
		i.y++;
	}
	return (tdata);
}

t_tex_pbox			*new_tex_previewbox(t_sdl *sdl, t_texture *tex, int id)
{
	t_tex_pbox	*tbox;
	t_canvas	psize;

	if (!(tbox = (t_tex_pbox *)malloc(sizeof(*tbox))))
		return (NULL);
	psize.pos = 0;
	psize.size = ipercent_of(sdl->height, PREV_BOX_PERC);
	tbox->tex_id = id;
	tbox->canvas = psize;
	tbox->next = NULL;
	if (!(tbox->tex_data = new_texdata(tex, psize.size)))
	{
		free(tbox);
		return (NULL);
	}
	return (tbox);
}

void				tex_previewbox_add(t_tex_pbox **abox, t_tex_pbox *add)
{
	if (add)
		add->next = *abox;
	*abox = add;
}

void				destroy_tex_previewbox(t_tex_pbox *pbox)
{
	if (!pbox)
		return ;
	destroy_tex_previewbox(pbox->next);
	if (pbox->tex_data)
		free(pbox->tex_data);
	free(pbox);
}
