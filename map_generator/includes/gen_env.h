/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:24:29 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/20 16:15:32 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_ENV_H
# define GEN_ENV_H

# include "libft.h"
# include "sdl_m.h"

# define MAP_GEN_NAME		"Wolf3d: Editor"

# define EDIT_USAGE			"W3d Editor:\n" EDIT_USAGE1
# define EDIT_USAGE1		"usage -- ./w3d_generator map_name.w3d\n"

/*
**	MAP WIDTH / HEIGHT
*/

# define DEF_SIZE_X			16
# define DEF_SIZE_Y			15
# define MIN_SIZE_X			5
# define MIN_SIZE_Y			5
# define MAX_SIZE_X			64
# define MAX_SIZE_Y			64

/*
**	GRID
*/

# define GRID_OFF_X			5
# define GRID_OFF_Y			5
# define GRID_PERC_X		70

# define GRID_SIZE_X		(GRID_PERC_X - (GRID_OFF_X * 2))
# define GRID_SIZE_Y		(100 - (GRID_OFF_Y * 2))

/*
**	BRUSHES
*/

# define PREV_BOX_PERC		10

# define BRUSH_PAN_SIZE_X	(int)(BRUSH_C_SIZE * 1.5)
# define BRUSH_PAN_SIZE_Y	75

# define BRUSH_PAN_OFF_X	68
# define BRUSH_PAN_OFF_Y	7

# define BRUSH_C_SIZE		10
# define BRUSH_OFF_X		(GRID_PERC_X + GRID_OFF_X)
# define BRUSH_OFF_Y		95

# define OBJ_OFF_X			(92)
# define OBJ_OFF_Y			GRID_OFF_Y
# define OBJ_SIZE_X			7
# define OBJ_SIZE_Y			GRID_SIZE_Y

# define WTEX_OFF_X			(OBJ_OFF_X - (OBJ_SIZE_X + 2))
# define WTEX_OFF_Y			OBJ_OFF_Y
# define WTEX_SIZE_X		OBJ_SIZE_X
# define WTEX_SIZE_Y		OBJ_SIZE_Y

/*
**	BUTTONS
*/

# define BUTTON_SIZE		4
# define BUTTON_TOP_POS_X	(WTEX_OFF_X - (BUTTON_SIZE + 2))
# define BUTTON_TOP_POS_Y	(WTEX_OFF_Y + WTEX_SIZE_Y - BUTTON_SIZE)

# define CANVAS_INIT(x, y)	(t_canvas){x, y}

typedef struct	s_canvas {
	t_ivec2		pos;
	t_ivec2		size;
}				t_canvas;

typedef struct	s_map {
	t_ivec2		size;
	int			**data;
}				t_map;

typedef struct	s_panel {
	t_color		**elem_tex;
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

t_color			*new_texdata(t_texture *tex, t_ivec2 size);
void			draw_tex(t_sdl *sdl, t_color *tex, t_bool shade,
						t_canvas anchor);

t_panel			*new_panel(t_u32 nb_elem, t_canvas anchor, void *param,
						t_color **(*get_elems)(void *, t_ivec2));
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
							t_texture *(*tex_src)(t_sdl*, int));
void			destroy_panel_tex(t_color ***pbox_src, unsigned int nb);

void			panel_draw(t_sdl *sdl, t_panel *pan);

enum			e_user_action {
	Draw_Wall,
	Set_Spawn,
	Erase_Wall,
	Max_action
};

typedef struct	s_button {
	t_canvas	anchor;
	t_color		*tex;
	t_bool		is_active;
	void		*param;
	void		(*on_enable)(void*);
}				t_button;

t_button		*button_new(t_canvas anchor, t_texture *tex, void *param,
						void (*on_enable)(void*));
t_bool			button_hover(t_button *button, t_ivec2 pos);
void			button_draw(t_sdl *sdl, t_button *button);
void			button_setactive(t_button *button, t_bool active);
void			button_destroy(t_button **button);

typedef struct	s_bresenham {
	t_ivec2		v1;
	t_ivec2		v2;
	void		*param;
	void		(*call)(void*, t_ivec2);
}				t_bresenham;

# define BRES_INIT(x, y, z, w)	(t_bresenham){(x), (y), (z), (w)}

typedef struct	s_env {
	t_sdl		sdl;
	t_map		*map;
	t_ivec2		map_pos;
	t_ivec2		map_topleft;
	t_float		ns_zoom;
	t_ivec2		spawn;
	t_button	*act_buttons[Max_action];
	int			user_action;
	int			spawn_rotation;
	t_canvas	grid;
	int			node_size;
	t_float		zoom;
	int			space;
	int			alt;
	int			ctrl;
	int			mouse1;
	int			mouse2;
	int			brush;
	t_panel		*obj_pan;
	t_panel		*brush_pan;
	int			spawner_id;
	char		*save_file;
	int			saved;
}				t_env;

void			toggle_action(t_env *env, int action);

int				env_init(t_env *env, char *filename);
void			env_destroy(t_env *env);
t_map			*create_new_map(t_ivec2 size);
void			destroy_map(t_map *map);
int				sdl_clear_color(t_sdl *sdl, unsigned int color);
void			sdl_put_pixel_safe(t_sdl *sdl, t_ivec2 px, t_color c);


t_bool			is_valid_mapfile(char *filename);
int				save_file(t_env *env);

int				manage_binds(SDL_Event *event, t_env *env);
void			manage_down(const Uint8	*state, t_env *env);

void			draw_grid(t_env *env, t_sdl *sdl);
void			draw_grid_lines(t_env *env, t_sdl *sdl);
t_bool			drawing_node(t_env *env, t_ivec2 mpos, t_ivec2 node);
void			draw_node(t_env *env, t_sdl *sdl, t_ivec2 i);
void			draw_on_map(t_env *env, int brush);

int				ipercent_of(int of, int percent);
t_bool			is_bounded(t_ivec2 pos, t_canvas canvas);
t_canvas		get_map_boundaries(t_env *env);
t_ivec2			map_to_center(t_env *env);
t_ivec2			mpos_to_map_index(t_canvas bounds, t_ivec2 mpos, t_env *env);
t_ivec2			get_mouse_pos(void);

void			draw_canvas_fill(t_sdl *sdl, t_canvas canvas, t_canvas parent,
								unsigned int color);
void			draw_canvas_border(t_sdl *sdl, t_canvas canvas, t_canvas parent,
								unsigned int color);
void			put_pixel_inside_canvas(t_sdl *sdl, t_canvas canvas,
								t_ivec2 pos, unsigned int color);

void			update_c_offset(t_env *env);
void			switch_brush(t_ivec2 mpos, t_env *env);

#endif
