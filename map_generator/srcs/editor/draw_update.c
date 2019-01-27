/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_update.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 21:36:41 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static void			draw_obj_prev_on_mouse(t_env *env)
{
	t_canvas		anchor;
	t_panel			*p;

	p = env->rpan.p[Object_Panel];
	anchor.size = env->obj.mb_size;
	anchor.pos = env->mouse.pos - anchor.size / 2;
	draw_tex(&env->sdl, &env->cpick,
		&env->sdl.tex_sprites[env->mouse.button_index], anchor);
}

void				draw_update(t_env *env, t_sdl *sdl)
{
	t_canvas		c;

	c.size = IVEC2_ZERO;
	c.pos = IVEC2_ZERO;
	sdl_clear_color(sdl, 0x101010);
	draw_canvas_fill(sdl, &env->grid, &c, 0x252525);
	draw_map(env, sdl);
	draw_ui(env, sdl);
	if (env->editor.mode == Object_Edit && env->mouse.area == Right_Panel
		&& env->mouse.b1 == True)
		draw_obj_prev_on_mouse(env);
}
