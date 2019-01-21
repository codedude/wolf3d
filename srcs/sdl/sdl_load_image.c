/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_load_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 13:07:22 by vparis            #+#    #+#             */
/*   Updated: 2019/01/21 16:22:56 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "SDL_image.h"
#include "libft.h"
#include "sdl_m.h"
#include "env.h"
#include "parser.h"

SDL_Surface				*sdl_load_image(char *filename)
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

int						sdl_convert_data(t_tex *tex, SDL_Surface *surf)
{
	Uint8		*pixels;
	Uint8		*p;
	int			x;
	int			y;
	int			i;

	if ((tex->pixels = (t_pixel **)malloc(sizeof(t_pixel *)
		* (size_t)tex->n_sprites)) == NULL)
		return (ERROR);
	pixels = (Uint8 *)surf->pixels;
	i = 0;
	while (i < tex->n_sprites)
	{
		if ((tex->pixels[i] = (t_pixel *)malloc(sizeof(t_pixel)
			* (size_t)(tex->h * tex->w))) == NULL)
			return (ERROR);
		y = 0;
		while (y < tex->h)
		{
			x = 0;
			while (x < tex->w)
			{
				p = pixels + (y + i / tex->n_cols * tex->h) * surf->pitch
				+ (x + i % tex->n_cols * tex->w) * surf->format->BytesPerPixel;
				tex->pixels[i][x + y * tex->w] =
						(t_pixel)(p[0] << 16 | p[1] << 8 | p[2]);
				++x;
			}
			++y;
		}
		++i;
	}
	return (SUCCESS);
}
