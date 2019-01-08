/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_load_image.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 13:07:22 by vparis            #+#    #+#             */
/*   Updated: 2019/01/08 21:47:29 by vparis           ###   ########.fr       */
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

t_pixel					*sdl_convert_data(SDL_Surface *surf)
{
	Uint8		*pixels;
	Uint8		*p;
	t_pixel		*data;
	int			x;
	int			y;

	data = (t_pixel *)malloc(sizeof(*data) * (size_t)(surf->w * surf->h));
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
					(t_pixel)(p[0] << 16 | p[1] << 8 | p[2]);
			x++;
		}
		y++;
	}
	return (data);
}
