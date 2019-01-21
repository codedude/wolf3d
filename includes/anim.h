/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:11:31 by vparis            #+#    #+#             */
/*   Updated: 2019/01/21 17:16:24 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_H
# define ANIM_H

# include "ft_type.h"
# include "types.h"
# include "sdl_m.h"
# include "entity.h"

# define ANIM_DOOR_OFFSET	0.015
# define ANIM_DOOR_SPEED	1

typedef struct s_env		t_env;
typedef struct s_anim		t_anim;
typedef enum e_anim_type	t_anim_type;
typedef struct s_list_anim	t_list_anim;

enum {
	ANIM_NONE = 0x00,
	ANIM_DOOR = 0x01,
	ANIM_SKYBOX = 0x02,
	ANIM_TEXTURE = 0x04,
	ANIM_LOOP = 0x0100,
	ANIM_ONCE = 0x0200,
};

# define ANIM_MASK_TYPE 0xff
# define ANIM_MASK_LOOP 0xff00

struct				s_anim {
	t_entity		*entity;
	int				type;
	t_bool			to_del;
	struct {
		int			speed;
		int			counter;
	}				key;
};

struct				s_list_anim {
	t_anim			*value;
	t_list_anim		*next;
};

t_anim				*anim_new(t_entity *entity, int type, t_bool to_del,
						int key_speed);
void				anim_destroy(t_anim *anim);

t_list_anim			*alist_new(t_anim *value);
int					alist_push(t_list_anim **head, t_anim *entry);
void				alist_del_elem(t_list_anim **head);
void				alist_del(t_list_anim **head, t_list_anim *entry);
void				alist_clear(t_list_anim **head);

void				compute_anim(t_env *env, t_list_anim **head);
t_bool				anim_door(t_env *env, t_anim *anim);
t_bool				anim_object(t_sdl *sdl, t_anim *anim);
t_bool				anim_texture(t_sdl *sdl, t_anim *anim);
t_bool				anim_skybox(t_sdl *sdl, t_anim *anim);
t_bool				anim_wall(t_sdl *sdl, t_anim *anim);

#endif
