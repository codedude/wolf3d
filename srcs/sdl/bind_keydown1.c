/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bind_keydown1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:31:59 by vparis            #+#    #+#             */
/*   Updated: 2018/05/03 23:05:58 by vparis           ###   ########.fr       */
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

static t_vec	check_angle(t_vec cam_ang, const Uint8 *state, t_env *env)
{
	if (state[SDL_SCANCODE_UP])
		cam_ang[0] += env->speed_ang;
	if (state[SDL_SCANCODE_DOWN])
		cam_ang[0] -= env->speed_ang;
	if (state[SDL_SCANCODE_RIGHT])
		cam_ang[1] += env->speed_ang;
	if (state[SDL_SCANCODE_LEFT])
		cam_ang[1] -= env->speed_ang;
	if (state[SDL_SCANCODE_Q])
		cam_ang[2] += env->speed_ang;
	if (state[SDL_SCANCODE_E])
		cam_ang[2] -= env->speed_ang;
	return (cam_ang);
}

static t_vec	check_pos(t_vec cam_pos, const Uint8 *state, t_env *env)
{
	if (state[SDL_SCANCODE_D])
		cam_pos = cam_pos + matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(env->speed_pos, 0.0, 0.0));
	if (state[SDL_SCANCODE_A])
		cam_pos = cam_pos + matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(-env->speed_pos, 0.0, 0.0));
	if (state[SDL_SCANCODE_S])
		cam_pos = cam_pos + matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(0.0, 0.0, -env->speed_pos));
	if (state[SDL_SCANCODE_W])
		cam_pos = cam_pos + matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(0.0, 0.0, env->speed_pos));
	if (state[SDL_SCANCODE_LSHIFT])
		cam_pos = cam_pos + matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(0.0, env->speed_pos, 0.0));
	if (state[SDL_SCANCODE_C])
		cam_pos = cam_pos + matrix_mul_vec(env->rt.camera.rot,
			VEC_INIT(0.0, -env->speed_pos, 0.0));
	return (cam_pos);
}

static int		manage_camera(t_env *env, const Uint8 *state)
{
	t_vec	cam_pos;
	t_vec	cam_pos_s;
	t_vec	cam_ang;
	t_vec	cam_ang_s;

	cam_pos = camera_get_origin(&env->rt);
	cam_pos_s = cam_pos;
	cam_ang = camera_get_angle(&env->rt);
	cam_ang_s = cam_ang;
	cam_ang = check_angle(cam_ang, state, env);
	cam_pos = check_pos(cam_pos, state, env);
	if (cam_pos[0] != cam_pos_s[0] || cam_pos[1] != cam_pos_s[1]
		|| cam_pos[2] != cam_pos_s[2]
		|| cam_ang[0] != cam_ang_s[0] || cam_ang[1] != cam_ang_s[1]
		|| cam_ang[2] != cam_ang_s[2])
	{
		camera_set_origin(&env->rt, cam_pos);
		camera_set_angle(&env->rt, cam_ang);
		return (1);
	}
	return (0);
}

int				manage_binds_down(t_env *env, int *update, const Uint8 *state)
{
	int		smth_changed;

	smth_changed = 0;
	if (env->mode)
	{
		smth_changed = manage_object(env, state);
		if (smth_changed == -1)
			return (-1);
	}
	else
		smth_changed = manage_camera(env, state);
	if (smth_changed == 1)
		*update = 1;
	return (1);
}
