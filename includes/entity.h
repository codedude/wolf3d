/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entity.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:49:30 by vparis            #+#    #+#             */
/*   Updated: 2019/02/04 14:15:23 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_H
# define ENTITY_H

# include "ft_type.h"
# include "types.h"

# define DOOR_NS	1
# define DOOR_EW	0

typedef struct s_entity		t_entity;
typedef struct s_entity		t_wall;
typedef struct s_brick		t_brick;
typedef struct s_door		t_door;
typedef struct s_object		t_object;

typedef enum e_entity_type	t_entity_type;

enum				e_entity_type {
	ENTITY_VOID, ENTITY_WALL, ENTITY_BRICK, ENTITY_DOOR, ENTITY_OBJECT,
	ENTITY_SKYBOX, ENTITY_NONE
};

/*
** Represent a bloc (aka wall)
*/

struct				s_entity {
	int				tex_id;
	int				tex_key;
	t_ivec3			tex_calc;
	int				crossable;
	int				id;
	t_entity_type	type;
	union {
		t_brick		*brick;
		t_door		*door;
		t_object	*object;
	}				e;
};

struct				s_norm {
	union {
		int			tweak;
	}				e;
};

/*
** A door is just a wall with special behavior
** tex = texture of the 4 faces -> 0 = default, 1 = half broken
** hp = life of the wall before it breaks
*/

struct				s_brick {
	int				current_hp;
	int				max_hp;
};

/*
** A door is just a wall with special behavior
** tex = sprites -> 0 = door, 1 = side
*/

struct				s_door {
	int				orientation;
	int				tex_wall_id;
	int				item_id;
	t_float			open_offset;
	t_bool			is_active;
	t_bool			is_open;
};

/*
** Represent an objet in the world
** tex = sprite of the object
*/

/*
**	collectable values:
**	1 = is collectable
**	0 = is not collectable
** -1 = is collected
*/

struct				s_object {
	t_vec2			pos;
	t_vec2			size;
	t_float			scale;
	t_float			z;
	t_float			z_buffer;
	int				collectable;
	int				y_start;
	int				y_end;
	int				x_end;
	int				x_start;
	int				x_offset;
	int				y_offset;
};

t_entity			*entity_new(int tex_id, int id, int crossable);
void				entity_destroy(t_entity *entity, t_bool keep_id);
t_brick				*entity_new_brick(int max_hp);
t_door				*entity_new_door(int orientation, int tex_wall_id);
t_object			*entity_new_object(t_vec2 pos, t_vec2 size, t_vec2 scale_z,
						int collectable);
void				entity_merge(t_entity *entity, void *obj,
						t_entity_type type);
void				entity_set_void(t_entity *entity, t_bool keep_id);
void				entity_set_wall(t_entity *entity, int tex_id, int id,
						int crossable);
void				entity_set(t_entity *entity, int tex_id, int id,
						int crossable);

#endif
