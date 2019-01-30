/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:10:03 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static void		destroy_rpanels(t_env *env)
{
	t_u32		i;

	i = 0;
	while (i < Max_RPan_Type)
	{
		panel_destroy(&env->rpan.p[i]);
		i++;
	}
}

static void		destroy_ui_tex(t_env *env)
{
	int			i;

	i = 0;
	while (i < UI_FILES_TOTAL)
	{
		tex_destroy_pixels(&env->ui_tex[i]);
		i++;
	}
	free(env->ui_tex);
}

void			env_destroy(t_env *env)
{
	sdl_destroy(&env->sdl);
	destroy_ui_tex(env);
	destroy_map_info(&env->map_info);
	object_tools_destroy(&env->obj);
	editor_destroy(&env->editor);
	destroy_button_array(env->inspector.action, Max_EditMod_type);
	checkbox_destroy(&env->inspector.world.cbox_ceil);
	destroy_button_array(env->map_properties.actions, Max_editor_action);
	destroy_button_array(env->inspector.b_select.type_select,
		Max_Brush_Buttons);
	destroy_rpanels(env);
}
