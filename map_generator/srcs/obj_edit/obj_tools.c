/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:19:33 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:25:36 by jbulant          ###   ########.fr       */
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
	anch.size = env->obj.mb_size;
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

static int		create_map_boxes(t_sdl *sdl, t_objects_tools *otools, t_u32 cnt)
{
	int			size;
	t_u32		i;

	otools->map_boxes = (t_color**)ft_memalloc(sizeof(t_color*) * cnt);
	if (!otools->map_boxes)
		return (ERROR);
	if (sdl->width < sdl->height)
		size = ipercent_of(sdl->width, MAP_BOXES_SZ);
	else
		size = ipercent_of(sdl->height, MAP_BOXES_SZ);
	i = 0;
	while (i < cnt)
	{
		otools->map_boxes[i] = new_texdata(&sdl->tex_sprites[i], size);
		if (!otools->map_boxes[i])
			return (ERROR);
		i++;
	}
	otools->mb_size = size;
	return (SUCCESS);
}

static int		init_grid_snap(t_objects_tools *otools, t_sdl *sdl)
{
	t_ivec2		pos;
	t_ivec2		size[2];


	pos.x = ipercent_of(sdl->width, G_SNAP_P_X);
	pos.y = ipercent_of(sdl->height, G_SNAP_P_Y);
	size[0].x = ipercent_of(sdl->width, G_SNAP_S_SZ_X);
	size[0].y = ipercent_of(sdl->height, G_SNAP_S_SZ_Y);
	size[1].x = ipercent_of(sdl->width, G_SNAP_C_SZ_X);
	size[1].y = ipercent_of(sdl->height, G_SNAP_C_SZ_Y);
	if (!(otools->g_snap = slider_new(pos, (t_tex*[2]){NULL, NULL}, size)))
		return (ERROR);
	slider_setup(otools->g_snap, Dir_Horizontal, VEC2_INIT(0.0, 1.0), 10.0);
	return (SUCCESS);
}

int				init_objects_tools(t_objects_tools *otools, t_sdl *sdl,
								t_env *env)
{
	if (env->loaded == False)
		otools->count = 0;
	otools->edit.selected = -1;
	if (create_map_boxes(sdl, otools, (t_u32)sdl->tex_sprite_nb) == ERROR
	|| init_grid_snap(otools, sdl) == ERROR
	|| init_cbox_solid(otools, sdl) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

void			object_tools_destroy(t_objects_tools *otools, t_panel *o_pan)
{
	t_u32		i;

	if (otools->map_boxes)
	{
		i = 0;
		while (i < (t_u32)o_pan->nb_elem)
		{
			free(otools->map_boxes[i]);
			i++;
		}
		free(otools->map_boxes);
	}
	i = 0;
	while (i < otools->count)
	{
		free(otools->list[i]);
		i++;
	}
	slider_destroy(&otools->g_snap);
	checkbox_destroy(&otools->cbox_solid);
}
