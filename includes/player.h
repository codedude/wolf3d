/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:49:30 by vparis            #+#    #+#             */
/*   Updated: 2019/01/15 18:25:27 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "types.h"

# define VEC2_FWD				VEC2_INIT(0.0, 1.0)
# define VEC2_BACK				-VEC2_FWD
# define VEC2_RIGHT				VEC2_INIT(1.0, 0.0)
# define VEC2_LEFT				-VEC2_RIGHT

typedef struct s_player	t_player;

struct				s_player {
	t_vec2			velocity;
	t_float			mov_speed;
	t_float			acceleration;
	t_float			rot_speed;
	t_float			jump_time;
	t_float			walk_anim;
	int				action_state;
};

#endif
