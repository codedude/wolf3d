/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editmod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:54:46 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/11 04:13:04 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"

static void		button_switch(t_button **b_list, t_u32 b_count, t_u32 active_id)
{
	t_u32		i;

	i = 0;
	while (i < b_count)
	{
		button_setactive(b_list[i], (i == active_id));
		i++;
	}
}

static void		sw_painter(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_switch(env->editmod.switch_b, Max_EditMod_type, Painter);
	env->inspector.mod = Brush_Select;
	env->rpan.type = Texture_Panel;
	env->editmod.type = Painter;
}

static void		sw_world(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_switch(env->editmod.switch_b, Max_EditMod_type, World);
	env->inspector.mod = Player_Radar;
	env->rpan.type = Texture_Panel;
	env->editmod.type = World;
}

static void		sw_door(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_switch(env->editmod.switch_b, Max_EditMod_type, Door);
	env->inspector.mod = Brush_Select;
	env->rpan.type = Texture_Panel;
	env->editmod.type = Door;
}

static void		sw_object(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_switch(env->editmod.switch_b, Max_EditMod_type, Object);
	env->inspector.mod = Object_Edit;
	env->rpan.type = Object_Panel;
	env->editmod.type = Object;
}

int				init_editmod_switch(t_env *env, t_sdl *sdl, t_editmod *editmod)
{
	t_ivec2		pos[2];
	t_canvas	anchor;

	anchor.size.x = ipercent_of(sdl->width, EM_B_SIZE_X);
	anchor.size.y = ipercent_of(sdl->height, EM_B_SIZE_Y);
	pos[0].x = ipercent_of(sdl->width, EM_B_POS_X);
	pos[0].y = ipercent_of(sdl->height, EM_B_POS_Y);
	pos[1].x = ipercent_of(sdl->width, EM_B_POS2_X);
	pos[1].y = ipercent_of(sdl->height, EM_B_POS2_Y);
	anchor.pos = pos[0];
	editmod->switch_b[Painter] = button_new(anchor, NULL, env, sw_painter);
	anchor.pos.x = pos[1].x;
	editmod->switch_b[World] = button_new(anchor, NULL, env, sw_world);
	anchor.pos = IVEC2_INIT(pos[0].x, pos[1].y);
	editmod->switch_b[Door] = button_new(anchor, NULL, env, sw_door);
	anchor.pos = pos[1];
	editmod->switch_b[Object] = button_new(anchor, NULL, env, sw_object);
	return (SUCCESS);
}

int				init_editmod(t_env *env, t_sdl *sdl, t_editmod *editmod)
{
	t_canvas	anchor;

	anchor.size.x = ipercent_of(sdl->width, EDITMOD_SIZE_X);
	anchor.size.y = ipercent_of(sdl->height, EDITMOD_SIZE_Y);
	anchor.pos.x = ipercent_of(sdl->width, EDITMOD_POS_X);
	anchor.pos.y = ipercent_of(sdl->height, EDITMOD_POS_Y);
	editmod->anchor = anchor;
	editmod->type = Painter;
	return (init_editmod_switch(env, sdl, editmod));
}
