/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:52:00 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 23:09:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void			init_tex_bg(t_env *env, t_door_edit *dedit,
						t_canvas i_anch)
{
	t_canvas	anchor;
	t_u32	i;
	t_button	*b;

	b = env->inspector.action[Door];
	i = 0;
	while (i < Max_Door_Area)
	{
		anchor.size = dedit->prev[i].size;
		anchor.pos = dedit->prev[i].pos - i_anch.pos;
		texdata_fill_rect(b->tex, i_anch.size, anchor, 0x757575);
		i++;
	}
}
//
// static void			init_tex_prev(t_env *env, t_door_edit *dedit,
// 						t_canvas i_anch)
// {
// 	t_ivec2		elem_size;
// 	t_canvas	anchor;
// 	int			offset;
//
// 	elem_size = env->rpan.p[Texture_Panel]->elem_anchor.size;
// 	anchor.size = elem_size;
// 	offset = (int)((t_float)anchor.size.x * 0.2);
// 	anchor.pos.y = i_anch.pos.y + offset * 2;
// 	anchor.pos.x = i_anch.pos.x + i_anch.size.x / 2 - (anchor.size.x + offset);
// 	dedit->prev[Door_Tex] = anchor;
// 	anchor.pos.x = i_anch.pos.x + i_anch.size.x / 2 + offset;
// 	dedit->prev[Side_Tex] = anchor;
// 	// anchor.size = ipercent_of(i_anch.size.x, 33);
// 	anchor.pos.y = dedit->prev[Door_Tex].pos.y + ipercent_of(i_anch.pos.x, 10);
// 	anchor.pos.x = i_anch.pos.x + i_anch.size.x / 2 - anchor.size.x / 2;
// 	dedit->prev[Door_Prev] = anchor;
// 	anchor.size = elem_size;
// 	anchor.pos.y = i_anch.pos.y + i_anch.size.y - offset * 2 - anchor.size.y;
// 	anchor.pos.x = i_anch.pos.x + i_anch.size.x / 2 - anchor.size.x / 2;
// 	dedit->prev[Item_Prev] = anchor;
// 	init_tex_bg(env, dedit, i_anch);
// }

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
	init_tex_bg(env, dedit, i_anch);
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

	if (!(b = button_new(i_anch, NULL, env, inspector_action_door)))
		return (ERROR);
	env->inspector.action[Door] = b;
	env->inspector.get_button[Door] = inspector_gb_door;
	env->inspector.draw[Door] = inspector_draw_door;
	init_door_areas(env, &env->inspector.door_edit, i_anch);
	return (SUCCESS);
}
