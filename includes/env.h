/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:39:55 by vparis            #+#    #+#             */
/*   Updated: 2019/01/12 18:46:50 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "libft.h"
# include "libtpool.h"
# include "sdl_m.h"
# include "types.h"
# include "entity.h"
# include "anim.h"

# define THREADS		0
# define TASKS			32
# define WINDOW_NAME	"DAT Wolf3D"

# define MAX_OFFSET		600
# define MAX_DEPTH		30.0
# define EFFECT_MASK			0xff
# define EFFECT_MASK_DEPTH		0xff00
# define EFFECT_MASK_COLOR		0xff0000
# define EFFECT_NONE	0
# define EFFECT_SIDE	0x01
# define EFFECT_DEPTH	0x0100
# define EFFECT_FOG		0x0200
# define EFFECT_WATER	0x0400
# define EFFECT_SEPIA	0x010000
# define EFFECT_BAW		0x020000

# define FOG_AMBIENT	VEC3_INIT(153.0, 211.0, 137.0)
# define WATER_AMBIENT	VEC3_INIT(136.0, 210.0, 208.0)

typedef struct s_cam	t_cam;
typedef struct s_map	t_map;
typedef struct s_algo	t_algo;
typedef struct s_env	t_env;

struct				s_cam {
	t_vec3			(*depth_filter)(t_vec3 color, t_float depth);
	t_vec3			(*color_filter)(t_vec3 color);
	t_vec2			pos;
	t_vec2			dir;
	t_vec2			plane;
	t_float			height;
	t_float			z;
	t_float			z_pos;
	t_float			z_default;
	int				side_filter;
	t_float			mov_speed;
	t_float			acceleration;
	t_float			rot_speed;
	t_float			jump_time;
	t_float			walk_anim;
	int				action_state;
};

struct				s_map {
	t_entity		**data;
	t_entity		*skybox;
	int				floor_id;
	int				ceil_id;
	int				show_ceil;
	t_ivec2			spawn;
	int				width;
	int				height;
};

struct				s_algo {
	t_env			*env;
	int				start;
	int				end;
	int				step;
};

struct				s_env {
	t_tpool			*tpool;
	t_entity		*objects;
	t_list_anim		*anims;
	t_algo			*packs;
	int				objects_nb;
	t_sdl			sdl;
	t_map			map;
	t_cam			cam;
	int				show_fps;
};

int					env_init(t_env *env, char *filename);
void				env_destroy(t_env *env);
int					render_prepare(t_env *env);
void				render_clean(t_env *env);

#endif
