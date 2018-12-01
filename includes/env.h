/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:24:09 by vparis            #+#    #+#             */
/*   Updated: 2018/12/01 15:18:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "libft.h"
# include "libtpool.h"
# include "sdl_m.h"
# include "types.h"

# define THREADS		1
# define TASKS			1
# define WINDOW_NAME	"DAT Wolf3D"

# define TEX_BASE(x, y)	{(x), "textures/" y, NULL}
# define TEXLAST	{-1, NULL, NULL}
# define TEX_COUNT	15

# define DEFAULT_CEIL	11
# define DEFAULT_FLOOR	11

# define MAX_OFFSET		600
# define MAX_DEPTH		16.0
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

typedef struct		s_map {
	int				**data;
	t_ivec2			spawn;
	int				width;
	int				height;
}					t_map;


# define ACTION_NONE		0b0
# define ACTION_GROUNDED	0b0001// 0x1
# define ACTION_WALKING		0b0010// 0x2
# define ACTION_CROUCHING	0b0100// 0x4
# define ACTION_FALLING		0b1000// 0x8
# define ACTION_FLY_MODE	(0x100)

# define ACTION_MAX_JUMP_TIME	2.5
# define ACTION_JUMP_FORCE		25.0
# define ACTION_FALL_SPEED		25.0

# define ANIM_WALK_UP		(0b0001 << 4)//0x10
# define ANIM_WALK_DOWN		(0b0010 << 4)//0x20
# define ANIM_WALK			(0b0011 << 4)//0x30
# define ANIM_WALK_SPEED	2.2
# define ANIM_WALK_HEIGHT	12	// wrong value, must be relative to sdl->height

# define ANIM_CROUCH_SPEED	25.0

typedef struct		s_cam {
	t_vec3			(*depth_filter)(t_vec3 color, t_float depth);
	t_vec3			(*color_filter)(t_vec3 color);
	t_vec2			pos;
	t_vec2			dir;
	t_vec2			plane;
	t_float			mov_speed;
	t_float			acceleration;
	t_float			rot_speed;
	t_float			height;
	t_float			z;
	t_float			z_pos;
	t_float			z_default;
	t_float			jump_time;
	t_float			walk_anim;
	int				action_state;
	int				side_filter;
}					t_cam;

typedef struct		s_env {
	t_tpool			*tpool;
	t_sdl			sdl;
	t_map			map;
	t_cam			cam;
	int				show_fps;
}					t_env;

typedef struct		s_algo {
	t_env			*env;
	int				start;
	int				end;
}					t_algo;

int					env_init(t_env *env, char *filename);
void				env_destroy(t_env *env);

int					manage_binds(SDL_Event *event, t_env *env);
void				manage_down(const Uint8	*state, t_env *env);

int					load_map(t_map *map, char *mapfile);
void				map_destroy(t_map *map);

#endif
