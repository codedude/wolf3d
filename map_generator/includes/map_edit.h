/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_edit.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 16:59:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:03:05 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_EDIT_H
# define MAP_EDIT_H

# include "types.h"
# include "entity.h"
# include "ui.h"

/*
**		MAP WIDTH / HEIGHT
*/

# define DEF_SZ_X			24
# define DEF_SZ_Y			24

# define MIN_SZ_X			5
# define MIN_SZ_Y			5

# define MAX_SZ_X			64
# define MAX_SZ_Y			64

/*
**		Forward declaration
*/

typedef struct s_mprops			t_mprops;

typedef struct s_map			t_map;
typedef struct s_map_info		t_map_info;

typedef struct s_env			t_env;

/*
**		Map Properties
*/

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

struct			s_mprops {
	t_button	*actions[Max_editor_action];
	t_canvas	anchor;
	t_u32		tick;
	t_u32		speed;
};

int				env_create_mprops(t_env *env);

void			mprops_act_scale_up(void *v_env);
void			mprops_act_scale_down(void *v_env);
void			mprops_act_size_x_up(void *v_env);
void			mprops_act_size_y_up(void *v_env);
void			mprops_act_size_x_down(void *v_env);
void			mprops_act_size_y_down(void *v_env);
void			mprops_act_recenter(void *v_env);

/*
**		Map Info
*/

struct			s_map {
	t_ivec2		size;
	t_entity	**data;
};

t_map			*map_new(t_ivec2 size);
void			destroy_map(t_map *map);

struct			s_map_info {
	int			x_draw[MAX_SZ_X + 1];
	int			y_draw[MAX_SZ_Y + 1];
	t_map		*map;
	int			**tmp_data;
	t_vec2		pos;
	t_float		zoom;
	t_float		zoom_min;
	t_float		zoom_max;
	t_vec2		grid_center;
	t_vec2		map_center;
};

int				init_map_info(t_env *env, t_map_info *minf, char *mapfile);
void			destroy_map_info(t_map_info *minf);

t_bool			is_valid_mapfile(char *filename);
int				load_map(t_env *env, char *filename);

void			clear_map(t_map_info *m_inf);

void			map_scale2grid(t_env *env);
void			map_update_center(t_env *env);
void			map_usebrush(t_env *env, int brush);

/*
**		Map Tools
*/

t_canvas		get_map_boundaries(t_env *env);
t_vec2			map_to_center(t_env *env);
t_ivec2			mpos_to_map_index(t_canvas bounds, t_env *env);
t_ivec2			pos_to_map_index(t_canvas bounds, t_ivec2 pos, t_env *env);
t_vec2			mpos_to_map_coord(t_canvas bounds, t_ivec2 mpos, t_env *env);
t_ivec2			map_coord_to_screen(t_env *env, t_vec2 v2);

void			draw_node(t_env *env, t_sdl *sdl, t_map_info *minf, t_ivec2 i);
void			draw_map(t_env *env, t_sdl *sdl);
void			draw_map_obj(t_env *env);

#endif
