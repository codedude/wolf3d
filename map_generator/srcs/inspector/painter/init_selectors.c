/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_selectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:48:55 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 03:56:26 by jbulant          ###   ########.fr       */
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

static void			init_xy(t_sdl *sdl, int xy[4], int tex_id[Max_brush_type])
{
	xy[0] = ipercent_of(sdl->width, B_TYPE_B_P_X);
	xy[1] = ipercent_of(sdl->width, B_TYPE_B_P_X2);
	xy[2] = ipercent_of(sdl->height, B_TYPE_B_P_Y);
	xy[3] = ipercent_of(sdl->width, B_TYPE_B_OFF_Y);
	tex_id[Pencil] = UI_Painter_Pencil;
	tex_id[Line] = UI_Painter_Line;
	tex_id[Horizontal_line] = UI_Painter_H_Line;
	tex_id[Vertical_line] = UI_Painter_V_Line;
	tex_id[Square] = UI_Painter_Rect;
	tex_id[Circle] = UI_Painter_Circle;
	tex_id[Paint_Bucket] = UI_Painter_P_Bucket;
}

int 				init_type_selectors(t_env *env, t_b_select *selector)
{
	t_button	*b;
	t_canvas	anchor;
	int			xy[4];
	int			tex_id[Max_brush_type];
	t_u32		i;

	i = 0;
	anchor.size = ipercent_of(env->sdl.width, B_TYPE_B_SZ);
	init_xy(&env->sdl, xy, tex_id);
	while (i < Max_brush_type)
	{
		anchor.pos = IVEC2_INIT(xy[i % 2], xy[2] + xy[3] * ((int)i / 2));
		b = button_new(anchor, &env->ui_tex[tex_id[i]], env, change_brush);
		if (!b)
			return (ERROR);
		selector->type_select[i] = b;
		i++;
	}
	selector->type_select[0]->is_active = True;
	selector->type = Pencil;
	return (SUCCESS);
}
