/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons_f1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:53:29 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 23:40:05 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static void		draw_y_line(t_env *env, int y)
{
	t_color		c;
	t_ivec2		px1;
	int			px2;
	int			i;

	c.rgba = 0x2BD929;
	i = -1;
	while (i < 1)
	{
		px1.x = env->obj.edit.bg_prev.pos.x;
		px1.y = y + i;
		px2 = px1.x + env->obj.edit.bg_prev.size.x;
		cpick_set_color(&env->cpick, c.rgba);
		draw_hline(&env->sdl, &env->cpick, px1, px2);
		i++;
	}
}

static void		draw_obj_selected(t_env *env)
{
	t_object_e	*obj;
	t_canvas	tex_anchor;
	t_panel		*p;

	obj = env->obj.list[env->obj.edit.selected];
	cpick_set_canvas(&env->cpick, env->obj.edit.bg_prev);
	p = env->rpan.p[Object_Panel];
	tex_anchor.size.x = (int)(env->obj.edit.tex_prev.size.x * obj->scale * 0.8);
	tex_anchor.size.y = (int)(env->obj.edit.tex_prev.size.y * obj->scale * 0.8);
	tex_anchor.pos = env->obj.edit.bg_prev.pos;
	tex_anchor.pos += (env->obj.edit.bg_prev.size - tex_anchor.size) / 2;
	tex_anchor.pos.y -= (int)(env->obj.edit.bg_prev.size.y / 2.0 * obj->y_pos);
	if (env->mouse.b1 == True && env->mouse.area == Inspector
	&& env->mouse.button_index == Obj_Preview)
		draw_y_line(env, tex_anchor.pos.y + tex_anchor.size.y / 2);
	cpick_set_transparency(&env->cpick, 0x0);
	draw_tex(&env->sdl, &env->cpick,
		&env->sdl.tex_sprites[obj->id], tex_anchor);
	cpick_unset_transparency(&env->cpick);
	cpick_unset_canvas(&env->cpick);
}

void			inspector_draw_object_edit(t_env *env)
{
	if (env->obj.edit.selected != -1)
		draw_obj_selected(env);
	checkbox_draw(&env->sdl, &env->cpick, env->obj.cbox_solid);
	slider_draw(&env->sdl, &env->cpick, env->obj.g_snap);
}
