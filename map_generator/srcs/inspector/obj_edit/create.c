/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:53:29 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 23:17:55 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void			init_object_edit(t_env *env, t_object_edit *oedit,
								t_button *b, t_canvas i_anch)
{
	t_panel		*p;

	p = env->rpan.p[Object_Panel];
	oedit->bg_prev.size.x = ipercent_of(i_anch.size.x, 98);
	oedit->bg_prev.size.y = ipercent_of(i_anch.size.y, 32);
	oedit->bg_prev.pos.x = i_anch.size.x / 2 - oedit->bg_prev.size.x / 2;
	oedit->bg_prev.pos.y = ipercent_of(i_anch.size.y, 10);
	texdata_fill_rect(b->tex, i_anch.size, env->obj.edit.bg_prev,
				0x484848);
	oedit->bg_prev.pos += i_anch.pos;
	oedit->tex_prev.size = p->elem_anchor.size;
	oedit->tex_prev.pos = oedit->bg_prev.size / 2 - oedit->tex_prev.size / 2;
	oedit->tex_prev.pos += oedit->bg_prev.pos;
}

int					create_object_edit_inpector(t_env *env, t_canvas i_anch)
{
	t_button	*b;

	init_objects_tools(&env->obj, &env->sdl, env);
	if (!(b = button_new(i_anch, NULL, env, inspector_action_object_edit)))
		return (ERROR);
	env->inspector.action[Object_Edit] = b;
	env->inspector.get_button[Object_Edit] = inspector_gb_object_edit;
	env->inspector.draw[Object_Edit] = inspector_draw_object_edit;
	init_object_edit(env, &env->obj.edit, b, i_anch);
	return (SUCCESS);
}
