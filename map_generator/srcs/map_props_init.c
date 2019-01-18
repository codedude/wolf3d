/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_props_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:58:01 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/17 19:29:04 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void				mprops_act_scale_up(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;
	t_float		factor;

	env = (t_env*)v_env;
	minf = &env->map_info;
	factor = 1.0 + (env->map_properties.tick / 60.0 * 0.05);
	if (factor != 0.0)
		minf->zoom *= factor;
	if (minf->zoom > minf->zoom_max)
		minf->zoom = minf->zoom_max;
}

void				mprops_act_size_x_up(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;

	env = (t_env*)v_env;
	minf = &env->map_info;
	if (minf->map->size.x < MAX_SIZE_X)
	{
		minf->map->size.x++;
		map_update_center(env);
	}
}

void				mprops_act_size_y_up(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;

	env = (t_env*)v_env;
	minf = &env->map_info;
	if (minf->map->size.y < MAX_SIZE_Y)
	{
		minf->map->size.y++;
		map_update_center(env);
	}
}

void				mprops_act_scale_down(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;
	t_float		factor;

	env = (t_env*)v_env;
	minf = &env->map_info;
	factor = 1.0 + (env->map_properties.tick / 60.0 * 0.05);
	if (factor != 0.0)
		minf->zoom /= factor;
	if (minf->zoom < minf->zoom_min)
		minf->zoom = minf->zoom_min;
}

void				mprops_act_size_x_down(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;

	env = (t_env*)v_env;
	minf = &env->map_info;
	if (minf->map->size.x > MIN_SIZE_X)
	{
		minf->map->size.x--;
		map_update_center(env);
	}
}

void				mprops_act_size_y_down(void *v_env)
{
	t_env		*env;
	t_map_info	*minf;

	env = (t_env*)v_env;
	minf = &env->map_info;
	if (minf->map->size.y > MIN_SIZE_Y)
	{
		minf->map->size.y--;
		map_update_center(env);
	}
}

static void			mprops_act_recenter(void *v_env)
{
	t_env		*env;

	env = (t_env*)v_env;
	env->map_info.pos = 0;
	map_scale2grid(env);
}

void				TMP_color_props(t_env *env)
{
	# define PURPLE_C	0x8524cc
	# define BLUE_C		0x5050cc
	# define GREEN_C	0x50cc50
	# define RED_C		0xcc5050
	static t_u32		col[Max_editor_action] = {PURPLE_C, GREEN_C, GREEN_C,
												  BLUE_C, PURPLE_C, PURPLE_C,
												 		    PURPLE_C};
	t_ivec2				px;
	t_button			*b;
	int					i;

	i = 0;
	while (i < Max_editor_action)
	{
		b = env->map_properties.actions[i];
		px.y = 0;
		while (px.y < b->anchor.size.y)
		{
			px.x = 0;
			while (px.x < b->anchor.size.x)
			{
				b->tex[px.x + px.y * b->anchor.size.x].rgba = col[i];
				px.x++;
			}
			px.y++;
		}
		i++;
	}
}

static void			init_xy(t_sdl *sdl, int x[3], int y[2])
{
	x[0] = ipercent_of(sdl->width, MPROPS_B_POS_X);
	x[1] = ipercent_of(sdl->width, MPROPS_B_POS_RX);
	x[2] = ipercent_of(sdl->width, MPROPS_B_POS_LX);
	y[0] = ipercent_of(sdl->height, MPROPS_B_POS_Y);
	y[1] = ipercent_of(sdl->height, MPROPS_B_OFF_Y);
}

static void			init_trigger(void (*trigger[Max_editor_action])(void*))
{
	trigger[Scale_increase] = mprops_act_scale_up;
	trigger[Size_X_increase] = mprops_act_size_x_up;
	trigger[Size_Y_increase] = mprops_act_size_y_up;
	trigger[Scale_decrease] = mprops_act_scale_down;
	trigger[Size_X_decrease] = mprops_act_size_x_down;
	trigger[Size_Y_decrease] = mprops_act_size_y_down;
	trigger[Recenter] = mprops_act_recenter;
}

static int			mprop_create_buttons(t_mprops *prop, t_env *env)
{
	t_canvas	anchor;
	void		(*trigger[Max_editor_action])(void*);
	int			x[3];
	int			y[2];
	t_u32		i;

	i = 0;
	anchor.size.x = ipercent_of(env->sdl.width, MPROPS_B_SIZE_X);
	anchor.size.y = ipercent_of(env->sdl.height, MPROPS_B_SIZE_Y);
	init_xy(&env->sdl, x, y);
	init_trigger(trigger);
	while (i < Max_editor_action)
	{
		anchor.pos = IVEC2_INIT(x[i % 3], y[0] + y[1] * ((int)i / 3));
		if (!(prop->actions[i] = button_new(anchor, NULL, env, trigger[i])))
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
	anchor.size.x = ipercent_of(env->sdl.width, MPROPS_SIZE_X);
	anchor.size.y = ipercent_of(env->sdl.height, MPROPS_SIZE_Y);
	anchor.pos.y = ipercent_of(env->sdl.height, MPROPS_TOP_POS_Y);
	anchor.pos.x = ipercent_of(env->sdl.width, MPROPS_TOP_POS_X);
	prop->anchor = anchor;
	if (mprop_create_buttons(prop, env) == ERROR)
		return (ERROR);
	TMP_color_props(env);
	return (SUCCESS);
}
