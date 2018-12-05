/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/05 17:36:29 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static void			init_grid(t_env *env, t_sdl *sdl)
{
	env->grid.size.x = ipercent_of(sdl->width, GRID_PERC_X - (GRID_OFF_X * 2));
	env->grid.size.y = ipercent_of(sdl->height, 100 - (GRID_OFF_Y * 2));
	env->grid.pos.x = ipercent_of(sdl->width, GRID_OFF_X);
	env->grid.pos.y = ipercent_of(sdl->height, GRID_OFF_Y);
	if (env->grid.pos.y < env->grid.pos.x)
		env->node_size = env->grid.pos.y;
	else
		env->node_size = env->grid.pos.x;
	env->zoom = 1.0;
	env->map_pos = map_to_center(env);
	env->space = 0;
	env->alt = 0;
	env->mouse2 = 0;
}

static void			init_brush(t_env *env, t_sdl *sdl)
{
	int			y;
	t_tex_pbox	*box;

	if (sdl->width < sdl->height)
		env->brush_prev.size = ipercent_of(sdl->width, BRUSH_C_SIZE);
	else
		env->brush_prev.size = ipercent_of(sdl->height, BRUSH_C_SIZE);
	env->brush_prev.pos.x = env->brush_box->canvas.pos.x;
	env->brush_prev.pos.y = env->brush_canvas.pos.y + env->brush_canvas.size.y;
	env->brush_prev.pos.y += env->brush_prev.size.y / 2;
	box =  env->brush_box;
	y = env->brush_box->canvas.pos.y;
	while ((box = box->next))
	{
		if (box->canvas.pos.y < y)
			y = box->canvas.pos.y;
	}
	env->max_bcoffset = (env->brush_box->canvas.pos.y - y)
				- env->brush_canvas.size.y
				+ (int)(env->brush_box->canvas.size.y * 1.5);
}

static t_tex_pbox	*create_brush_boxes(t_sdl *sdl)
{
	t_tex_pbox	*box;
	t_tex_pbox	*new;
	int			i;
	int			pos_y;

	i = 0;
	box = NULL;
	pos_y = ipercent_of(sdl->height, GRID_OFF_Y * 2);
	while (i < sdl->textures_nb)
	{
		if ((new = new_tex_previewbox(sdl, sdl->textures + i, i)))
		{
			tex_previewbox_add(&box, new);
			new->canvas.pos.x = ipercent_of(sdl->width,
									100 - (100 - GRID_PERC_X) / 2);
			new->canvas.pos.y = pos_y + (int)(box->canvas.size.y * 1.5) * i;
			new->canvas.pos.x -= box->canvas.size.x;
		}
		i++;
	}
	return (box);
}

static int			env_init2(t_env *env)
{
	init_grid(env, &env->sdl);
	env->brush = 0;
	env->brush_canvas.size.x = ipercent_of(env->sdl.width, BRUSH_PAN_SIZE_X);
	env->brush_canvas.size.y = ipercent_of(env->sdl.height, BRUSH_PAN_SIZE_Y);
	env->brush_canvas.pos.x = ipercent_of(env->sdl.width, BRUSH_PAN_OFF_X);
	env->brush_canvas.pos.y = ipercent_of(env->sdl.height, BRUSH_PAN_OFF_Y);
	init_brush(env, &env->sdl);
	env->mouse1 = 0;
	env->space = 0;
	env->brush_c_offset = 0;
	env->spawner_id = env->brush_box->tex_id + 1;
	return (SUCCESS);
}
int					env_init(t_env *env)
{
	if (sdl_init(&env->sdl, MAP_GEN_NAME, 1280, 720) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if (sdl_init_textures(&env->sdl) == ERROR)
	{
		ft_putstr_fd("Can't load textures\n", 2);
		return (ERROR);
	}
	if (!(env->map = create_new_map(IVEC2_INIT(DEF_SIZE_X, DEF_SIZE_Y)))
	|| !(env->brush_box = create_brush_boxes(&env->sdl)))
	{
		perror("Wolf3d: ");
		return (ERROR);
	}
	return (env_init2(env));
}
