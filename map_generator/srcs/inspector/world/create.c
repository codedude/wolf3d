/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:55:36 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 22:53:04 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void		init_cf_prev(t_env *env, t_world_i *w_inf, t_canvas i_anch)
{
	t_canvas	anchor;
	int			offset;
	t_button	*b;

	b = env->inspector.action[World];
	anchor.size = env->rpan.p[Texture_Panel]->elem_anchor.size;
	offset = (int)((t_float)anchor.size.x * 0.1);
	anchor.pos.y = w_inf->radar.center.y + (int)(w_inf->radar.f_radius * 1.6);
	anchor.pos.x = w_inf->radar.center.x - (anchor.size.x + offset);
	w_inf->prev[WButton_Floor] = anchor;
	anchor.pos.x = w_inf->radar.center.x + offset;
	w_inf->prev[WButton_Ceil] = anchor;
	anchor.pos -= i_anch.pos;
	texdata_fill_rect(b->tex, i_anch.size, anchor, 0x757575);
	anchor.pos.x = (w_inf->radar.center.x - (anchor.size.x + offset))
			- i_anch.pos.x;
	texdata_fill_rect(b->tex, i_anch.size, anchor, 0x757575);
}

static int		gstate_draw_ceil(void *v_env)
{
	t_env		*env;

	env = (t_env*)v_env;
	return ((int)env->inspector.world.draw_ceil);
}

static void		rstate_draw_ceil(void *v_env)
{
	t_env 		*env;
	t_world_i	*w_inf;

	env = (t_env*)v_env;
	w_inf = &env->inspector.world;
	w_inf->draw_ceil = !w_inf->draw_ceil;
}

static int		init_cbox_draw_ceil(t_env *env, t_sdl *sdl,
					t_world_i *w_inf, t_canvas i_anch)
{
	t_canvas	anchor;

	if (sdl->width < sdl->height)
		anchor.size = ipercent_of(sdl->width, CB_SOL_S_SZ);
	else
		anchor.size = ipercent_of(sdl->height, CB_SOL_S_SZ);
	anchor.pos.x = i_anch.pos.x + i_anch.size.x;
	anchor.pos.x -= (int)(anchor.size.x * 1.5);
	anchor.pos.y = w_inf->prev[WButton_Ceil].pos.y
				+ w_inf->prev[WButton_Ceil].size.y;
	anchor.pos.y += (int)(anchor.size.y * 1.0);
	if (!(w_inf->cbox_ceil = checkbox_new(anchor, NULL)))
		return (ERROR);
	checkbox_setup(w_inf->cbox_ceil, env, rstate_draw_ceil, gstate_draw_ceil);
	return (SUCCESS);
}

int				create_world_inpector(t_env *env, t_canvas i_anch)
{
	t_world_i	*w_inf;
	t_button	*b;

	w_inf = &env->inspector.world;
	if (!(b = button_new(i_anch, NULL, env, inspector_action_world)))
		return (ERROR);
	env->inspector.action[World] = b;
	env->inspector.draw[World] = inspector_draw_world;
	env->inspector.get_button[World] = inspector_gb_world;
	init_radar(env, &w_inf->radar, i_anch);
	init_cf_prev(env, w_inf, i_anch);
	init_cbox_draw_ceil(env, &env->sdl, w_inf, i_anch);
	if (env->loaded == False)
	{
		w_inf->id[WButton_Ceil] = 0;
		w_inf->id[WButton_Floor] = 0;
		env->inspector.world.draw_ceil = False;
	}
	return (SUCCESS);
}
