/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:18:38 by vparis            #+#    #+#             */
/*   Updated: 2018/12/17 13:06:27 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "parser.h"

static int		sdl_load_sprites(t_sdl *sdl, t_stack **stack)
{
	char		*tmp;
	int			i;

	i = 0;
	while (i < sdl->sprites_nb)
	{
		if ((tmp = ft_stackpop(stack)) == NULL)
			return (ERROR);
		if (sdl_load_texture(&sdl->sprites[i].texture, tmp) == ERROR)
		{
			free(tmp);
			return (ERROR);
		}
		free(tmp);
		i++;
	}
	return (SUCCESS);
}

int				sdl_init_sprites(t_sdl *sdl)
{
	t_stack		*stack;
	int			n;

	sdl->sprites = NULL;
	stack = NULL;
	if ((n = read_file(SPRITES_CONF_FILE, &stack)) <= 0
		|| (sdl->sprites =
			(t_sprite *)ft_memalloc((size_t)n * sizeof(t_sprite)))
		== NULL)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	sdl->sprites_nb = n;
	if (sdl_load_sprites(sdl, &stack) == ERROR)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	return (SUCCESS);
}

void			sdl_destroy_sprites(t_sdl *sdl)
{
	int	i;

	if (sdl->sprites == NULL)
		return ;
	i = 0;
	while (i < sdl->sprites_nb)
	{
		free(sdl->sprites[i].texture.data);
		i++;
	}
	free(sdl->sprites);
	sdl->sprites_nb = 0;
	sdl->sprites = NULL;
}
