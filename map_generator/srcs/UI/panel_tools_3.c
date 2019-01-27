/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_tools_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 18:34:21 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:47:49 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "gen_env.h"

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
