/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/20 15:51:38 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

void			draw_line(t_sdl *sdl, t_ivec2 v1, t_ivec2 v2, t_u32 c)
{
	t_ivec2 orientation;
	t_ivec2 direction;
	t_ivec2 error;

	direction = IVEC2_INIT(abs(v1.x - v2.x), abs(v1.y - v2.y));
	orientation = IVEC2_INIT(((v1.x < v2.x) ? 1 : -1), ((v1.y < v2.y) ? 1 : -1));
	error.x = ((direction.x > direction.y) ? direction.x : -direction.y) / 2;
	while (!(v1.x == v2.x && v1.y == v2.y))
	{
		sdl_put_pixel_safe(sdl, v1, (t_color)c);
		error.y = error.x;
		if (error.y > -direction.x)
		{
			error.x -= direction.y;
			v1.x += orientation.x;
		}
		if (error.y < direction.y)
		{
			error.x += direction.x;
			v1.y += orientation.y;
		}
	}
}

static void			draw_ui(t_env *env, t_sdl *sdl)
{
	t_u32		i;

	panel_draw(sdl, env->obj_pan);
	panel_draw(sdl, env->brush_pan);
	i = 0;
	while (i < Max_action)
	{
		button_draw(sdl, env->act_buttons[i]);
		i++;
	}
}

void				draw_grid(t_env *env, t_sdl *sdl)
{
	sdl_clear_color(sdl, 0x101010);
	draw_canvas_fill(sdl, env->grid, CANVAS_INIT(0, 0), 0x252525);
	draw_grid_lines(env, sdl);
	draw_ui(env, sdl);
}
