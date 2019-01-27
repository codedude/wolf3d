/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paint_bucket_tools.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 00:14:25 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 20:10:38 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"
#include "algo.h"

static int			pbucket_flood_cond(t_flood_d *f_data, t_ivec2 px)
{
	t_sdl			*sdl;
	t_color_pick	*cpick;
	t_color			c;

	sdl = (t_sdl*)(((void **)f_data->param)[0]);
	cpick = (t_color_pick*)(((void **)f_data->param)[1]);
	c = sdl_pixel_pick_from_img(sdl, px.x, px.y);
	return (0 <= px.x && px.x < sdl->width
		&& 0 <= px.y && px.y < sdl->height
		&& c.rgba == cpick->replace.rgba);
}

static void			pbucket_flood_act(t_flood_d *f_data, t_ivec2 px)
{
	t_sdl			*sdl;
	t_color_pick	*cpick;

	sdl = (t_sdl*)(((void **)f_data->param)[0]);
	cpick = (t_color_pick*)(((void **)f_data->param)[1]);
	sdl_put_pixel(sdl, px.x, px.y, cpick->current);
}

void				paint_bucket_tools(t_sdl *sdl, t_color_pick *cpick,
						t_ivec2 pos)
{
	void		*pb_data[2];
	t_flood_d	fl_data;

	pb_data[0] = sdl;
	pb_data[1] = cpick;
	cpick_pick_color_replace(sdl, cpick, pos);
	if (cpick->current.rgba == cpick->replace.rgba)
		return ;
	fl_data = FLOOD_D_INIT(pbucket_flood_cond, pbucket_flood_act, pb_data);
	ft_flood(&fl_data, pos);
}
