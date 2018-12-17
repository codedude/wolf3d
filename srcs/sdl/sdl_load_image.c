/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_load_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 13:07:22 by vparis            #+#    #+#             */
/*   Updated: 2018/12/17 13:10:49 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "parser.h"

static SDL_Surface		*sdl_load_image(char *filename)
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

static unsigned int		*sdl_convert_data(SDL_Surface *surf)
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

int						sdl_load_texture(t_texture *texture, char *filename)
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
