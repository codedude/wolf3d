/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:19:33 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 03:35:05 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gen_env.h"
#include "objects_edit.h"
#include "ui.h"

int				get_obj_at_mpos(t_env *env)
{
	t_ivec2		mpos;
	t_canvas	anch;
	t_u32		i;

	mpos = env->mouse.pos;
	anch.size = env->map_info.x_draw[1] - env->map_info.x_draw[0];
	i = 0;
	while (i < env->obj.count)
	{
		anch.pos = map_coord_to_screen(env, env->obj.list[i]->pos);
		anch.pos -= anch.size / 2;
		if (is_bounded(env->mouse.pos, anch))
		{
			env->mouse.obj_offset = env->obj.list[i]->pos
			- mpos_to_map_coord(get_map_boundaries(env), env->mouse.pos, env);
			return ((int)i);
		}
		i++;
	}
	return (-1);
}

static int		init_grid_snap(t_objects_tools *otools, t_sdl *sdl, t_env *env)
{
	t_ivec2		pos;
	t_ivec2		size[2];


	pos.x = ipercent_of(sdl->width, G_SNAP_P_X);
	pos.y = ipercent_of(sdl->height, G_SNAP_P_Y);
	size[0].x = ipercent_of(sdl->width, G_SNAP_S_SZ_X);
	size[0].y = ipercent_of(sdl->height, G_SNAP_S_SZ_Y);
	size[1].x = ipercent_of(sdl->width, G_SNAP_C_SZ_X);
	size[1].y = ipercent_of(sdl->height, G_SNAP_C_SZ_Y);
	if (!(otools->g_snap = slider_new(pos,
			(t_tex*[2]){NULL, &env->ui_tex[UI_Objects_SlideCurs]}, size)))
		return (ERROR);
	slider_setup(otools->g_snap, Dir_Horizontal, VEC2_INIT(0.0, 1.0), 10.0);
	otools->g_snap->draw_bar = False;
	return (SUCCESS);
}

int				init_objects_tools(t_objects_tools *otools, t_sdl *sdl,
								t_env *env)
{
	if (env->loaded == False)
		otools->count = 0;
	otools->edit.selected = -1;
	if (init_grid_snap(otools, sdl, env) == ERROR
	|| init_cbox_solid(otools, sdl, env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void			object_tools_destroy(t_objects_tools *otools)
{
	t_u32		i;

	i = 0;
	while (i < otools->count)
	{
		free(otools->list[i]);
		i++;
	}
	slider_destroy(&otools->g_snap);
	checkbox_destroy(&otools->cbox_solid);
}
