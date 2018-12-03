/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:20:25 by vparis            #+#    #+#             */
/*   Updated: 2018/12/03 10:53:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "SDL.h"
#include "libft.h"
#include "types.h"

/*
** t_color sdl_get_pixel(SDL_Surface *surface, int x, int y)
** {
**     int     bpp;
**     Uint8   *p;
**     t_color pixel;
**
**     bpp = surface->format->BytesPerPixel;
**     p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;
**     if (bpp == 4)
**         pixel = *(t_color *)p;
**     else if (bpp == 1)
**         pixel = (t_color)*p;
**     else if (bpp == 2)
**         pixel = (t_color)(*(Uint16 *)p);
**     else if (bpp == 3)
**     {
**         if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
**            pixel = (t_color)(p[0] << 16 | p[1] << 8 | p[2]);
**        else
**            pixel = (t_color)(p[0] | p[1] << 8 | p[2] << 16);
**    }
**     else
**         pixel = 0;
**     return (pixel);
** }
*/

t_color	sdl_get_pixel(SDL_Surface *surface, int x, int y)
{
    Uint8	*p;
    t_color	pixel;

    p = (Uint8 *)surface->pixels + y * surface->pitch + x * 3;
	pixel.c = (unsigned int)(p[0] | p[1] << 8 | p[2] << 16);
    return (pixel);
}

void    get_fps(int show_fps)
{
    static struct timeval   last = {0, 0};
    static int              sum_fps = 60;
    struct timeval          new;

    if (show_fps == 0)
        return ;
    gettimeofday(&new, NULL);
    sum_fps += 1;
    if (new.tv_sec - last.tv_sec >= 1)
    {
        ft_putstr("\rFPS : ");
        ft_putnbr(sum_fps);
        sum_fps = 0;
    }
    last.tv_usec = new.tv_usec;
    last.tv_sec = new.tv_sec;
}
