/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:34:21 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:48:05 by jbulant          ###   ########.fr       */
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
