/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:34:21 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:47:53 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gen_env.h"

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
