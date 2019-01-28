/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_f1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:53:29 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 23:17:26 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void		draw_gizmos(t_env *env, t_canvas tex_anchor)
{
	t_ivec2		px1;
	int			px2;

	if (env->mouse.b1 == True && env->mouse.area == Inspector
	&& env->mouse.button_index == Obj_Preview)
	{
		cpick_set_color(&env->cpick, 0x2BD929);
		px1.x = env->obj.edit.bg_prev.pos.x;
		px1.y = tex_anchor.pos.y + tex_anchor.size.y;
		px1.y -= (env->obj.edit.tex_prev.size.y * 0.6) / 2;
		px2 = px1.x + env->obj.edit.bg_prev.size.x;
		if (px1.y >= env->obj.edit.bg_prev.pos.y
		&& px1.y < env->obj.edit.bg_prev.pos.y + env->obj.edit.bg_prev.size.y)
			draw_hline(&env->sdl, &env->cpick, px1, px2);
		if (env->ctrl)
		{
			px1.x += env->obj.edit.bg_prev.size.x / 2;
			px1.y =  env->obj.edit.bg_prev.pos.y;
			px2 = px1.y + env->obj.edit.bg_prev.size.y - 4;
			draw_vline(&env->sdl, &env->cpick, px1, px2);
		}
	}
}

static void		draw_obj_selected(t_env *env)
{
	t_color_pick	*cpick;
	t_object_e		*obj;
	t_canvas		tex_anchor;
	t_canvas		mask;
	t_panel			*p;

	cpick = &env->cpick;
	obj = env->obj.list[env->obj.edit.selected];
	mask = env->obj.edit.bg_prev;
	mask.size.y = (int)(mask.size.y + env->obj.edit.tex_prev.size.y * 0.9) / 2;
	cpick_set_canvas(cpick, mask);
	p = env->rpan.p[Object_Panel];
	tex_anchor.size.x = (int)(env->obj.edit.tex_prev.size.x * obj->scale * 0.6);
	tex_anchor.size.y = (int)(env->obj.edit.tex_prev.size.y * obj->scale * 0.6);
	tex_anchor.pos = env->obj.edit.bg_prev.pos;
	tex_anchor.pos.x += (env->obj.edit.bg_prev.size.x - tex_anchor.size.x) / 2;
	tex_anchor.pos.y += ((env->obj.edit.bg_prev.size.y
				+ env->obj.edit.tex_prev.size.y * 0.6) / 2) - tex_anchor.size.y;
	tex_anchor.pos.y -= (int)(env->obj.edit.bg_prev.size.y / 2 * obj->y_pos);
	cpick_set_transparency(cpick, 0x0);
	draw_gizmos(env, tex_anchor);
	draw_tex(&env->sdl, cpick, &env->sdl.tex_sprites[obj->id], tex_anchor);
	cpick_unset_transparency(cpick);
	cpick_unset_canvas(cpick);
}

void			inspector_draw_object_edit(t_env *env)
{
	if (env->obj.edit.selected != -1)
		draw_obj_selected(env);
	checkbox_draw(&env->sdl, &env->cpick, env->obj.cbox_solid);
	slider_draw(&env->sdl, &env->cpick, env->obj.g_snap);
}
