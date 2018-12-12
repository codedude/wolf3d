/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/02 16:18:38 by vparis            #+#    #+#             */
/*   Updated: 2018/12/12 17:34:36 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "parser.h"

static SDL_Surface	*sdl_load_image(char *filename)
{
	SDL_Surface	*surf;

	if (filename == NULL)
		return (NULL);
	if ((surf = IMG_Load(filename)) == NULL)
	{
		ft_putstr("Error : can't load texture from ");
		ft_putendl(filename);
		return (NULL);
	}
	return (surf);
}

unsigned int		*sdl_convert_data(SDL_Surface *surf)
{
	Uint8			*pixels;
	Uint8			*p;
	unsigned int	*data;
	int				x;
	int				y;

	data = (unsigned int *)malloc(sizeof(*data) * (size_t)(surf->w * surf->h));
	if (data == NULL)
		return (NULL);
	pixels = (Uint8 *)surf->pixels;
	y = 0;
	while (y < surf->h)
	{
		x = 0;
		while (x < surf->w)
		{
			p = pixels + y * surf->pitch + x * surf->format->BytesPerPixel;
			data[x + y * surf->w] =
					(unsigned int)(p[0] << 16 | p[1] << 8 | p[2]);
			x++;
		}
		y++;
	}
	return (data);
}

int					sdl_load_texture(t_texture *texture, char *filename)
{
	SDL_Surface	*surf;
	SDL_Surface	*tmp;

	if ((tmp = sdl_load_image(filename)) == NULL)
		return (ERROR);
	if ((surf = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888, 0))
		== NULL)
		return (ERROR);
	SDL_FreeSurface(tmp);
	texture->h = surf->h;
	texture->w = surf->w;
	if ((texture->data = sdl_convert_data(surf)) == NULL)
		return (ERROR);
	SDL_FreeSurface(surf);
	return (SUCCESS);
}

int					sdl_load_textures(t_sdl *sdl, t_stack **stack)
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

int					sdl_init_textures(t_sdl *sdl)
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

int					sdl_load_sprites(t_sdl *sdl, t_stack **stack)
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

int					sdl_init_sprites(t_sdl *sdl)
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

void				sdl_destroy_textures(t_sdl *sdl)
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

void				sdl_destroy_sprites(t_sdl *sdl)
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
