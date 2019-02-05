/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_ui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/02/05 13:16:18 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static void			draw_mprops(t_env *env, t_mprops *props)
{
	t_canvas	anch;

	anch.pos = props->anchor.pos - 1;
	anch.size = props->anchor.size + 2;
	draw_tex(&env->sdl, &env->cpick, &env->ui_tex[UI_MProps_BG], anch);
	if (env->mouse.b1 == True && env->mouse.area == Map_properties_buttons)
		button_draw(&env->sdl, &env->cpick,
			props->actions[env->mouse.button_index]);
}

static void			draw_editor(t_env *env)
{
	t_editor	*ed;

	ed = &env->editor;
	draw_tex(&env->sdl, &env->cpick, &env->ui_tex[UI_EMode_BG], ed->anchor);
	button_draw(&env->sdl, &env->cpick, ed->switch_b[ed->mode]);
}

static void			draw_cursor(t_env *env)
{
	t_canvas	anch;

	if (env->mouse.b1 != Mouse_Press || env->mouse.area != Right_Panel
	|| env->editor.mode != Object_Edit
	|| env->mouse.button_index > (t_u32)env->sdl.tex_sprite_nb)
		return ;
	anch.size = env->rpan.p[Object_Panel]->elem_anchor.size;
	anch.size = IVEC2_INIT((int)(anch.size.x * 0.8), (int)(anch.size.y * 0.8));
	anch.pos = env->mouse.pos - anch.size / 2;
	draw_tex(&env->sdl, &env->cpick,
		&env->sdl.tex_sprites[env->mouse.button_index], anch);

}

void				draw_ui(t_env *env, t_sdl *sdl)
{
	panel_draw(sdl, &env->cpick, env->rpan.p[env->rpan.type]);
	button_draw(sdl, &env->cpick, env->inspector.action[env->editor.mode]);
	env->inspector.draw[env->editor.mode](env);
	draw_mprops(env, &env->map_properties);
	draw_editor(env);
	draw_cursor(env);
}
