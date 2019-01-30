/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   painter.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:16:31 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:31:20 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PAINTER_H
# define PAINTER_H

# include "types.h"
# include "ui.h"

/*
**		Forward declaration
*/

typedef struct s_b_select		t_b_select;
typedef struct s_toolset		t_toolset;

typedef struct s_env			t_env;

/*
**		Common
*/

enum			e_brush_buttons {
	Pencil,
	Line,
	Vertical_line,
	Horizontal_line,
	Square,
	Circle,
	Paint_Bucket,
	Max_brush_type,
	Brush_Mode = Max_brush_type,
	Eraser_Mode,
	Max_Brush_Buttons
};

/*
**		Inspector
*/

struct			s_b_select {
	t_button	*type_select[Max_Brush_Buttons];
	t_ivec2		anchor;
	int			type;
	int			type_save;
};

int				init_type_selectors(t_env *env, t_b_select *selector);

int				create_painter_inpector(t_env *env, t_canvas i_anch);
void			inspector_action_painter(void *v_env);
void			inspector_draw_painter(t_env *env);
t_bool			inspector_gb_painter(t_env *env);

/*
**		Toolset
*/

enum			e_tooltype {
	Brush,
	Eraser,
	SpawnSetter,
	Picker,
	Max_ToolType_Painter,
	Hand = Max_ToolType_Painter,
	ZoomIn,
	ZoomOut,
	Max_ToolType
};

struct			s_toolset {
	void		(*map_fx[Max_ToolType])(t_env *env);
	t_u32		tmp_type;
	t_u32		type;
	t_bool		use_tmp;
};

void			init_toolset(t_toolset *toolset);
void			toolset_set_type(t_toolset *toolset, t_u32 type);
void			toolset_set_tmp_type(t_toolset *toolset, t_u32 type);
t_u32			toolset_get_type(t_toolset *toolset);
void			toolset_use_fx(t_env *env);

void			map_fx_picker(t_env *env);
void			map_fx_hand(t_env *env);
void			map_fx_zoomin(t_env *env);
void			map_fx_zoomout(t_env *env);
void			map_fx_brush(t_env *env);
void			map_fx_spawnsetter(t_env *env);
void			map_fx_eraser(t_env *env);

#endif
