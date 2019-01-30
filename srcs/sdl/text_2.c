/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:38:30 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:39:26 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "types.h"
#include "libft.h"
#include "ft_type.h"
#include "libft.h"
#include "env.h"

int			text_error(char *info)
{
	ft_putendl_fd(info, 2);
	ft_putendl_fd(TTF_GetError(), 2);
	return (ERROR);
}

void		*text_error_null(char *info)
{
	ft_putendl_fd(info, 2);
	ft_putendl_fd(TTF_GetError(), 2);
	return (NULL);
}

int			text_init(t_text *text)
{
	if (TTF_Init() == -1)
		return (text_error("Can't init TTF"));
	if (text_load_all(text) == ERROR)
		return (text_error("Can't init fonts"));
	return (SUCCESS);
}

void		text_write(t_env *env, int x, int y, char *str)
{
	t_tex	*tex;
	t_color	color;
	int		it_xpad_i[4];

	tex = &(env->sdl.text.font_little);
	ft_bzero(it_xpad_i, 4 * sizeof(int));
	while (str[it_xpad_i[3]] != 0)
	{
		it_xpad_i[0] = 0;
		while (it_xpad_i[0] < tex->w)
		{
			it_xpad_i[1] = -1;
			while (++it_xpad_i[1] < tex->h)
			{
				color = sdl_get_pixel(tex, it_xpad_i[0], it_xpad_i[1],
					str[it_xpad_i[3]] - 32);
				if (color.rgba > 0)
					sdl_put_pixel(&env->sdl, x + it_xpad_i[0] + it_xpad_i[3]
						* tex->w + it_xpad_i[2], y + it_xpad_i[1], color);
			}
			++it_xpad_i[0];
		}
		it_xpad_i[2] += 2;
		++it_xpad_i[3];
	}
}
