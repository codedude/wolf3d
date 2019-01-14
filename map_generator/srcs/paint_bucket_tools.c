/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bucket_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:14:25 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/11 05:54:06 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"
#include "algo.h"

static int			pbucket_flood_cond(t_flood_d *f_data, t_ivec2 px)
{
	t_env		*env;
	t_sdl		*sdl;
	t_color		c;

	env = (t_env*)f_data->param;
	sdl = &env->sdl;
	c = sdl_pixel_pick_from_img(sdl, px.x, px.y);
	return (0 <= px.x && px.x < sdl->width
		&& 0 <= px.y && px.y < sdl->height
		&& c.rgba == env->cpick.replace.rgba);
}

static void			pbucket_flood_act(t_flood_d *f_data, t_ivec2 px)
{
	t_env		*env;
	t_sdl		*sdl;

	env = (t_env*)f_data->param;
	sdl = &env->sdl;
	sdl_put_pixel(sdl, px.x, px.y, env->cpick.current);
}

void				paint_bucket_tools(t_env *env, t_ivec2 pos, t_u32 color)
{
	t_flood_d	fl_data;

	env_pick_color_replace(env, pos);
	env_set_color(env, color);
	if (env->cpick.current.rgba == env->cpick.replace.rgba)
		return ;
	fl_data = FLOOD_D_INIT(pbucket_flood_cond, pbucket_flood_act, env);
	ft_flood(&fl_data, pos);
}
