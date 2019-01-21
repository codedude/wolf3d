/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:56:20 by vparis            #+#    #+#             */
/*   Updated: 2019/01/21 16:21:36 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <stdio.h>
# include <stdlib.h>
# include "libft.h"
# include "types.h"
# include "sdl_m.h"
# include "env.h"
# include "list.h"

# define C_RED			0x00FF0000
# define C_GREEN		0x0000FF00
# define C_BLUE			0x000000FF
# define C_WHITE		0x00FFFFFF
# define C_BLACK		0x00000000
# define C_GREY			0x00999999

# define STEP	0
# define SIDE	1
# define DELTA	2

typedef struct			s_dist {
	t_vec2				step;
	t_vec2				side;
	t_vec2				delta;
}						t_dist;

typedef struct			s_ray {
	t_vec2				pos;
	t_vec2				dir;
}						t_ray;

typedef struct			s_hit_info {
	t_ray				ray;
	t_vec2				map;
	t_float				z;
	t_float				wall_x;
	t_float				tex_off_x;
	t_entity			*e_door;
	int					offset;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					x;
	int					side;
	int					hit;
	int					is_thin;
}						t_hit_infos;

t_color					dark_color(t_color color, t_cam *cam, int side,
							t_float z);
t_color					get_cf_color(t_tex *text, t_vec2 curr_cf, t_cam *cam,
						t_float z);

int						prepare_sprite(t_env *env, t_klist **lst);
void					compute_sprite(t_env *env);

t_bool					prepare_object(t_env *env, int i, t_vec2 obj_dir,
							t_float obj_x);
void					draw_sprite(t_env *env, t_sdl *sdl, t_entity *obj);

void					get_wall_xz(t_hit_infos *infos, t_vec2 dir,
							t_vec2 dist_step);
void					simu_wall_xz(t_hit_infos *infos, t_vec2 map_tmp,
							t_vec2 dist[3], int side);
t_bool					cmap(int x, int y, int max_x, int max_y);

int						thin_wall_ns(t_vec2 dist[3], t_hit_infos *infos,
							t_map *map, t_door *door);
int						thin_wall_ew(t_vec2 dist[3], t_hit_infos *infos,
							t_map *map, t_door *door);

void					draw_wall(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
							t_entity *e);
void					draw_ceil(t_env *env, t_sdl *sdl, t_hit_infos *infos,
							t_vec2 texel);
void					draw_floor(t_env *env, t_sdl *sdl, t_hit_infos *infos,
							t_vec2 texel);
void					draw_skybox(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
							t_map *map);

void					rc_render(t_env *env, t_hit_infos *infos);

int						raycast(t_hit_infos *infos, t_map *map, t_env *env,
							int x);

t_vec3					color_filter_baw(t_vec3 c);
t_vec3					color_filter_sepia(t_vec3 c);

t_vec3					depth_filter_depth(t_vec3 color, t_float depth);
t_vec3					depth_filter_fog(t_vec3 c, t_float depth);
t_vec3					depth_filter_water(t_vec3 c, t_float depth);

#endif
