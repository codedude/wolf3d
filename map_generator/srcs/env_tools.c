/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:15:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/18 05:23:35 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"

void			env_pick_color_replace(t_env *env, t_ivec2 px)
{
	env->cpick.replace = sdl_pixel_pick_from_img(&env->sdl, px.x, px.y);
}

void			env_set_color(t_env *env, t_u32 color)
{
	env->cpick.current.rgba = color;
}

void			env_set_canvas(t_env *env, t_canvas canvas)
{
	env->cpick.canvas_mask = canvas;
	env->cpick.use_canvas = True;
}

void			env_unset_canvas(t_env *env)
{
	env->cpick.use_canvas = False;
}

void			env_set_transparency(t_env *env, t_u32 color)
{
	t_color_pick	*cpick;

	cpick = &env->cpick;
	cpick->use_transparency = True;
	cpick->ignore_c.rgba = color;
}

void			env_unset_transparency(t_env *env)
{
	env->cpick.use_transparency = False;
}
