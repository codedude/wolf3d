/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:18:38 by vparis            #+#    #+#             */
/*   Updated: 2018/12/17 13:14:23 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "parser.h"

static int		sdl_load_textures(t_sdl *sdl, t_stack **stack)
{
	char		*tmp;
	int			i;

	i = 0;
	while (i < sdl->textures_nb)
	{
		if ((tmp = ft_stackpop(stack)) == NULL)
			return (ERROR);
		if (sdl_load_texture(sdl->textures + i, tmp) == ERROR)
		{
			free(tmp);
			return (ERROR);
		}
		free(tmp);
		i++;
	}
	return (SUCCESS);
}

int				sdl_init_textures(t_sdl *sdl)
{
	t_stack		*stack;
	int			n;

	sdl->textures = NULL;
	stack = NULL;
	if ((n = read_file(TEXTURES_CONF_FILE, &stack)) <= 0
		|| (sdl->textures =
			(t_texture *)ft_memalloc((size_t)n * sizeof(t_texture)))
		== NULL)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	sdl->textures_nb = n;
	if (sdl_load_textures(sdl, &stack) == ERROR)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	return (SUCCESS);
}

void			sdl_destroy_textures(t_sdl *sdl)
{
	int	i;

	if (sdl->textures == NULL)
		return ;
	i = 0;
	while (i < sdl->textures_nb)
	{
		free(sdl->textures[i].data);
		i++;
	}
	free(sdl->textures);
	sdl->textures_nb = 0;
	sdl->textures = NULL;
}
