/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_selectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:48:55 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 23:29:15 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void				env_change_brush(t_env *env, t_u32 type)
{
	t_button	*b;
	t_b_select	*selector;
	t_u32		i;

	selector = &env->inspector.b_select;
	i = 0;
	while (i < Max_brush_type)
	{
		b = selector->type_select[i];
		b->is_active = (type == i);
		i++;
	}
	selector->type = (int)type;
}

static void			change_brush(void *v_env)
{
	t_env		*env;

	env = (t_env*)v_env;
	env_change_brush(env, env->mouse.button_index);
}

static void			init_xy(t_sdl *sdl, int x[2], int y[2])
{
	x[0] = ipercent_of(sdl->width, B_TYPE_B_P_X);
	x[1] = ipercent_of(sdl->width, B_TYPE_B_P_X2);
	y[0] = ipercent_of(sdl->height, B_TYPE_B_P_Y);
	y[1] = ipercent_of(sdl->height, B_TYPE_B_OFF_Y);
}

int 				init_type_selectors(t_env *env, t_b_select *selector)
{
	t_button	*b;
	t_canvas	anchor;
	int			x[2];
	int			y[2];
	t_u32		i;

	i = 0;
	anchor.size.x = ipercent_of(env->sdl.width, B_TYPE_B_SZ_X);
	anchor.size.y = ipercent_of(env->sdl.height, B_TYPE_B_SZ_Y);
	init_xy(&env->sdl, x, y);
	while (i < Max_brush_type)
	{
		anchor.pos = IVEC2_INIT(x[i % 2], y[0] + y[1] * ((int)i / 2));
		b = button_new(anchor, NULL, env, change_brush);
		if (!b)
			return (ERROR);
		anchor.pos = 0;
		texdata_fill_rect(b->tex, anchor.size, anchor, 0xffffff);
		selector->type_select[i] = b;
		i++;
	}
	selector->type_select[0]->is_active = True;
	selector->type = Pencil;
	return (SUCCESS);
}
