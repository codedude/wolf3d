/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:57:36 by vparis            #+#    #+#             */
/*   Updated: 2019/01/29 16:05:45 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"
#include "types.h"

static void	render(t_env *env, int start, int end, int step)
{
	int			x;
	t_cam		*cam;
	t_hit_infos	infos;

	cam = &env->cam;
	infos.ray.pos = cam->pos;
	x = start;
	while (x < end)
	{
		infos.map = VEC2_INIT(floorf(cam->pos.x), floorf(cam->pos.y));
		infos.ray.dir = cam->dir + -cam->plane *
			((t_float)(x << 1) / env->sdl.canvas_w - 1.0f);
		raycast(&infos, &env->map, env, x);
		rc_render(env, &infos);
		x += step;
	}
}

static int	start_render(void *data)
{
	t_algo		*algo;

	algo = (t_algo *)data;
	render(algo->env, algo->start, algo->end, algo->step);
	return (SUCCESS);
}

static int	make_skybox_anim(t_env *env)
{
	t_anim		*anim;

	if ((anim = anim_new(env->map.skybox, ANIM_SKYBOX | ANIM_LOOP, False, 1))
		== NULL)
		return (ERROR);
	alist_push(&env->anims, anim);
	return (SUCCESS);
}

int			render_prepare(t_env *env)
{
	int			i;
	int			tasks;

	tasks = th_getnbr_proc();
	if ((env->packs = (t_algo *)malloc((size_t)(tasks) * sizeof(t_algo)))
		== NULL)
		return (ERROR);
	i = 0;
	while (i < tasks)
	{
		env->packs[i].env = env;
		env->packs[i].start = i;
		env->packs[i].end = env->sdl.width;
		env->packs[i].step = tasks;
		tp_add_task(env->tpool, &start_render, &env->packs[i]);
		i++;
	}
	if (make_skybox_anim(env) == ERROR)
		ft_putstr_fd("Skybox animation can't be set !\n", 2);
	return (SUCCESS);
}

void		render_clean(t_env *env)
{
	free(env->packs);
	env->packs = NULL;
}
