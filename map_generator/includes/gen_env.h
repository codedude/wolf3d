/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:24:29 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 20:50:28 by jbulant          ###   ########.fr       */
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

void 			palette_init(t_env *env);

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

int				init_rpanels(t_sdl *sdl, t_rpanel *rpan);

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
	int				loaded;
	int				saved;
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

#endif
