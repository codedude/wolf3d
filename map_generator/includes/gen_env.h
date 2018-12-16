/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:24:29 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 01:58:55 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_ENV_H
# define GEN_ENV_H

# include "libft.h"
# include "sdl_m.h"

# define MAP_GEN_NAME		"Wolf3d: Map generator"

# define EDIT_USAGE			"W3d Editor:\n" EDIT_USAGE1
# define EDIT_USAGE1		"usage -- ./w3d_generator map_name.w3d\n"

# define DEF_SIZE_X			16
# define DEF_SIZE_Y			15
# define MIN_SIZE_X			5
# define MIN_SIZE_Y			5
# define MAX_SIZE_X			64
# define MAX_SIZE_Y			64

# define GRID_OFF_X			5
# define GRID_OFF_Y			5
# define GRID_PERC_X		70

# define PREV_BOX_PERC		10

# define BRUSH_PAN_SIZE_X	15
# define BRUSH_PAN_SIZE_Y	75

# define BRUSH_PAN_OFF_X	75
# define BRUSH_PAN_OFF_Y	7

# define BRUSH_C_SIZE		10
# define BRUSH_OFF_X		95
# define BRUSH_OFF_Y		95

# define CANVAS_INIT(x, y)	(t_canvas){x, y}

typedef struct	s_canvas {
	t_ivec2		pos;
	t_ivec2		size;
}				t_canvas;

typedef struct	s_map {
	t_ivec2		size;
	int			**data;
}				t_map;

typedef struct	s_tex_previewbox {
	struct	s_tex_previewbox	*next;
	t_canvas					canvas;
	t_color						*tex_data;
	int							tex_id;
}				t_tex_pbox;

t_tex_pbox		*new_tex_previewbox(t_sdl *sdl, t_texture *tex, int id);
void			tex_previewbox_add(t_tex_pbox **abox, t_tex_pbox *add);
void			destroy_tex_previewbox(t_tex_pbox *pbox);

typedef struct	s_env {
	t_sdl		sdl;
	t_map		*map;
	t_ivec2		map_pos;
	t_ivec2		spawn;
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
	t_canvas	brush_prev;
	t_tex_pbox	*brush_box;
	t_canvas	brush_canvas;
	int			brush_c_offset;
	int			max_bcoffset;
	int			spawner_id;
	char		*save_file;
	int			saved;
}				t_env;

int				env_init(t_env *env, char *filename);
void			env_destroy(t_env *env);
t_map			*create_new_map(t_ivec2 size);
void			destroy_map(t_map *map);
int				sdl_clear_color(t_sdl *sdl, unsigned int color);


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
