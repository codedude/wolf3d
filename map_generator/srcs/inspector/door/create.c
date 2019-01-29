/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:52:00 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 03:35:59 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void			init_tex_prev(t_env *env, t_door_edit *dedit,
						t_canvas i_anch)
{
	t_ivec2		elem_size;
	t_canvas	anchor;
	int			offset;

	elem_size = env->rpan.p[Texture_Panel]->elem_anchor.size;
	anchor.size = (int)(elem_size.x * 0.8);
	offset = (int)((i_anch.size.y - anchor.size.y * 4) / 5.0);
	anchor.pos.x = i_anch.pos.x + i_anch.size.x - (offset / 2 + anchor.size.x);
	anchor.pos.y = i_anch.pos.y + offset;
	dedit->prev[Door_Prev] = anchor;
	anchor.pos.y += offset + anchor.size.y;
	dedit->prev[Item_Prev] = anchor;
	anchor.pos.y += offset + anchor.size.y;
	dedit->prev[Door_Tex] = anchor;
	anchor.pos.y += offset + anchor.size.y;
	dedit->prev[Side_Tex] = anchor;
}

static void			init_door_areas(t_env *env, t_door_edit *dedit,
						t_canvas i_anch)
{
	init_tex_prev(env, dedit, i_anch);
	dedit->selected = NULL;
	dedit->mode = Door_Select;
}

int					create_door_inpector(t_env *env, t_canvas i_anch)
{
	t_button	*b;

	if (!(b = button_new(i_anch, &env->ui_tex[UI_Doors_BG],
					env, inspector_action_door)))
		return (ERROR);
	b->is_active = True;
	env->inspector.action[Door] = b;
	env->inspector.get_button[Door] = inspector_gb_door;
	env->inspector.draw[Door] = inspector_draw_door;
	init_door_areas(env, &env->inspector.door_edit, i_anch);
	return (SUCCESS);
}
