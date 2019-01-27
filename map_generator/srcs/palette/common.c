/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 20:22:46 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 20:44:58 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"

void			draw_wall(void *v_env, t_ivec2 pos)
{
	t_env	*env;
	int		**tmp_data;
	t_ivec2	size;

	env = (t_env*)v_env;
	tmp_data = env->map_info.tmp_data;
	size = env->map_info.map->size;
	if (pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x)
		return ;
	tmp_data[pos.y][pos.x] = env->palette.brush;
}

static void 	init_brush_fx(t_palette *palette)
{
	palette->b_fx[Pencil] = compute_simple_brush;
	palette->b_fx[Line] = compute_line_tracer;
	palette->b_fx[Horizontal_line] = compute_hline_tracer;
	palette->b_fx[Vertical_line] = compute_vline_tracer;
	palette->b_fx[Square] = compute_square_tracer;
	palette->b_fx[Circle] = compute_circle_tracer;
	palette->b_fx[Paint_Bucket] = compute_bucket_filler;
}

void 			palette_init(t_env *env)
{
	t_palette	*palette;

	palette = &env->palette;
	palette->brush = 0;
	init_brush_fx(palette);
}
