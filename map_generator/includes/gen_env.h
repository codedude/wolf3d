/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gen_env.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:24:29 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/04 00:59:11 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GEN_ENV_H
# define GEN_ENV_H

# include "libft.h"

# define MAP_GEN_NAME		"Wolf3d: Map generator"
# define TEX_COUNT	15
# define DEF_SIZE_X		16
# define DEF_SIZE_Y		15
# define MIN_SIZE_X		5
# define MIN_SIZE_Y		5
# define MAX_SIZE_X		64
# define MAX_SIZE_Y		64

# define GRID_OFF_X		5
# define GRID_OFF_Y		5
# define GRID_PERC_X	70

# define PREV_BOX_PERC	10

# define BRUSH_PAN_SIZE_X	15
# define BRUSH_PAN_SIZE_Y	75

# define BRUSH_PAN_OFF_X	75
# define BRUSH_PAN_OFF_Y	7

# define BRUSH_C_SIZE	10
# define BRUSH_OFF_X	95
# define BRUSH_OFF_Y	95

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

t_tex_pbox		*new_tex_previewbox(t_sdl *sdl, SDL_Surface *tex, int id);
void			tex_previewbox_add(t_tex_pbox **abox, t_tex_pbox *add);
void			destroy_tex_previewbox(t_tex_pbox *pbox);

typedef struct	s_env {
	t_sdl		sdl;
	t_map		*map;
	t_ivec2		map_pos;
	t_canvas	grid;
	int			node_size;
	t_float		zoom;
	int			space;
	int			alt;
	int			mouse1;
	int			mouse2;
	int			brush;
	t_canvas	brush_prev;
	t_tex_pbox	*brush_box;
	t_canvas	brush_canvas;
	int			brush_c_offset;
	int			max_bcoffset;
	int			spawner_id;
}				t_env;

int				ipercent_of(int of, int percent);
t_bool			is_bounded(t_ivec2 pos, t_canvas canvas);
t_canvas		get_map_boundaries(t_env *env);
t_ivec2			get_mouse_pos(void);

#endif
