/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:49:30 by vparis            #+#    #+#             */
/*   Updated: 2019/01/29 16:41:02 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "types.h"
# include "camera.h"
# include "sdl_m.h"
# include "list.h"

# define VEC2_FWD				VEC2_INIT(0.0f, 1.0f)
# define VEC2_BACK				-VEC2_FWD
# define VEC2_RIGHT				VEC2_INIT(1.0f, 0.0f)
# define VEC2_LEFT				-VEC2_RIGHT

typedef struct s_player		t_player;
typedef enum e_axis_state	t_axis_state;

# define PLAYER_MAXSPEED		3.5f
# define PLAYER_ACCEL			(PLAYER_MAXSPEED * 0.75f)
# define PLAYER_DECEL			(PLAYER_MAXSPEED * 0.75f)
# define PLAYER_STOP_TRESHOLD	0.01f

# define WALKANIM_MAXHEIGHT		15.0f
# define WALKANIM_SPEED			75.0f

# define DASH_LIFETIME			0.25f
# define DASH_SPEED				45.0f

# define ACTION_MAX_JUMP_TIME	0.35f
# define ACTION_JUMP_FORCE		5.0f
# define ACTION_FALL_SPEED		5.0f

# define ACTION_NONE		0b0
# define ACTION_GROUNDED	0b000001
# define ACTION_WALKING		0b000010
# define ACTION_CROUCHING	0b000100
# define ACTION_FALLING		0b001000
# define ACTION_JUMPING		0b010000
# define ACTION_DASHING		0b100000
# define ACTION_FLY_MODE	(0x1000)

# define ANIM_CROUCH_SPEED	2.5f

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
	t_vec2			controller;
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
	t_klist			*inventory;
};

void				compute_player(t_env *env);
void				player_set_dash(t_player *player);
void				player_jump(t_sdl *sdl, t_cam *cam, t_player *player);
void				player_fall(t_sdl *sdl, t_cam *cam, t_player *player,
						t_env *env);
void				player_set_acceleration(t_player *player);
void				player_set_z(t_sdl *sdl, t_cam *cam, t_player *player);
void				player_set_anim(t_sdl *sdl, t_cam *cam, t_player *player,
						t_env *env);
t_float				float_lerp(t_float from, t_float to, t_float t);

#endif
