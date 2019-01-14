/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 01:22:45 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/14 04:44:23 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static int		create_map_boxes(t_panel *p, t_objects_tools *otools, t_sdl *sdl)
{
	int			size;
	t_u32		i;

	otools->map_boxes = (t_color**)ft_memalloc(sizeof(t_color*) * p->nb_elem);
	if (!otools->map_boxes)
		return (ERROR);
	if (sdl->width < sdl->height)
		size = ipercent_of(sdl->width, MAP_BOXES_SIZE);
	else
		size = ipercent_of(sdl->height, MAP_BOXES_SIZE);
	i = 0;
	while (i < p->nb_elem)
	{
		otools->map_boxes[i] = new_texdata(&sdl->sprites[i].texture, size);
		if (!otools->map_boxes[i])
			return (ERROR);
		i++;
	}
	otools->mb_size = size;
	return (SUCCESS);
}

void			add_new_object(t_objects_tools *otools, t_vec2 pos,
						t_bool is_solid, t_u32 id)
{
	t_object	*obj;

	if (otools->count == MAX_OBJECTS)
		return ;
	obj = (t_object*)malloc(sizeof(t_object));
	if (!obj)
		return ;
	obj->pos = pos;
	obj->is_solid = is_solid;
	obj->id = id;
	obj->y_pos = 0.0;
	otools->list[otools->count++] = obj;
}

void			object_destroy(t_objects_tools *otools, t_u32 obj_i)
{
	if (obj_i >= otools->count)
		return ;
	free(otools->list[obj_i]);
	if (otools->count > 1)
		otools->list[obj_i] = otools->list[otools->count - 1];
	if ((int)obj_i == otools->edit.selected)
		otools->edit.selected = -1;
	otools->count--;
}

int				init_grid_snap(t_objects_tools *otools, t_sdl *sdl)
{
	t_ivec2		pos;
	t_ivec2		size[2];


	pos.x = ipercent_of(sdl->width, G_SNAP_POS_X);
	pos.y = ipercent_of(sdl->height, G_SNAP_POS_Y);
	size[0].x = ipercent_of(sdl->width, G_SNAP_S_SIZE_X);
	size[0].y = ipercent_of(sdl->height, G_SNAP_S_SIZE_Y);
	size[1].x = ipercent_of(sdl->width, G_SNAP_C_SIZE_X);
	size[1].y = ipercent_of(sdl->height, G_SNAP_C_SIZE_Y);
	if (!(otools->g_snap = slider_new(pos, (t_texture*[2]){NULL, NULL}, size)))
		return (ERROR);
	slider_setup(otools->g_snap, Dir_Horizontal, VEC2_INIT(0.0, 1.0), 10.0);
	return (SUCCESS);
}

int			gstate_obj_solid(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	if (env->obj.edit.selected == -1)
		return (Unavailable);
	return ((int)env->obj.list[env->obj.edit.selected]->is_solid);
}

void		rstate_obj_solid(void *v_env)
{
	t_env 		*env;
	t_object	*o;

	env = (t_env*)v_env;
	if (env->obj.edit.selected == -1)
		return ;
	o = env->obj.list[env->obj.edit.selected];
	o->is_solid = !o->is_solid;
}

int				init_cbox_solid(t_objects_tools *otools, t_sdl *sdl, t_env *env)
{
	t_canvas	anchor;

	anchor.pos.x = ipercent_of(sdl->width, CB_SOL_POS_X);
	anchor.pos.y = ipercent_of(sdl->height, CB_SOL_POS_Y);
	if (sdl->width < sdl->height)
		anchor.size = ipercent_of(sdl->width, CB_SOL_S_SIZE);
	else
		anchor.size = ipercent_of(sdl->height, CB_SOL_S_SIZE);
	if (!(otools->cbox_solid = checkbox_new(anchor, NULL)))
		return (ERROR);
	checkbox_setup(otools->cbox_solid, env, rstate_obj_solid, gstate_obj_solid);
	return (SUCCESS);
}

int			gstate_obj_collect(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	if (env->obj.edit.selected == -1)
		return (Unavailable);
	return ((int)env->obj.list[env->obj.edit.selected]->collectible);
}

void		rstate_obj_collect(void *v_env)
{
	t_env 		*env;
	t_object	*o;

	env = (t_env*)v_env;
	if (env->obj.edit.selected == -1)
		return ;
	o = env->obj.list[env->obj.edit.selected];
	o->collectible = !o->collectible;
}

int			init_cbox_collect(t_objects_tools *otools, t_env *env)
{
	t_canvas	anchor;

	anchor = otools->cbox_solid->anchor;
	anchor.pos.y -= (int)(anchor.size.y * 1.5);
	if (!(otools->cbox_collect = checkbox_new(anchor, NULL)))
		return (ERROR);
	checkbox_setup(otools->cbox_collect, env,
			rstate_obj_collect, gstate_obj_collect);
	return (SUCCESS);
}

int				init_objects_tools(t_objects_tools *otools, t_sdl *sdl,
								t_env *env)
{
	otools->count = 0;
	otools->edit.selected = -1;
	if (create_map_boxes(env->rpan.p[Object_Panel], otools, sdl) == ERROR
	|| init_grid_snap(otools, sdl) == ERROR
	|| init_cbox_solid(otools, sdl, env) == ERROR
	|| init_cbox_collect(otools, env) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
