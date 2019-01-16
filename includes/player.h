/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:49:30 by vparis            #+#    #+#             */
/*   Updated: 2019/01/16 03:57:50 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "types.h"

# define VEC2_FWD				VEC2_INIT(0.0, 1.0)
# define VEC2_BACK				-VEC2_FWD
# define VEC2_RIGHT				VEC2_INIT(1.0, 0.0)
# define VEC2_LEFT				-VEC2_RIGHT

typedef struct s_player		t_player;
typedef enum e_axis_state	t_axis_state;


enum				e_axis_state {
	Axis_None = 0,
	Axis_Right = (1 << 0),
	Axis_NOT_Right = ~Axis_Right,
	Axis_Left = (1 << 1),
	Axis_NOT_Left = ~Axis_Left,
	Axis_Horizontal = (Axis_Right | Axis_Left),
	Axis_Up = (1 << 2),
	Axis_NOT_Up = ~Axis_Up,
	Axis_Down = (1 << 3),
	Axis_NOT_Down = ~Axis_Down,
	Axis_Vertical = (Axis_Up | Axis_Down),
	Axis_Neg = (Axis_Down | Axis_Left)
};

struct				s_player {
	t_vec2			velocity;
	t_vec2			dash;
	t_float			dash_time;
	t_axis_state	axis_state;
	t_float			mov_speed;
	t_float			acceleration;
	t_float			rot_speed;
	t_float			jump_time;
	t_float			walk_anim;
	t_float			wanim_towards;
	int				action_state;
};

#endif
