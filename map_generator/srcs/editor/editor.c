/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/10 23:54:46 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 21:49:07 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "editor.h"
#include "gen_env.h"

void			editor_destroy(t_editor *editor)
{
	destroy_button_array(editor->switch_b, Max_EditMod_type);
}

int				editor_init(t_env *env, t_sdl *sdl, t_editor *editor)
{
	t_canvas	anchor;

	anchor.size.x = ipercent_of(sdl->width, EDITMOD_SZ_X);
	anchor.size.y = ipercent_of(sdl->height, EDITMOD_SZ_Y);
	anchor.pos.x = ipercent_of(sdl->width, EDITMOD_P_X);
	anchor.pos.y = ipercent_of(sdl->height, EDITMOD_P_Y);
	editor->anchor = anchor;
	editor->mode = Painter;
	return (init_editor_switch(env, sdl, editor));
}
