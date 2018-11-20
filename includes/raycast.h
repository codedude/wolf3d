/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:56:20 by vparis            #+#    #+#             */
/*   Updated: 2018/11/01 21:39:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"

#define WIDTH 1024
#define HEIGHT 768

# define C_RED			0x00FF0000
# define C_GREEN		0x0000FF00
# define C_BLUE			0x000000FF
# define C_WHITE		0x00FFFFFF
# define C_BLACK		0x00000000
# define C_GREY			0x00999999

typedef int				t_int;
typedef unsigned int	t_uint;
typedef double			t_float;
typedef t_float			t_vec __attribute__((ext_vector_type(2)));
typedef t_float			t_color __attribute__((ext_vector_type(4)));

# define VEC_ZERO		(t_vec){0.0, 0.0}
# define VEC_INIT(a, b)	(t_vec){(a), (b)}
# define COLOR_ZERO		(t_color){0.0, 0.0, 0.0, 0.0}
# define COLOR_INIT(a, b, c, d)	(t_color){(a), (b), (c), (d)}

t_vec					move_forward(t_vec from, t_vec to, t_float speed);
t_vec					straf(t_vec from, t_vec to, t_float speed);
t_vec					vec_rotate(t_vec dir, t_float speed);

typedef struct			s_ray {
	t_vec				pos;
	t_vec				dir;
}						t_ray;

typedef struct			s_player {
	t_vec				pos;
	t_vec				dir;
	t_vec				plane;
	t_float				mov_speed;
	t_float				rot_speed;
}						t_player;

void					raycast(t_sdl *sdl, t_player *player);

#endif
