/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:56:20 by vparis            #+#    #+#             */
/*   Updated: 2018/11/29 22:42:40 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "types.h"
#include "sdl_m.h"
#include "env.h"

# define C_RED			0x00FF0000
# define C_GREEN		0x0000FF00
# define C_BLUE			0x000000FF
# define C_WHITE		0x00FFFFFF
# define C_BLACK		0x00000000
# define C_GREY			0x00999999

#define STEP	0
#define SIDE	1
#define DELTA	2

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
	int					offset;
	int					line_height;
	int					draw_start;
	int					draw_end;
	int					x;
	int					side;
	int					hit;
	int					effect;
}						t_hit_infos;

t_vec2					move_forward(t_map *map, t_vec2 from, t_vec2 to,
							t_float speed);
t_vec2					straf(t_map *map, t_vec2 from, t_vec2 to,
							t_float speed);
t_vec2					vec_rotate(t_vec2 dir, t_float speed);



void					render(t_env *env, t_ivec2 range);
int						start_render(void *data);

int						raycast(t_hit_infos *infos, t_map *map, t_env *env,
							int x);
void					rc_render(t_sdl *sdl, t_cam *cam, t_map *map, t_hit_infos *infos);

#endif
