/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:38:54 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:45:03 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "gen_env.h"

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

void			panel_destroy(t_panel **pan)
{
	if (!*pan)
		return ;
	destroy_panel_tex(&(*pan)->elem_tex, (*pan)->nb_elem);
	free(*pan);
	*pan = NULL;
}

void			panel_set_anchor(t_panel *pan, t_canvas anchor)
{
	int			size;
	int			opposite_size;

	pan->anchor = anchor;
	if (anchor.size.x < anchor.size.y)
	{
		size = anchor.size.x;
		opposite_size = anchor.size.y;
	}
	else
	{
		size = anchor.size.y;
		opposite_size = anchor.size.x;
	}
	pan->viewable_elem = (t_u32)(opposite_size / size);
	pan->elem_anchor.size = ipercent_of(size, 90);
	pan->elem_anchor.pos = ipercent_of(size, 5);
}

t_panel			*new_panel(t_u32 nb_elem, t_canvas anchor, void *param,
						t_color **(*get_elems)(void *, t_ivec2),
						t_tex *elems)
{
	t_panel		*pan;

	if (!(pan = ft_memalloc(sizeof(*pan))))
		return (NULL);
	pan->nb_elem = nb_elem;
	pan->tex = elems;
	pan->cursor = 0;
	panel_set_anchor(pan, anchor);
	if (!(pan->elem_tex = get_elems(param, pan->elem_anchor.size)))
	{
		panel_destroy(&pan);
		return (NULL);
	}
	pan->draw_bg = False;
	pan->draw_border = False;
	pan->hightlight = False;
	pan->view_min = 0;
	pan->view_max = pan->nb_elem < pan->viewable_elem ?
			pan->nb_elem : pan->viewable_elem;
	return (pan);
}
