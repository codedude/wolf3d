/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:24:09 by vparis            #+#    #+#             */
/*   Updated: 2018/11/27 20:08:37 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "libft.h"
# include "libtpool.h"
# include "sdl_m.h"
# include "ft_type.h"

# define THREADS		0
# define TASKS			16
# define WINDOW_NAME	"DAT Wolf3D"

# define TEX_BASE(x, y)	{(x), "textures/" y, NULL}
# define TEXLAST	{-1, NULL, NULL}
# define TEX_COUNT	6

# define MAX_OFFSET		240
# define MAX_DEPTH		18.0
# define EFFECT_DEPTH	1


typedef struct		s_map {
	int				**data;
	t_ivec2			spawn;
	int				width;
	int				height;
}					t_map;

typedef struct		s_cam {
	t_float			*lookup_table;
	t_vec2			pos;
	t_vec2			dir;
	t_vec2			plane;
	t_float			mov_speed;
	t_float			acceleration;
	t_float			rot_speed;
	t_float			height;
}					t_cam;

typedef struct		s_env {
	t_tpool			*tpool;
	t_sdl			sdl;
	t_map			map;
	t_cam			cam;
	int				show_fps;
	int				effect;
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
