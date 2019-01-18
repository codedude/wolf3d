/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:23:16 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/18 04:57:37 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "gen_env.h"
#include "libft.h"

static t_color	*create_button_tex(t_tex *tex, t_ivec2 size, t_u32 c)
{
	t_color		*btex;
	t_ivec2		i;

	if (tex)
		return (new_texdata(tex, size));
	if (!(btex = (t_color*)malloc(sizeof(t_color) * (size_t)(size.x * size.y))))
		return (NULL);
	i.y = 0;
	while (i.y < size.y)
	{
		i.x = 0;
		while (i.x < size.x)
		{
			btex[i.x + i.y * size.x].rgba = c;
			i.x++;
		}
		i.y++;
	}
	return (btex);
}

t_checkbox		*checkbox_new(t_canvas anchor, t_tex *tex)
{
	t_checkbox	*cbox;

	if ((cbox = (t_checkbox*)ft_memalloc(sizeof(*cbox))))
	{
		if ((cbox->tex = create_button_tex(tex, anchor.size, 0x989898)))
			cbox->anchor = anchor;
		else
			checkbox_destroy(&cbox);
	}
	return (cbox);
}

void			checkbox_setup(t_checkbox *cbox, void *param,
					void (*reverse_state)(void*), int (*get_state)(void *))
{
	cbox->param = param;
	cbox->reverse_state = reverse_state;
	cbox->get_state = get_state;
}

t_bool			checkbox_hover(t_checkbox *cbox, t_ivec2 pos)
{
	return (is_bounded(pos, cbox->anchor));
}

void			draw_cross(t_env *env, t_checkbox *cbox)
{
	t_ivec2		px1;
	t_ivec2		px2;

	px1 = cbox->anchor.pos;
	px2 = px1 + cbox->anchor.size;
	draw_line(env, px1, px2, 0xffffff);
	px1.x++;
	px2.y--;
	draw_line(env, px1, px2, 0xffffff);
	px1.x--;
	px1.y++;
	px2.y++;
	px2.x--;
	draw_line(env, px1, px2, 0xffffff);
	px1 = cbox->anchor.pos;
	px2 = px1;
	px1.x += cbox->anchor.size.x;
	px2.y += cbox->anchor.size.y;
	draw_line(env, px1, px2, 0xffffff);
	px1.y++;
	px2.x++;
	draw_line(env, px1, px2, 0xffffff);
	px1 -= 1;
	px2 -= 1;
	draw_line(env, px1, px2, 0xffffff);
}

void			checkbox_draw(t_env *env, t_checkbox *cbox)
{
	int		state;

	state = cbox->get_state(cbox->param);
	draw_tex_color(env, cbox->tex, (state == Unavailable), cbox->anchor);
	if (state == Check)
		draw_cross(env, cbox);
}

void			checkbox_clic(t_checkbox *cbox)
{
	cbox->reverse_state(cbox->param);
}

void			checkbox_destroy(t_checkbox **cbox)
{
	free((*cbox)->tex);
	free(*cbox);
	*cbox = NULL;
}
