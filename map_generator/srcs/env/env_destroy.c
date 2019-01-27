/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 22:38:55 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"


static void		ask_saving(t_env *env)
{
	char	str[5];
	ssize_t	r;

	ft_putstr("W3dEditor: modification occurs\n");
	ft_putstr("  Would you like to save (Yes/No): ");
	while ((r = read(0, str, 4)) > 0)
	{
		str[r - 1] = '\0';
		ft_strtolower(str);
		if (ft_strequ("yes", str) || ft_strequ("y", str))
		{
			save_file(env);
			break ;
		}
		if (ft_strequ("no", str) || ft_strequ("n", str))
			break ;
		ft_putstr("Please answer by [Yes] or [No]\n");
		ft_putstr("  Would you like to save (Yes/No): ");
	}
}


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

void			env_destroy(t_env *env)
{
	sdl_destroy(&env->sdl);
	if (env->saved == False)
		ask_saving(env);
	destroy_map_info(&env->map_info);
	object_tools_destroy(&env->obj, env->rpan.p[Object_Panel]);
	editor_destroy(&env->editor);
	destroy_button_array(env->inspector.action, Max_EditMod_type);
	checkbox_destroy(&env->inspector.world.cbox_ceil);
	destroy_button_array(env->map_properties.actions, Max_editor_action);
	destroy_button_array(env->inspector.b_select.type_select, Max_Brush_Buttons);
	destroy_rpanels(env);
}
