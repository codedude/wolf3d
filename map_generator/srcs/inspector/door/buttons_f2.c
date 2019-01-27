/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_f2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 23:05:19 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 23:39:59 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

t_bool			inspector_gb_door(t_env *env)
{
	t_door_edit		*dedit;
	t_u32			i;

	dedit = &env->inspector.door_edit;
	i = 0;
	while (i < Max_Door_Area)
	{
		if (is_bounded(env->mouse.pos, dedit->prev[i]))
		{
			env->mouse.button_index = i;
			return (True);
		}
		i++;
	}
	return (False);
}

void			inspector_action_door(void *v_env)
{
	t_door_edit	*dedit;
	t_env		*env;
	t_entity	*ent;
	t_u32		index;

	env = (t_env*)v_env;
	dedit = &env->inspector.door_edit;
	ent = dedit->selected;
	if (ent == NULL || env->mouse.b1_status != Mouse_Release)
		return ;
	index = env->mouse.button_index;
	if (index == Door_Tex)
		ent->tex_id = (int)env->rpan.p[Texture_Panel]->cursor;
	else if (index == Side_Tex)
		ent->e.door->tex_wall_id = (int)env->rpan.p[Texture_Panel]->cursor;
	else if (index == Item_Prev)
		dedit->mode = !dedit->mode;

}
