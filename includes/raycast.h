/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:56:20 by vparis            #+#    #+#             */
/*   Updated: 2018/11/20 19:14:18 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "env.h"

# define C_RED			0x00FF0000
# define C_GREEN		0x0000FF00
# define C_BLUE			0x000000FF
# define C_WHITE		0x00FFFFFF
# define C_BLACK		0x00000000
# define C_GREY			0x00999999

t_vec2					move_forward(t_map *map, t_vec2 from, t_vec2 to,
							t_float speed);
t_vec2					straf(t_map *map, t_vec2 from, t_vec2 to,
							t_float speed);
t_vec2					vec_rotate(t_vec2 dir, t_float speed);

typedef struct			s_ray {
	t_vec2				pos;
	t_vec2				dir;
}						t_ray;

void					raycast(t_sdl *sdl, t_cam *cam, t_map *map,
							t_ivec2 range);
int						compute_raycast(void *data);

#endif
