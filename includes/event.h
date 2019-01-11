/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:56:20 by vparis            #+#    #+#             */
/*   Updated: 2019/01/11 14:38:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "types.h"
# include "sdl_m.h"
# include "env.h"

# define ACTION_NONE		0b0
# define ACTION_GROUNDED	0b00001
# define ACTION_WALKING		0b00010
# define ACTION_CROUCHING	0b00100
# define ACTION_FALLING		0b01000
# define ACTION_JUMPING		0b10000
# define ACTION_FLY_MODE	(0x1000)

# define ACTION_MAX_JUMP_TIME	2.5
# define ACTION_JUMP_FORCE		25.0
# define ACTION_FALL_SPEED		25.0

# define ANIM_WALK_UP		(0b0001 << 8)
# define ANIM_WALK_DOWN		(0b0010 << 8)
# define ANIM_WALK			(0b0011 << 8)
# define ANIM_WALK_SPEED	2.2
# define ANIM_WALK_HEIGHT	12

# define ANIM_CROUCH_SPEED	25.0

int						manage_binds(SDL_Event *event, t_env *env);
void					manage_down(const Uint8	*state, t_env *env);

void					update_skybox_offset(t_cam *cam, t_sdl *sdl,
							t_map *map);
t_vec2					vec_rotate(t_vec2 dir, t_float speed);
t_vec2					move_forward(t_env *env, t_vec2 from, t_vec2 to,
							t_float speed);
t_vec2					straf(t_env *env, t_vec2 from, t_vec2 to,
							t_float speed);
t_float					player_speed(int action_state, t_float speed,
							t_float acceleration, t_float factor);
void					player_set_z(t_cam *player);
void					player_set_anim(t_cam *player);
void					player_set_acceleration(t_cam *player);
void					player_jump(t_cam *player);
void					player_fall(t_cam *player);
void					update_player(t_env *env);

#endif
