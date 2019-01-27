/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:27:34 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 21:49:35 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ui.h"
#include "sdl_m.h"
#include "types.h"
#include "ft_type.h"
#include "libft.h"

static t_color	*create_button_tex(t_tex *tex, t_ivec2 size)
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
			btex[i.x + i.y * size.x].rgba = 0xaaaaaa;
			i.x++;
		}
		i.y++;
	}
	return (btex);
}

t_button		*button_new(t_canvas anchor, t_tex *tex, void *param,
						void (*trigger)(void *))
{
	t_button	*b;

	if (!(b = (t_button*)ft_memalloc(sizeof(*b))))
		return (NULL);
	if (!(b->tex = create_button_tex(tex, anchor.size)))
	{
		free(b);
		return (NULL);
	}
	b->anchor = anchor;
	b->is_active = False;
	b->param = param;
	b->trigger = trigger;
	return (b);
}

void			button_destroy(t_button **button)
{
	t_button	*b;

	b = *button;
	if (!b)
		return ;
	free(b->tex);
	free(b);
	*button = NULL;
}

void			destroy_button_array(t_button **buttons, t_u32 count)
{
	t_u32		i;

	i = 0;
	while (i < count)
	{
		button_destroy(&buttons[i]);
		i++;
	}
}
