/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_switch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:54:46 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 03:03:11 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "editor.h"
#include "ui.h"
#include "gen_env.h"

static void		sw_painter(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_switch(env->editor.switch_b, Max_EditMod_type, Painter);
	env->rpan.type = Texture_Panel;
	env->editor.mode = Painter;
	toolset_set_type(&env->toolset, Pencil);
}

static void		sw_world(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_switch(env->editor.switch_b, Max_EditMod_type, World);
	env->rpan.type = Texture_Panel;
	env->editor.mode = World;
	toolset_set_type(&env->toolset, SpawnSetter);
}

static void		sw_door(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_switch(env->editor.switch_b, Max_EditMod_type, Door);
	env->rpan.type = Texture_Panel;
	env->editor.mode = Door;
}

static void		sw_object(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_switch(env->editor.switch_b, Max_EditMod_type, Object_Edit);
	env->rpan.type = Object_Panel;
	env->editor.mode = Object_Edit;
}

int				init_editor_switch(t_env *env, t_sdl *sdl, t_editor *editor)
{
	t_ivec2		pos[2];
	t_canvas	anchor;

	anchor.size.x = ipercent_of(sdl->width, EM_B_SZ_X);
	anchor.size.y = ipercent_of(sdl->height, EM_B_SZ_Y);
	pos[0].x = ipercent_of(sdl->width, EM_B_P_X);
	pos[0].y = ipercent_of(sdl->height, EM_B_P_Y);
	pos[1].x = ipercent_of(sdl->width, EM_B_POS2_X);
	pos[1].y = ipercent_of(sdl->height, EM_B_POS2_Y);
	anchor.pos = pos[0];
	editor->switch_b[Painter] = button_new(anchor,
							&env->ui_tex[UI_EMode_Painter], env, sw_painter);
	anchor.pos.x = pos[1].x;
	editor->switch_b[World] = button_new(anchor,
							&env->ui_tex[UI_EMode_World], env, sw_world);
	anchor.pos = IVEC2_INIT(pos[0].x, pos[1].y);
	editor->switch_b[Door] = button_new(anchor,
							&env->ui_tex[UI_EMode_Doors], env, sw_door);
	anchor.pos = pos[1];
	editor->switch_b[Object_Edit] = button_new(anchor,
							&env->ui_tex[UI_EMode_Objects], env, sw_object);
	return (SUCCESS);
}
