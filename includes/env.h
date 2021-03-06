/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:39:55 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 15:04:52 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "libtpool.h"
# include "sdl_m.h"
# include "audio.h"
# include "types.h"
# include "entity.h"
# include "anim.h"
# include "camera.h"
# include "player.h"

# define THREADS		0
# define TASKS			32
# define WINDOW_NAME	"DAT Wolf3D"

# define WINDOW_WIDTH	1280
# define WINDOW_HEIGHT	720

typedef struct s_map	t_map;
typedef struct s_algo	t_algo;
typedef struct s_env	t_env;

struct				s_map {
	t_entity		**data;
	t_entity		*skybox;
	int				floor_id;
	int				ceil_id;
	int				show_ceil;
	t_ivec2			spawn;
	t_float			spawn_rotation;
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
	t_player		player;
	t_audio			audio;
	int				show_fps;
};

int					env_init(t_env *env, char *filename);
void				env_destroy(t_env *env);
int					wolf_init(t_env *env, char *filename);
void				wolf_destroy(t_env *env, t_map *map);

int					load_map(t_env *env, t_map *map, char *mapfile);
void				map_destroy(t_map *map);

int					render_prepare(t_env *env);
void				render_clean(t_env *env);

#endif
