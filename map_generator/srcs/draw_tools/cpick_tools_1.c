/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpick_tools_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:15:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 22:45:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"
#include "sdl_m.h"
#include "sdl_plus.h"
#include "libft.h"
#include "types.h"

void			cpick_set_color_mask(t_color_pick *cpick,
					t_u32 color, t_float height)
{
	cpick->color_mask.rgba = color;
	cpick->cmask_height = clamp_float(height, 0.0, 1.0);
	cpick->use_col_mask = True;
}

void			cpick_unset_color_mask(t_color_pick *cpick)
{
	cpick->use_col_mask = False;
}

void			cpick_set_color(t_color_pick *cpick, t_u32 color)
{
	cpick->current.rgba = color;
}

void			cpick_set_canvas(t_color_pick *cpick, t_canvas canvas)
{
	cpick->canvas_mask = canvas;
	cpick->use_canvas = True;
}

void			cpick_unset_canvas(t_color_pick *cpick)
{
	cpick->use_canvas = False;
}
