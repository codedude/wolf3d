/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:55:36 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/28 14:49:50 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void			inspector_draw_world(t_env *env)
{
	t_world_i	*w_inf;
	t_u32		id;

	w_inf = &env->inspector.world;
	draw_radar(env, &w_inf->radar);
	checkbox_draw(&env->sdl, &env->cpick, w_inf->cbox_ceil);
	id = w_inf->id[WButton_Floor];
	draw_tex(&env->sdl, &env->cpick,
		&env->sdl.tex_walls[id], w_inf->prev[WButton_Floor]);
	id = w_inf->id[WButton_Ceil];
	if (w_inf->draw_ceil == False)
	{
		cpick_set_color_mask(&env->cpick, 0x0, 0.75);
		draw_tex(&env->sdl, &env->cpick,
			&env->sdl.tex_walls[id], w_inf->prev[WButton_Ceil]);
		cpick_unset_color_mask(&env->cpick);
	}
	else
		draw_tex(&env->sdl, &env->cpick,
			&env->sdl.tex_walls[id], w_inf->prev[WButton_Ceil]);
}

static void		action_player_radar(t_env *env, t_radar *radar)
{
	t_ivec2		mpos;
	t_button	*b;

	b = env->inspector.action[World];
	mpos = env->mouse.pos - radar->center;
	env->spawn_rotation = (int)(atan2(mpos.y, mpos.x) * 180.0 / MY_PI) + 180;
}

void			inspector_action_world(void *v_env)
{
	t_env		*env;
	t_world_i	*w_inf;
	t_u32		b_index;

	env = (t_env*)v_env;
	w_inf = &env->inspector.world;
	b_index = env->mouse.button_index;
	if (b_index == WButton_Radar)
		action_player_radar(env, &w_inf->radar);
	else if (env->mouse.b1_status == Mouse_Release)
	{
		if (b_index == WButton_Ceil && w_inf->draw_ceil)
			w_inf->id[WButton_Ceil] = env->rpan.p[Texture_Panel]->cursor;
		else if (b_index == WButton_Floor)
			w_inf->id[WButton_Floor] = env->rpan.p[Texture_Panel]->cursor;
		else if (b_index == WButton_Draw_Ceil)
			checkbox_clic(w_inf->cbox_ceil);
	}
}

static t_bool	gb_player_radar(t_env *env, t_radar *radar)
{
	t_ivec2		rpos;

	rpos = env->mouse.record_pos_b - radar->center;
	return (rpos.x * rpos.x + rpos.y * rpos.y < radar->squ_radius);
}

t_bool			inspector_gb_world(t_env *env)
{
	t_world_i	*w_inf;
	int			button;

	w_inf = &env->inspector.world;
	button = -1;
	if (is_bounded(env->mouse.pos, w_inf->prev[WButton_Ceil]))
		button = WButton_Ceil;
	else if (is_bounded(env->mouse.pos, w_inf->prev[WButton_Floor]))
		button = WButton_Floor;
	else if (gb_player_radar(env, &w_inf->radar) == True)
		button = WButton_Radar;
	else if (checkbox_hover(w_inf->cbox_ceil, env->mouse.pos))
		button = WButton_Draw_Ceil;
	else
		return (False);
	env->mouse.button_index = (t_u32)button;
	return (True);
}
