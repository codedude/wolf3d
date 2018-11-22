/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:20:25 by vparis            #+#    #+#             */
/*   Updated: 2018/11/22 17:25:23 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL.h"
#include "ft_type.h"

t_color	sdl_get_pixel(SDL_Surface *surface, int x, int y)
{
    int		bpp;
    Uint8	*p;
    t_color	pixel;

    bpp = surface->format->BytesPerPixel;
    p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
    if (bpp == 4)
    	pixel = *(t_color *)p;
    else if (bpp == 1)
		pixel = (t_color)*p;
	else if (bpp == 2)
		pixel = (t_color)(*(Uint16 *)p);
	else if (bpp == 3)
	{
		if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
        	pixel = p[0] << 16 | p[1] << 8 | p[2];
    	else
        	pixel = p[0] | p[1] << 8 | p[2] << 16;
	}
	else
		pixel = 0;
    return (pixel);
}
