/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/29 05:52:51 by jbulant          ###   ########.fr       */
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

static void		destroy_buttons(t_button **buttons, t_u32 count)
{
	t_u32		i;

	i = 0;
	while (i < count)
	{
		button_destroy(&buttons[i]);
		i++;
	}
}

void			destroy_objets_tools(t_objects_tools *otools)
{
	t_u32		i;

	if (otools->map_boxes)
	{
		i = 0;
		while (i < (t_u32)otools->pan->nb_elem)
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
	panel_destroy(&otools->pan);
	checkbox_destroy(&otools->cbox_solid);
}

void			env_destroy(t_env *env)
{
	sdl_destroy_textures(&env->sdl);
	sdl_destroy(&env->sdl);
	if (env->saved == False)
		ask_saving(env);
	destroy_map(env->map_info.map);
	destroy_map(env->map_info.map_mask);
	panel_destroy(&env->palette.b_pan);
	destroy_objets_tools(&env->obj);
	destroy_buttons(env->act_buttons, Max_action);
	destroy_buttons(env->inspector.action, Max_Inspector_mod);
	destroy_buttons(env->map_properties.actions, Max_editor_action);
	destroy_buttons(env->inspector.b_select.type_select, Max_brush_type);
}
