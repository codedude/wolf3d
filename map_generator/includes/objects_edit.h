/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects_edit.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:39:24 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:47:52 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_EDIT_H
# define OBJECTS_EDIT_H

# include "types.h"
# include "sdl_plus.h"
# include "entity.h"
# include "ui.h"

/*
**		Forward declaration
*/

typedef struct s_object_edit	t_object_edit;
typedef struct s_objects_tools	t_objects_tools;
typedef struct s_object_e		t_object_e;

typedef struct s_env			t_env;

/*
**		Object elem info
*/

struct			s_object_e {
	t_vec2		pos;
	t_float		y_pos;
	t_bool		is_solid;
	t_bool		collectible;
	t_entity	*unlock_door;
	t_float		scale;
	t_u32		id;
};

/*
**		Inspector
*/

enum			e_otools_button {
	Grid_Snap,
	Box_Is_Solid,
	Obj_Preview,
	Otools_No_Button
};

struct			s_object_edit {
	t_canvas	bg_prev;
	t_canvas	tex_prev;
	int			selected;
	t_float		saved_scale;
};

int				create_object_edit_inpector(t_env *env, t_canvas i_anch);
void			inspector_draw_object_edit(t_env *env);
void			inspector_action_object_edit(void *v_env);
t_bool			inspector_gb_object_edit(t_env *env);

/*
**		Object tools
*/

# define MAX_OBJECTS		150

struct			s_objects_tools {
	t_object_edit	edit;
	t_slider		*g_snap;
	t_checkbox		*cbox_solid;
	t_ivec2			mb_size;
	t_object_e		*list[MAX_OBJECTS];
	t_bool			holding;
	t_u32			count;
};

int				init_objects_tools(t_objects_tools *obj_tools, t_sdl *sdl,
							t_env *env);
int				init_cbox_solid(t_objects_tools *otools, t_sdl *sdl,
								t_env *env);
void			object_tools_destroy(t_objects_tools *otools);

void			add_new_object(t_objects_tools *otools, t_vec2 pos,
						t_bool is_solid, t_u32 id);
void			object_destroy(t_objects_tools *otools, t_u32 obj_i);

int				get_obj_at_mpos(t_env *env);

#endif
