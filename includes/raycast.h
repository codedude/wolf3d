/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:56:20 by vparis            #+#    #+#             */
/*   Updated: 2019/01/11 14:49:24 by vparis           ###   ########.fr       */
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
# include "texture.h"

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
void					compute_sprites(t_env *env);
void					draw_wall(t_sdl *sdl, t_hit_infos *infos, t_cam *cam,
							t_tex *text);
void					draw_ceil(t_env *env, t_sdl *sdl, t_hit_infos *infos,
							t_vec2 texel);
void					draw_floor(t_env *env, t_sdl *sdl, t_hit_infos *infos,
							t_vec2 texel);
void					rc_render(t_env *env, t_hit_infos *infos);
int						raycast(t_hit_infos *infos, t_map *map, t_env *env,
							int x);

t_vec3					color_filter_baw(t_vec3 c);
t_vec3					color_filter_sepia(t_vec3 c);

t_vec3					depth_filter_depth(t_vec3 color, t_float depth);
t_vec3					depth_filter_fog(t_vec3 c, t_float depth);
t_vec3					depth_filter_water(t_vec3 c, t_float depth);

void					render(t_env *env, int start, int end, int step);

#endif
