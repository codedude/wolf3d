/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox_is_solid.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 01:17:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 03:32:47 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "sdl_m.h"
#include "ui.h"
#include "objects_edit.h"
#include "libft.h"

static int		gstate_obj_solid(void *v_otools)
{
	t_objects_tools 	*otools;

	otools = (t_objects_tools*)v_otools;
	if (otools->edit.selected == -1)
		return (Unavailable);
	return ((int)otools->list[otools->edit.selected]->is_solid);
}

static void		rstate_obj_solid(void *v_otools)
{
	t_objects_tools		*otools;
	t_object_e			*o;

	otools = (t_objects_tools*)v_otools;
	if (otools->edit.selected == -1)
		return ;
	o = otools->list[otools->edit.selected];
	o->is_solid = !o->is_solid;
}

int				init_cbox_solid(t_objects_tools *otools, t_sdl *sdl, t_env *env)
{
	t_canvas	anchor;

	anchor.pos.x = ipercent_of(sdl->width, CB_SOL_P_X);
	anchor.pos.y = ipercent_of(sdl->height, CB_SOL_P_Y);
	if (sdl->width < sdl->height)
		anchor.size = ipercent_of(sdl->width, CB_SOL_S_SZ);
	else
		anchor.size = ipercent_of(sdl->height, CB_SOL_S_SZ);
	if (!(otools->cbox_solid = checkbox_new(anchor, &env->ui_tex[UI_CheckBox])))
		return (ERROR);
	checkbox_setup(otools->cbox_solid, otools,
		rstate_obj_solid, gstate_obj_solid);
	return (SUCCESS);
}
