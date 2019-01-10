/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:11:31 by vparis            #+#    #+#             */
/*   Updated: 2019/01/10 18:47:25 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ANIM_H
# define ANIM_H

# include "ft_type.h"
# include "types.h"
# include "texture.h"
# include "entity.h"

# define ANIM_DOOR_OFFSET	0.01
# define ANIM_DOOR_SPEED	1

typedef struct s_anim		t_anim;
typedef enum e_anim_type	t_anim_type;
typedef struct s_list_anim	t_list_anim;

enum				e_anim_type {
	ANIM_LOOP, ANIM_ONCE, ANIM_DESTROY, ANIM_NONE
};

struct				s_anim {
	t_entity		*entity;
	t_anim_type		type;
	struct {
		int			speed;
		int			counter;
	}				key;
};

struct				s_list_anim {
	t_anim			*value;
	t_list_anim		*next;
};

t_anim				*anim_new(t_entity *entity, t_anim_type type,
						int key_speed);
void				anim_destroy(t_anim *anim);

t_list_anim			*alist_new(t_anim *value);
int					alist_push(t_list_anim **head, t_anim *entry);
void				alist_del(t_list_anim **head, t_list_anim *entry);
void				alist_clear(t_list_anim **head);

void				anim_compute(t_sdl *sdl, t_list_anim **head);
t_bool				anim_door(t_anim *anim);
t_bool				anim_object(t_sdl *sdl, t_anim *anim);

#endif
