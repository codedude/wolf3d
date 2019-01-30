/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkbox.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/27 16:23:16 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:19:44 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "sdl_plus.h"
#include "ui.h"
#include "ft_type.h"
#include "types.h"

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

void			checkbox_destroy(t_checkbox **cbox)
{
	free(*cbox);
	*cbox = NULL;
}
