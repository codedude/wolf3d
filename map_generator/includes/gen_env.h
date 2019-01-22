/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:24:29 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/22 02:48:12 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_ENV_H
# define GEN_ENV_H

# include "libft.h"
# include "sdl_m.h"
# include "entity.h"

# define MAP_GEN_NAME		"Wolf3d: Editor"

# define WIN_X				1776
# define WIN_Y				1000

# define EDIT_USAGE			"W3d Editor:\n" EDIT_USAGE1
# define EDIT_USAGE1		"usage -- ./w3d_generator map_name.w3d\n"

/*
**	MAP WIDTH / HEIGHT
*/

# define DEF_SIZE_X			24
# define DEF_SIZE_Y			24
# define MIN_SIZE_X			5
# define MIN_SIZE_Y			5
# define MAX_SIZE_X			64
# define MAX_SIZE_Y			64

/*
**	GRID
*/

# define GRID_OFF_X			1
# define GRID_OFF_Y			5
# define GRID_PERC_X		74

# define GRID_SIZE_X		(GRID_PERC_X - (GRID_OFF_X * 2))
# define GRID_SIZE_Y		(100 - (GRID_OFF_Y * 2))

/*
**	BRUSHES
*/

# define PREV_BOX_PERC		10

# define BRUSH_C_SIZE		10
# define BRUSH_OFF_X		(GRID_PERC_X + GRID_OFF_X)
# define BRUSH_OFF_Y		95

# define OBJ_OFF_X			(91)
# define OBJ_OFF_Y			GRID_OFF_Y
# define OBJ_SIZE_X			7
# define OBJ_SIZE_Y			GRID_SIZE_Y

/*
**	MPROPS
*/

# define MPROPS_SIZE_X			(MPROPS_B_SIZE_X + MPROPS_B_OFF_X * 2 + 2)
# define MPROPS_SIZE_Y			(MPROPS_B_SIZE_Y + MPROPS_B_OFF_Y * 2 + 6)
# define MPROPS_TOP_POS_Y		OBJ_OFF_Y
# define MPROPS_TOP_POS_X		(OBJ_OFF_X - (MPROPS_SIZE_X + 1))

# define MPROPS_B_SIZE_X		4
# define MPROPS_B_SIZE_Y		4

# define MPROPS_B_POS_LX		(1 + MPROPS_TOP_POS_X)
# define MPROPS_B_POS_X			(MPROPS_B_POS_LX + MPROPS_B_OFF_X)
# define MPROPS_B_POS_RX		(MPROPS_B_POS_X + MPROPS_B_OFF_X)
# define MPROPS_B_POS_Y			(3 + MPROPS_TOP_POS_Y)
# define MPROPS_B_OFF_X			(1 + MPROPS_B_SIZE_X)
# define MPROPS_B_OFF_Y			(2 + MPROPS_B_SIZE_Y)

/*
**	BRUSH_TYPE_BUTTONS
*/

# define B_TYPE_TOP_POS_Y		INSPECTOR_TOP_POS_Y
# define B_TYPE_TOP_POS_X		INSPECTOR_TOP_POS_X

# define B_TYPE_B_SIZE_X		5
# define B_TYPE_B_SIZE_Y		5

# define B_TYPE_B_POS_X			(INSPECTOR_MID_POS_X + 1)
# define B_TYPE_B_POS_X2		(INSPECTOR_MID_POS_X - 1 - B_TYPE_B_SIZE_X)
# define B_TYPE_B_POS_Y			(3 + B_TYPE_TOP_POS_Y)
# define B_TYPE_B_OFF_X			(1 + B_TYPE_B_SIZE_X)
# define B_TYPE_B_OFF_Y			(2 + B_TYPE_B_SIZE_Y)

/*
**	INSPECTOR
*/

# define INSPECTOR_SIZE_X		(BUTTON_SIZE + BUTTON_OFFSET * 2 + 2)
# define INSPECTOR_SIZE_Y		(BUTTON_TOP_POS_Y - (MPROPS_TOP_POS_Y + MPROPS_SIZE_Y + 4))
# define INSPECTOR_TOP_POS_Y	(MPROPS_TOP_POS_Y + (MPROPS_SIZE_Y + 2))
# define INSPECTOR_TOP_POS_X	(OBJ_OFF_X - (INSPECTOR_SIZE_X + 1))
# define INSPECTOR_MID_POS_X	(INSPECTOR_TOP_POS_X + INSPECTOR_SIZE_X / 2)

/*
**	EDITMOD
*/

# define EDITMOD_SIZE_X			INSPECTOR_SIZE_X
# define EDITMOD_SIZE_Y			((GRID_OFF_Y + GRID_SIZE_Y) - EDITMOD_POS_Y)
# define EDITMOD_POS_X			INSPECTOR_TOP_POS_X
# define EDITMOD_POS_Y			(INSPECTOR_TOP_POS_Y + INSPECTOR_SIZE_Y + 1)
# define EDITMOD_MID_POS_X		(EDITMOD_POS_X + EDITMOD_SIZE_X / 2)
# define EDITMOD_MID_POS_Y		(EDITMOD_POS_Y + EDITMOD_SIZE_Y / 2)

# define EM_B_POS_X				(EDITMOD_MID_POS_X - (EM_B_SIZE_X + 1))
# define EM_B_POS_Y				(EDITMOD_MID_POS_Y - (EM_B_SIZE_Y + 1))
# define EM_B_POS2_X			(EDITMOD_MID_POS_X + 1)
# define EM_B_POS2_Y			(EDITMOD_MID_POS_Y + 1)

# define EM_B_SIZE_X			5
# define EM_B_SIZE_Y			3

// OLD !
# define BUTTON_SIZE			4
# define BUTTON_OFFSET			(BUTTON_SIZE + 1)
# define BUTTON_TOP_POS_X		(OBJ_OFF_X - (BUTTON_SIZE + 2))
# define BUTTON_TOP_POS_Y		(OBJ_OFF_Y + OBJ_SIZE_Y - (BUTTON_SIZE * 2) - 1)


/*
**	GRID_SNAP_SLIDER
*/

# define G_SNAP_POS_Y			(INSPECTOR_TOP_POS_Y + INSPECTOR_SIZE_Y - 4)
# define G_SNAP_POS_X			INSPECTOR_TOP_POS_X + 1

# define G_SNAP_S_SIZE_X		(INSPECTOR_SIZE_X - 2)
# define G_SNAP_S_SIZE_Y		2

# define G_SNAP_C_SIZE_X		1
# define G_SNAP_C_SIZE_Y		4

/*
**	CHECKBOX_IS_SOLID
*/

# define CB_SOL_POS_Y			(G_SNAP_POS_Y - (CB_SOL_S_SIZE + 5))
# define CB_SOL_POS_X			(G_SNAP_POS_X + (G_SNAP_S_SIZE_X - CB_SOL_S_SIZE))

# define CB_SOL_S_SIZE			3

# define CANVAS_INIT(x, y)	(t_canvas){(x), (y)}

typedef struct	s_canvas {
	t_ivec2		pos;
	t_ivec2		size;
}				t_canvas;

typedef struct	s_map {
	t_ivec2		size;
	t_entity	**data;
	// int			**data;
}				t_map;

typedef struct	s_panel {
	t_color		**elem_tex;
	t_tex		*tex;
	t_u32		nb_elem;
	t_u32		cursor;
	t_canvas	anchor;
	t_u32		viewable_elem;
	t_canvas	elem_anchor;
	t_ivec2		elem_pos;
	t_color		bg_col;
	t_bool		draw_bg;
	t_color		border_col;
	t_bool		draw_border;
	int			hightlight;
	t_u32		view_min;
	t_u32		view_max;
}				t_panel;

t_color			*new_texdata(t_tex *tex, t_ivec2 size);

t_panel			*new_panel(t_u32 nb_elem, t_canvas anchor, void *param,
						t_color **(*get_elems)(void *, t_ivec2),
						t_tex *elems);
void			panel_set_anchor(t_panel *pan, t_canvas anchor);
void			panel_set_bgcolor(t_panel *pan, t_u32 color);
void			panel_set_bordercolor(t_panel *pan, t_u32 color);
void			panel_set_highlight(t_panel *pan);
void			panel_destroy(t_panel **pan);

void			panel_decrease_view(t_panel *pan);
void			panel_increase_view(t_panel *pan);
void			panel_change_view(t_panel *pan, int move);
void			panel_update_cursor(t_panel *pan, t_u32 new_curs);

t_bool			panel_isinside(t_panel *pan, t_ivec2 point);
int				panel_get_index_by_pos(t_panel *pan, t_ivec2 point);
t_canvas		panel_get_elem_anchor(t_panel *pan, int i);

t_color			**new_panel_tex(t_sdl *sdl, t_u32 nb, t_ivec2 size,
							t_tex *(*tex_src)(t_sdl*, int));
void			destroy_panel_tex(t_color ***pbox_src, unsigned int nb);

enum			e_user_action {
	Draw_Wall,
	Set_Spawn,
	Erase_Wall,
	Edit_Obj,
	Max_action
};

typedef struct	s_button {
	t_canvas	anchor;
	t_color		*tex;
	t_bool		is_active;
	void		*param;
	void		(*trigger)(void*);
}				t_button;

t_button		*button_new(t_canvas anchor, t_tex *tex, void *param,
						void (*trigger)(void*));
t_bool			button_hover(t_button *button, t_ivec2 pos);
void			button_trigger(t_button *button);
void			button_setactive(t_button *button, t_bool active);
void			button_destroy(t_button **button);

enum			e_editor_action {
	Size_Y_decrease,
	Scale_increase,
	Scale_decrease,
	Recenter,
	Size_X_increase,
	Size_X_decrease,
	Size_Y_increase,
	Max_editor_action
};

typedef struct s_mprops			t_mprops;
typedef struct s_mousetrack		t_mousetrack;
typedef struct s_color_pick		t_color_pick;
typedef struct s_checkbox		t_checkbox;
typedef struct s_object_edit	t_object_edit;
typedef struct s_objects_tools	t_objects_tools;
typedef struct s_slider			t_slider;
typedef struct s_object_e		t_object_e;
typedef struct s_world_i		t_world_i;
typedef struct s_door_e			t_door_e;
typedef struct s_door_edit		t_door_edit;
typedef struct s_inspector		t_inspector;
typedef struct s_palette		t_palette;
typedef struct s_map_info		t_map_info;
typedef struct s_toolset		t_toolset;
typedef struct s_rpanel			t_rpanel;
typedef struct s_radar			t_radar;
typedef struct s_b_select		t_b_select;
typedef struct s_editor			t_editor;
typedef struct s_env			t_env;

struct			s_mprops {
	t_button	*actions[Max_editor_action];
	t_canvas	anchor;
	t_u32		tick;
	t_u32		speed;
};

enum			e_win_area {
	Map_window,
	Map_properties_buttons,
	Inspector,
	Tools_buttons,
	Right_Panel,
	Max_Win_Area,
	Not_On_Window = Max_Win_Area
};

enum			e_mb_status {
	Mouse_no_clic,
	Mouse_Press,
	Mouse_Hold,
	Mouse_Release
};

struct			s_mousetrack {
	t_bool		(*get_area[Max_Win_Area])(t_env *);
	void		(*trigger[Max_Win_Area])(t_env *);
	void		(*update[Max_Win_Area])(t_env *);
	t_ivec2		last_pos;
	t_ivec2		rel_pos;
	t_ivec2		pos;
	t_ivec2		record_pos_b;
	t_vec2		obj_offset;
	t_u32		area;
	t_bool		b1;
	t_u32		b1_status;
	t_bool		b2;
	t_bool		b2_cancel_b1;
	t_bool		is_editing;
	t_bool		no_trigger;
	t_u32		button_index;
	int			wheel;
};

struct			s_color_pick {
	t_canvas	canvas_mask;
	t_bool		use_canvas;
	t_bool		use_transparency;
	t_color		replace;
	t_color		current;
	t_color		ignore_c;
};

enum			e_brush_Buttons {
	Pencil,
	Line,
	Horizontal_line,
	Vertical_line,
	Square,
	Circle,
	Paint_Bucket,
	Max_brush_type,
	Brush_Mode = Max_brush_type,
	Eraser_Mode,
	Max_Brush_Buttons
};

# define MAX_OBJECTS		150

struct			s_object_e {
	t_vec2		pos;
	t_float		y_pos;
	t_bool		is_solid;
	t_bool		collectible;
	t_entity	*unlock_door;
	t_float		scale;
	t_u32		id;
};

void			add_new_object(t_objects_tools *otools, t_vec2 pos,
						t_bool is_solid, t_u32 id);
void			object_destroy(t_objects_tools *otools, t_u32 obj_i);

# define MAP_BOXES_SIZE		6

enum			e_direction {
	Dir_Horizontal,
	Dir_Vertical
};

struct			s_slider {
	t_color		*slid_img;
	t_ivec2		slid_img_size;
	t_color		*curs_img;
	t_ivec2		curs_img_size;
	t_ivec2		pos;
	int			direction;
	int			size;
	t_float		step;
	t_float		min_val;
	t_float		max_val;
	t_float		range;
	t_float		val;
};

t_slider		*slider_new(t_ivec2 pos, t_tex *imgs[2],
						t_ivec2 img_size[2]);
void			slider_setup(t_slider *slider, int direction,
						t_vec2 range, t_float step);
t_bool			slider_hover(t_slider *slider, t_ivec2 pos);
void			slider_draw(t_env *env, t_slider *slider);
void			slider_update_bypos(t_slider *slider, t_ivec2 pos);
void			slider_destroy(t_slider **slider);

enum			e_cbox_state {
	Unchecked,
	Check,
	Unavailable
};

struct			s_checkbox {
	t_color		*tex;
	t_canvas	anchor;
	void		*param;
	int			(*get_state)(void *);
	void		(*reverse_state)(void *);
};

t_checkbox		*checkbox_new(t_canvas anchor, t_tex *tex);
void			checkbox_setup(t_checkbox *cbox, void *param,
					void (*reverse_state)(void*), int (*get_state)(void *));
t_bool			checkbox_hover(t_checkbox *cbox, t_ivec2 pos);
void			checkbox_draw(t_env *env, t_checkbox *cbox);
void			checkbox_clic(t_checkbox *cbox);
void			checkbox_destroy(t_checkbox **cbox);

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

struct			s_objects_tools {
	t_object_edit	edit;
	t_slider		*g_snap;
	t_checkbox		*cbox_solid;
	t_color			**map_boxes;
	t_ivec2			mb_size;
	t_object_e		*list[MAX_OBJECTS];
	t_bool			holding;
	t_u32			count;
};

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

int				init_editor(t_env *env, t_sdl *sdl, t_editor *editor);

struct			s_radar {
	t_float		vlines_height;
	t_ivec2		center;
	int			radius;
	int			gizmo_rad;
	t_float		f_radius;
	t_float		triangle_cdist;
	int			squ_radius;
};

struct			s_b_select {
	t_button	*type_select[Max_Brush_Buttons];
	t_ivec2		anchor;
	int			type;
	int			type_save;
};

enum			e_world_buttons {
	WButton_Ceil,
	WButton_Floor,
	Max_WButton_Prev,
	WButton_Radar = Max_WButton_Prev,
	WButton_Draw_Ceil
};

struct			s_world_i {
	t_radar		radar;
	t_canvas	prev[Max_WButton_Prev];
	t_u32		id[Max_WButton_Prev];
	t_bool		draw_ceil;
	t_checkbox	*cbox_ceil;
};

enum			e_door_edit_area {
	Door_Tex,
	Side_Tex,
	Max_Door_Tex,
	Door_Prev = Max_Door_Tex,
	Item_Prev,
	Max_Door_Area
};

t_bool			door_valid_mouse_coord(t_env *env);
t_bool			door_check_neighbour(t_map *map, t_entity *ent);
void			door_destroy_selected(t_env *env, t_door_edit *dedit);
int				door_create(t_env *env, t_door_edit *dedit);

t_bool			door_valid_mouse_coord(t_env *env);

enum			e_door_ed_mode {
	Door_Select,
	Object_Select
};

struct			s_door_edit {
	t_canvas	prev[Max_Door_Area];
	t_u32		count;
	t_entity	*selected;
	t_ivec2		door_pos;
	t_u32		mode;
};

struct			s_inspector {
	t_world_i	world;
	t_b_select	b_select;
	t_door_edit	door_edit;
	void		(*draw[Max_EditMod_type])(t_env *);
	t_bool		(*get_button[Max_EditMod_type])(t_env *);
	t_button	*action[Max_EditMod_type];
};

struct			s_palette {
	void		(*b_fx[Max_brush_type])(t_env *, t_canvas);
	int			brush;
};

struct			s_map_info {
	int			x_draw[MAX_SIZE_X + 1];
	int			y_draw[MAX_SIZE_Y + 1];
	t_map		*map;
	int			**tmp_data;
	t_vec2		pos;
	t_float		zoom;
	t_float		zoom_min;
	t_float		zoom_max;
	t_vec2		grid_center;
	t_vec2		map_center;
};

void			map_scale2grid(t_env *env);
void			map_update_center(t_env *env);

void			mprops_act_scale_up(void *v_env);
void			mprops_act_scale_down(void *v_env);
void			mprops_act_size_x_up(void *v_env);
void			mprops_act_size_y_up(void *v_env);
void			mprops_act_size_x_down(void *v_env);
void			mprops_act_size_y_down(void *v_env);

void			free_ar_data(void **tab, size_t size);
void			**new_ar_data(size_t height, size_t width);

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
	t_ivec2			spawn;
	int				ed_map_value;
	t_bool			erasing;
	int				spawn_rotation;
	t_canvas		grid;
	int				space;
	int				alt;
	int				ctrl;
	char			*save_file;
	int				kframe;
	int				loaded;
	int				saved;
};

void			toggle_action(t_env *env, int action);

int				env_init(t_env *env, char *filename);
void 			palette_init(t_env *env);
void			mouse_track_init(t_env *env);
int				init_wall_pbox(t_panel **pan, t_sdl *sdl);
int				init_objects_tools(t_objects_tools *obj_tools, t_sdl *sdl,
							t_env *env);
int				init_object_pbox(t_panel **pan, t_sdl *sdl);
int				env_create_inspect(t_env *env);
int				env_create_mprops(t_env *env);
void			env_destroy(t_env *env);
t_map			*map_new(t_ivec2 size);
void			clear_map(t_map_info *m_inf);
void			destroy_map(t_map *map);
int				sdl_clear_color(t_sdl *sdl, unsigned int color);
void			sdl_put_pixel_safe(t_sdl *sdl, t_ivec2 px, t_color c);
t_color			sdl_pixel_pick_from_img(t_sdl *sdl, int x, int y);

t_bool			is_valid_mapfile(char *filename);
int				save_file(t_env *env);

int				manage_binds(SDL_Event *event, t_env *env);
void			manage_down(const Uint8	*state, t_env *env);

void			draw_grid(t_env *env, t_sdl *sdl);
// void			draw_grid_lines(t_env *env, t_sdl *sdl);
void			draw_map(t_env *env, t_sdl *sdl);
void			draw_player_radar(t_env *env, t_radar *radar);
void			draw_node(t_env *env, t_sdl *sdl, t_map_info *minf, t_ivec2 i);
void			draw_on_map(t_env *env, int brush);

int				ipercent_of(int of, int percent);
t_bool			is_bounded(t_ivec2 pos, t_canvas canvas);
t_canvas		get_map_boundaries(t_env *env);
t_vec2			map_to_center(t_env *env);
t_ivec2			mpos_to_map_index(t_canvas bounds, t_env *env);
t_ivec2			pos_to_map_index(t_canvas bounds, t_ivec2 pos, t_env *env);
t_vec2			mpos_to_map_coord(t_canvas bounds, t_ivec2 mpos, t_env *env);
t_ivec2			map_coord_to_screen(t_env *env, t_vec2 v2);
t_ivec2			get_mouse_pos(void);
void			update_mouse_pos(t_env *env);

void			draw_canvas_fill(t_sdl *sdl, t_canvas *canvas, t_canvas *parent,
								unsigned int color);
void			draw_canvas_border(t_sdl *sdl, t_canvas canvas, t_canvas parent,
								unsigned int color);

void			sdl_draw_rect(t_env *env, t_canvas rect, int line_h);
void			sdl_draw_circle(t_sdl *sdl, t_ivec2 pos,
								t_float radius, t_u32 color);
void			texdata_draw_circle_filled(t_color *tex, t_canvas anchor,
								t_float radius, t_u32 color);
void			texdata_fill_rect(t_color *tex, t_ivec2 t_size,
								t_canvas rect, t_u32 color);
void			texdata_draw_rect(t_color *tex, t_ivec2 t_size,
								t_canvas rect, t_u32 color);
void			draw_tex(t_env *env, t_tex *tex, t_bool shade,
						t_canvas anchor);
void			draw_tex_color(t_env *env, t_color *tex, t_bool shade,
						t_canvas anchor);
void			put_pixel_inside_canvas(t_sdl *sdl, t_canvas canvas,
								t_ivec2 pos, unsigned int color);

void			button_draw(t_env *env, t_button *button);
void			panel_draw(t_env *env, t_sdl *sdl, t_panel *pan);

void			draw_line(t_env *env, t_ivec2 px1, t_ivec2 px2, t_u32 c);
void			draw_vline(t_env *env, t_ivec2 from, int y2);
void			draw_hline(t_env *env, t_ivec2 from, int x2);
void			paint_bucket_tools(t_env *env, t_ivec2 pos, t_u32 color);

void			env_pick_color_replace(t_env *env, t_ivec2 px);
void			env_set_color(t_env *env, t_u32 color);
void			env_set_canvas(t_env *env, t_canvas canvas);
void			env_unset_canvas(t_env *env);
void			env_set_transparency(t_env *env, t_u32 color);
void			env_unset_transparency(t_env *env);
void			env_change_brush(t_env *env, t_u32 type);

void			mouse_track_update_area(t_env *env);
void			mouse_button_setstate(t_env *env, int button, t_bool state);

void			switch_brush(t_ivec2 mpos, t_env *env);

t_float			snap_f(t_float snap, t_float height);
t_vec2			vec_snap(t_vec2 snap, t_float height);

#endif
