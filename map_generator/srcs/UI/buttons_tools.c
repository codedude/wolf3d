/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:27:34 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 21:49:26 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "types.h"
#include "sdl_plus.h"
#include "ui.h"
#include "sdl_m.h"

void			button_switch(t_button **b_list, t_u32 b_count, t_u32 active_id)
{
	t_u32		i;

	i = 0;
	while (i < b_count)
	{
		button_setactive(b_list[i], (i == active_id));
		i++;
	}
}

t_bool			button_hover(t_button *button, t_ivec2 pos)
{
	return (is_bounded(pos, button->anchor));
}

void			button_setactive(t_button *button, t_bool active)
{
	if (button->is_active == active)
		return ;
	button->is_active = active;
	if (active == True)
		button->trigger(button->param);
}

void			button_trigger(t_button *button)
{
	button->trigger(button->param);
}

void			button_draw(t_sdl *sdl, t_color_pick *cpick, t_button *button)
{
	if (button->is_active == False)
	{
		cpick_set_color_mask(cpick, 0x0, 0.75);
		draw_tex_color(sdl, cpick, button->tex, button->anchor);
		cpick_unset_color_mask(cpick);
	}
	else
		draw_tex_color(sdl, cpick, button->tex, button->anchor);
}
