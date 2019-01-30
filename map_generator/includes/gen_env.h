/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:24:29 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:01:58 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_ENV_H
# define GEN_ENV_H

# include "libft.h"
# include "lft_plus.h"
# include "editor.h"
# include "objects_edit.h"
# include "mouse_tracker.h"
# include "ui_positions.h"
# include "inspector.h"
# include "map_edit.h"
# include "ui.h"
# include "sdl_m.h"
# include "sdl_plus.h"
# include "entity.h"

# define MAP_GEN_NAME		"Wolf3d: Editor"

# define WIN_X				1776
# define WIN_Y				1000

# define EDIT_USAGE			"W3d Editor:\n" EDIT_USAGE1
# define EDIT_USAGE1		"usage -- ./w3d_generator map_name.w3d\n"

typedef struct s_palette		t_palette;
typedef struct s_rpanel			t_rpanel;
typedef struct s_env			t_env;

# define MAP_BOXES_SZ		6

struct			s_palette {
	void		(*b_fx[Max_brush_type])(t_env *, t_canvas);
	int			brush;
};

void			palette_init(t_env *env);

void			draw_wall(void *v_env, t_ivec2 pos);

void			compute_simple_brush(t_env *env, t_canvas bounds);
void			compute_line_tracer(t_env *env, t_canvas bounds);
void			compute_hline_tracer(t_env *env, t_canvas bounds);
void			compute_vline_tracer(t_env *env, t_canvas bounds);
void			compute_square_tracer(t_env *env, t_canvas bounds);
void			compute_circle_tracer(t_env *env, t_canvas bounds);
void			compute_bucket_filler(t_env *env, t_canvas bounds);

void			env_change_brush(t_env *env, t_u32 type);

enum			e_rpan_type {
	Texture_Panel,
	Object_Panel,
	Max_RPan_Type
};

struct			s_rpanel {
	t_panel		*p[Max_RPan_Type];
	t_u32		type;
};

struct			s_env {
	t_sdl			sdl;
	t_color_pick	cpick;
	t_map_info		map_info;
	t_toolset		toolset;
	t_mousetrack	mouse;
	t_objects_tools	obj;
	t_inspector		inspector;
	t_palette		palette;
	t_mprops		map_properties;
	t_rpanel		rpan;
	t_editor		editor;
	t_tex			*ui_tex;
	t_ivec2			spawn;
	int				ed_map_value;
	t_bool			erasing;
	int				spawn_rotation;
	t_canvas		grid;
	int				space;
	int				alt;
	int				ctrl;
	char			*save_file;
	int				loaded;
};

int				env_init(t_env *env, char *filename);
void			env_destroy(t_env *env);

int				save_file(t_env *env);
void			save_map(t_env *env, int fd);

int				manage_binds(SDL_Event *event, t_env *env);
int				on_key_press(SDL_Event *event, t_env *env);
int				on_key_release(SDL_Event *event, t_env *env);
void			manage_down(const Uint8	*state, t_env *env);

void			draw_update(t_env *env, t_sdl *sdl);
void			draw_ui(t_env *env, t_sdl *sdl);

/*
**		UI Files
*/

# define UI_FOLDER	"data/editor_ui/"

# define UI_FILE01	UI_FOLDER "doors/doors_bg.png"
# define UI_FILE02	UI_FOLDER "edit_mode/edit_mode_bg.png"
# define UI_FILE03	UI_FOLDER "edit_mode/painter.png"
# define UI_FILE04	UI_FOLDER "edit_mode/world.png"
# define UI_FILE05	UI_FOLDER "edit_mode/doors.png"
# define UI_FILE06	UI_FOLDER "edit_mode/objects.png"
# define UI_FILE07	UI_FOLDER "map_props/map_props_bg.png"
# define UI_FILE08	UI_FOLDER "map_props/recenter.png"
# define UI_FILE09	UI_FOLDER "map_props/sizeX_decrease.png"
# define UI_FILE10	UI_FOLDER "map_props/sizeX_increase.png"
# define UI_FILE11	UI_FOLDER "map_props/sizeY_decrease.png"
# define UI_FILE12	UI_FOLDER "map_props/sizeY_increase.png"
# define UI_FILE13	UI_FOLDER "map_props/zoom_in.png"
# define UI_FILE14	UI_FOLDER "map_props/zoom_out.png"
# define UI_FILE15	UI_FOLDER "objects/checkbox.png"
# define UI_FILE16	UI_FOLDER "objects/objects_bg.png"
# define UI_FILE17	UI_FOLDER "objects/prev_bg.png"
# define UI_FILE18	UI_FOLDER "objects/slide_curs.png"
# define UI_FILE19	UI_FOLDER "painter/brush.png"
# define UI_FILE20	UI_FOLDER "painter/circle.png"
# define UI_FILE21	UI_FOLDER "painter/eraser.png"
# define UI_FILE22	UI_FOLDER "painter/h_line.png"
# define UI_FILE23	UI_FOLDER "painter/line.png"
# define UI_FILE24	UI_FOLDER "painter/p_bucket.png"
# define UI_FILE25	UI_FOLDER "painter/painter_bg.png"
# define UI_FILE26	UI_FOLDER "painter/pencil.png"
# define UI_FILE27	UI_FOLDER "painter/rect.png"
# define UI_FILE28	UI_FOLDER "painter/v_line.png"
# define UI_FILE29	UI_FOLDER "world/world_bg.png"

enum			e_ui_files {
	UI_Doors_BG,
	UI_EMode_BG,
	UI_EMode_Buttons,
	UI_EMode_Painter = UI_EMode_Buttons,
	UI_EMode_World,
	UI_EMode_Doors,
	UI_EMode_Objects,
	UI_MProps_BG,
	UI_MProps_Recenter,
	UI_MProps_SX_DEC,
	UI_MProps_SX_INC,
	UI_MProps_SY_DEC,
	UI_MProps_SY_INC,
	UI_MProps_Zoom_In,
	UI_MProps_Zoom_Out,
	UI_CheckBox,
	UI_Objects_BG,
	UI_Objects_Prev_BG,
	UI_Objects_SlideCurs,
	UI_Painter_Brush,
	UI_Painter_Circle,
	UI_Painter_Eraser,
	UI_Painter_H_Line,
	UI_Painter_Line,
	UI_Painter_P_Bucket,
	UI_Painter_BG,
	UI_Painter_Pencil,
	UI_Painter_Rect,
	UI_Painter_V_Line,
	UI_World_BG,
	UI_FILES_TOTAL
};

# define UI_F_REPACK1	UI_FILE01, UI_FILE02, UI_FILE03, UI_FILE04, UI_FILE05
# define UI_F_REPACK2	UI_FILE06, UI_FILE07, UI_FILE08, UI_FILE09, UI_FILE10
# define UI_F_REPACK3	UI_FILE11, UI_FILE12, UI_FILE13, UI_FILE14, UI_FILE15
# define UI_F_REPACK4	UI_FILE16, UI_FILE17, UI_FILE18, UI_FILE19, UI_FILE20
# define UI_F_REPACK5	UI_FILE21, UI_FILE22, UI_FILE23, UI_FILE24, UI_FILE25
# define UI_F_REPACK6	UI_FILE26, UI_FILE27, UI_FILE28, UI_FILE29

# define UI_F_REPACK_1	UI_F_REPACK1, UI_F_REPACK2, UI_F_REPACK3, UI_F_REPACK4
# define UI_F_REPACK_2	UI_F_REPACK5, UI_F_REPACK6

# define UI_F_REPACK	UI_F_REPACK_1, UI_F_REPACK_2

#endif
