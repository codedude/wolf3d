/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:56:20 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:48:09 by vparis           ###   ########.fr       */
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

t_bool					compute_event(t_env *env);
t_bool					event_kb_poll(SDL_Event *event, t_env *env);
void					event_kb_poll_up(SDL_Event *event, t_cam *cam,
							t_player *player, t_env *env);
void					event_kb_state(const Uint8	*state, t_env *env);
void					switch_effect(t_cam *cam, void *new, int type);
void					binds_open_door(t_env *env, t_cam *cam, t_map *map);
void					update_skybox_offset(t_cam *cam, t_sdl *sdl,
							t_map *map);
t_vec2					vec_rotate(t_vec2 dir, t_float speed);
t_vec2					move_forward(t_env *env, t_vec2 from, t_vec2 to,
							t_float speed);

#endif
