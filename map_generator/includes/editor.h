/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 16:45:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:45:35 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EDITOR_H
# define EDITOR_H

# include "ui.h"
# include "sdl_m.h"
# include "types.h"

/*
**		Forward declaration
*/

typedef struct s_editor			t_editor;

typedef struct s_env			t_env;

/*
**		Editor
*/

enum			e_editor_type {
	Painter,
	World,
	Door,
	Object_Edit,
	Max_EditMod_type
};

struct			s_editor {
	t_canvas	anchor;
	t_button	*switch_b[Max_EditMod_type];
	t_u32		mode;
};

int				init_editor_switch(t_env *env, t_sdl *sdl, t_editor *editor);

int				editor_init(t_env *env, t_sdl *sdl, t_editor *editor);
void			editor_destroy(t_editor *editor);

#endif
