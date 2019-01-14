/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:34:21 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/20 14:33:12 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gen_env.h"

void			panel_set_bgcolor(t_panel *pan, t_u32 color)
{
	pan->draw_bg = True;
	pan->bg_col.rgba = color;
}

void			panel_set_bordercolor(t_panel *pan, t_u32 color)
{
	pan->draw_border = True;
	pan->border_col.rgba = color;
}

void			panel_set_highlight(t_panel *pan)
{
	pan->hightlight = True;
}

t_bool			panel_isinside(t_panel *pan, t_ivec2 point)
{
	return (is_bounded(point, pan->anchor));
}

t_canvas		panel_get_elem_anchor(t_panel *pan, int i)
{
	t_canvas	e_anch;

	e_anch = pan->elem_anchor;
	e_anch.pos.y += ((e_anch.pos.y * 2 * (i + 2)) + e_anch.size.y * i);
	return (e_anch);
}

void			panel_change_view(t_panel *pan, int move)
{
	int		vmin;
	int		vmax;

	vmin = (int)pan->view_min + move;
	vmax = (int)pan->view_max + move;
	if (vmin >= 0 && vmax <= (int)pan->nb_elem)
	{
		pan->view_min = (t_u32)vmin;
		pan->view_max = (t_u32)vmax;
	}
}

void			panel_update_view_to_cursor(t_panel *pan)
{
	if (pan->cursor < pan->view_min)
		panel_change_view(pan, (int)(pan->cursor - pan->view_min));
	else if (pan->cursor >= pan->view_max)
		panel_change_view(pan, (int)(pan->cursor - (pan->view_max - 1)));
}

void			panel_update_cursor(t_panel *pan, t_u32 new_curs)
{
	if (new_curs >= pan->nb_elem || new_curs == pan->cursor)
		return ;
	pan->cursor = new_curs;
	panel_update_view_to_cursor(pan);
}

int				panel_get_index_by_pos(t_panel *pan, t_ivec2 point)
{
	t_canvas	e_anch;
	t_u32		tmp_min;
	int			i;

	i = 0;
	tmp_min = pan->view_min;
	while (tmp_min < pan->view_max)
	{
		e_anch = panel_get_elem_anchor(pan, i);
		e_anch.pos += pan->anchor.pos;
		if (is_bounded(point, e_anch))
			return ((int)tmp_min);
		tmp_min++;
		i++;
	}
	return (-1);
}

void			panel_increase_view(t_panel *pan)
{
	if (pan->view_max < pan->nb_elem)
	{
		pan->view_max++;
		pan->view_min++;
	}
}

void			panel_decrease_view(t_panel *pan)
{
	if (pan->view_min > 0)
	{
		pan->view_max--;
		pan->view_min--;
	}
}
