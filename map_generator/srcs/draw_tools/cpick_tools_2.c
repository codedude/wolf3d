/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpick_tools_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:15:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 22:45:30 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"
#include "sdl_m.h"
#include "sdl_plus.h"
#include "libft.h"
#include "types.h"

void			cpick_pick_color_replace(t_sdl *sdl, t_color_pick *cpick,
					t_ivec2 px)
{
	cpick->replace = sdl_pixel_pick_from_img(sdl, px.x, px.y);
}

void			cpick_set_transparency(t_color_pick *cpick, t_u32 color)
{
	cpick->use_transparency = True;
	cpick->ignore_c.rgba = color;
}

void			cpick_unset_transparency(t_color_pick *cpick)
{
	cpick->use_transparency = False;
}
