/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 16:39:41 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 23:52:22 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSPECTOR_H
# define INSPECTOR_H

# include "types.h"
# include "ui.h"

# include "entity.h"

# include "editor.h"
# include "painter.h"
# include "map_edit.h"

/*
**		Forward declaration
*/

typedef struct s_world_i		t_world_i;
typedef struct s_door_edit		t_door_edit;
typedef struct s_inspector		t_inspector;
typedef struct s_radar			t_radar;

typedef struct s_env			t_env;

/*
**		World inspector - struct & enum
*/

enum			e_world_buttons {
	WButton_Ceil,
	WButton_Floor,
	Max_WButton_Prev,
	WButton_Radar = Max_WButton_Prev,
	WButton_Draw_Ceil
};

struct			s_radar {
	t_float		vlines_height;
	t_ivec2		center;
	int			radius;
	int			gizmo_rad;
	t_float		f_radius;
	t_float		triangle_cdist;
	int			squ_radius;
};

void			draw_radar(t_env *env, t_radar *radar);
void			init_radar(t_env *env, t_radar *radar, t_canvas i_anch);

struct			s_world_i {
	t_radar		radar;
	t_canvas	prev[Max_WButton_Prev];
	t_u32		id[Max_WButton_Prev];
	t_bool		draw_ceil;
	t_checkbox	*cbox_ceil;
};

int				create_world_inpector(t_env *env, t_canvas i_anch);

void			inspector_draw_world(t_env *env);
void			inspector_action_world(void *v_env);
t_bool			inspector_gb_world(t_env *env);

/*
**		Door inspector - struct & enum
*/

enum			e_door_ed_mode {
	Door_Select,
	Object_Select
};

enum			e_door_edit_area {
	Door_Tex,
	Side_Tex,
	Max_Door_Tex,
	Door_Prev = Max_Door_Tex,
	Item_Prev,
	Max_Door_Area
};

struct			s_door_edit {
	t_canvas	prev[Max_Door_Area];
	t_u32		count;
	t_entity	*selected;
	t_ivec2		door_pos;
	t_u32		mode;
};

int				create_door_inpector(t_env *env, t_canvas i_anch);
void			inspector_action_door(void *v_env);
t_bool			inspector_gb_door(t_env *env);
void			inspector_draw_door(t_env *env);

t_bool			door_valid_mouse_coord(t_env *env);
t_bool			door_check_neighbour(t_map *map, t_entity *ent);
void			door_destroy_selected(t_env *env, t_door_edit *dedit);
int				door_create(t_env *env, t_door_edit *dedit);


/*
**		Inspector - struct & enum
*/

struct			s_inspector {
	t_world_i	world;
	t_b_select	b_select;
	t_door_edit	door_edit;
	void		(*draw[Max_EditMod_type])(t_env *);
	t_bool		(*get_button[Max_EditMod_type])(t_env *);
	t_button	*action[Max_EditMod_type];
};

int				env_create_inspect(t_env *env);

#endif
