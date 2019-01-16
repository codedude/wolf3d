/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:56:20 by vparis            #+#    #+#             */
/*   Updated: 2019/01/16 04:37:49 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EVENT_H
# define EVENT_H

# include "ft_type.h"
# include "types.h"
# include "sdl_m.h"
# include "env.h"
# include "camera.h"
# include "player.h"

# define ACTION_NONE		0b0
# define ACTION_GROUNDED	0b000001
# define ACTION_WALKING		0b000010
# define ACTION_CROUCHING	0b000100
# define ACTION_FALLING		0b001000
# define ACTION_JUMPING		0b010000
# define ACTION_DASHING		0b100000
# define ACTION_FLY_MODE	(0x1000)

# define ACTION_MAX_JUMP_TIME	2.5
# define ACTION_JUMP_FORCE		21.0
# define ACTION_FALL_SPEED		18.0

# define SPEED_F			1.25
# define SPEED_B			1.0

# define ANIM_CROUCH_SPEED	18.0

t_bool					compute_event(t_env *env);
t_bool					event_kb_poll(SDL_Event *event, t_env *env);
void					event_kb_state(const Uint8	*state, t_env *env);
void					switch_effect(t_cam *cam, void *new, int type);
void					binds_open_door(t_env *env, t_cam *cam, t_map *map);
void					update_skybox_offset(t_cam *cam, t_sdl *sdl,
							t_map *map);
t_vec2					vec_rotate(t_vec2 dir, t_float speed);
t_vec2					move_forward(t_env *env, t_vec2 from, t_vec2 to,
							t_float speed);
int						is_inside(t_float x, t_float min, t_float max);
int						is_close_objects(t_env *env, t_vec2 pos);
void					compute_player(t_env *env);
void					player_jump(t_cam *cam, t_player *player);
void					player_fall(t_cam *cam, t_player *player);
void					player_set_acceleration(t_player *player);
void					player_set_z(t_cam *cam, t_player *player);

#endif
