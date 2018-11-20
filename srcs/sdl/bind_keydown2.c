/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_keydown2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 12:22:45 by vparis            #+#    #+#             */
/*   Updated: 2018/05/02 13:23:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "sdl_m.h"
#include <stdlib.h>
#include "libft.h"
#include "env.h"
#include "vec.h"
#include "rt.h"
#include "objects.h"
#include "render.h"
#include "bmp.h"

static t_vec	check_obj_rot(t_vec obj_rot, const Uint8 *state)
{
	if (state[SDL_SCANCODE_UP])
		obj_rot[0] += 1.0;
	if (state[SDL_SCANCODE_DOWN])
		obj_rot[0] -= 1.0;
	if (state[SDL_SCANCODE_RIGHT])
		obj_rot[1] += 1.0;
	if (state[SDL_SCANCODE_LEFT])
		obj_rot[1] -= 1.0;
	if (state[SDL_SCANCODE_Q])
		obj_rot[2] += 1.0;
	if (state[SDL_SCANCODE_E])
		obj_rot[2] -= 1.0;
	return (obj_rot);
}

static t_vec	check_obj_pos(t_vec obj_pos, const Uint8 *state)
{
	if (state[SDL_SCANCODE_D])
		obj_pos[0] += 1.0;
	if (state[SDL_SCANCODE_A])
		obj_pos[0] -= 1.0;
	if (state[SDL_SCANCODE_S])
		obj_pos[2] -= 1.0;
	if (state[SDL_SCANCODE_W])
		obj_pos[2] += 1.0;
	if (state[SDL_SCANCODE_LSHIFT])
		obj_pos[1] += 1.0;
	if (state[SDL_SCANCODE_C])
		obj_pos[1] -= 1.0;
	return (obj_pos);
}

int				manage_object(t_env *env, const Uint8 *state)
{
	t_object	*obj;
	t_vec		obj_pos;
	t_vec		obj_pos_s;
	t_vec		obj_rot;
	t_vec		obj_rot_s;

	if ((obj = env->obj_edit) == NULL)
		return (0);
	obj_pos = obj->pos;
	obj_pos_s = obj_pos;
	obj_rot = obj->rot;
	obj_rot_s = obj_rot;
	obj_pos = check_obj_pos(obj_pos, state);
	obj_rot = check_obj_rot(obj_rot, state);
	if (obj_pos[0] != obj_pos_s[0] || obj_pos[1] != obj_pos_s[1]
		|| obj_pos[2] != obj_pos_s[2]
		|| obj_rot[0] != obj_rot_s[0] || obj_rot[1] != obj_rot_s[1]
		|| obj_rot[2] != obj_rot_s[2])
	{
		env->rt.objects.is_update = 1;
		object_set_pos(obj, obj_pos);
		object_set_matrix(obj, obj_rot);
		return (1);
	}
	return (0);
}
