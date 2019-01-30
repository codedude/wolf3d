/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:58:01 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:16:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void			init_xy(t_sdl *sdl, int xy[3])
{
	xy[0] = ipercent_of(sdl->width, MPROPS_B_P_X);
	xy[1] = ipercent_of(sdl->width, MPROPS_B_P_RX);
	xy[2] = ipercent_of(sdl->width, MPROPS_B_P_LX);
	xy[3] = ipercent_of(sdl->height, MPROPS_B_P_Y);
	xy[4] = ipercent_of(sdl->height, MPROPS_B_OFF_Y);
}

static void			init_trigger_and_tex_id(
						void (*trigger[Max_editor_action])(void*),
						int tex_id[Max_editor_action])
{
	trigger[Scale_increase] = mprops_act_scale_up;
	trigger[Size_X_increase] = mprops_act_size_x_up;
	trigger[Size_Y_increase] = mprops_act_size_y_up;
	trigger[Scale_decrease] = mprops_act_scale_down;
	trigger[Size_X_decrease] = mprops_act_size_x_down;
	trigger[Size_Y_decrease] = mprops_act_size_y_down;
	trigger[Recenter] = mprops_act_recenter;
	tex_id[Scale_increase] = UI_MProps_Zoom_In;
	tex_id[Size_X_increase] = UI_MProps_SX_INC;
	tex_id[Size_Y_increase] = UI_MProps_SY_INC;
	tex_id[Scale_decrease] = UI_MProps_Zoom_Out;
	tex_id[Size_X_decrease] = UI_MProps_SX_DEC;
	tex_id[Size_Y_decrease] = UI_MProps_SY_DEC;
	tex_id[Recenter] = UI_MProps_Recenter;
}

static int			mprop_create_buttons(t_mprops *prop, t_env *env)
{
	t_canvas	anchor;
	void		(*trigger[Max_editor_action])(void*);
	int			tex_id[Max_editor_action];
	int			xy[5];
	t_u32		i;

	i = 0;
	anchor.size.x = ipercent_of(env->sdl.width, MPROPS_B_SZ_X);
	anchor.size.y = ipercent_of(env->sdl.height, MPROPS_B_SZ_Y);
	init_xy(&env->sdl, xy);
	init_trigger_and_tex_id(trigger, tex_id);
	while (i < Max_editor_action)
	{
		anchor.pos = IVEC2_INIT(xy[i % 3], xy[3] + xy[4] * ((int)i / 3));
		prop->actions[i] = button_new(anchor, &env->ui_tex[tex_id[i]],
								env, trigger[i]);
		if (prop->actions[i] == NULL)
			return (ERROR);
		prop->actions[i]->is_active = True;
		i++;
	}
	return (SUCCESS);
}

int					env_create_mprops(t_env *env)
{
	t_mprops	*prop;
	t_canvas	anchor;

	prop = &env->map_properties;
	anchor.size.x = ipercent_of(env->sdl.width, MPROPS_SZ_X);
	anchor.size.y = ipercent_of(env->sdl.height, MPROPS_SZ_Y);
	anchor.pos.y = ipercent_of(env->sdl.height, MPROPS_TOP_P_Y);
	anchor.pos.x = ipercent_of(env->sdl.width, MPROPS_TOP_P_X);
	prop->anchor = anchor;
	if (mprop_create_buttons(prop, env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
