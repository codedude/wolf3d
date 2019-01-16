/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/01 17:39:55 by vparis            #+#    #+#             */
/*   Updated: 2019/01/16 15:50:44 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdlib.h>
# include "libft.h"
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
	t_tex			*textures;
	int				textures_nb;
	t_map			map;
	t_cam			cam;
	t_player		player;
	t_audio			audio;
	int				show_fps;
};

int					env_init(t_env *env, char *filename);
void				env_destroy(t_env *env);
int					render_prepare(t_env *env);
void				render_clean(t_env *env);

#endif
