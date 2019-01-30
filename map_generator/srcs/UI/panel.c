/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:38:54 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:59:09 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "gen_env.h"

void			panel_destroy(t_panel **pan)
{
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

t_panel			*new_panel(t_u32 nb_elem, t_canvas anchor, t_tex *elems)
{
	t_panel		*pan;

	if (!(pan = ft_memalloc(sizeof(*pan))))
		return (NULL);
	pan->nb_elem = nb_elem;
	pan->tex = elems;
	pan->cursor = 0;
	panel_set_anchor(pan, anchor);
	pan->draw_bg = False;
	pan->draw_border = False;
	pan->hightlight = False;
	pan->view_min = 0;
	pan->view_max = pan->nb_elem < pan->viewable_elem ?
			pan->nb_elem : pan->viewable_elem;
	return (pan);
}
