/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:20:25 by vparis            #+#    #+#             */
/*   Updated: 2019/01/08 22:02:57 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "sdl_m.h"
#include "libft.h"
#include "types.h"

void		sdl_put_pixel(t_sdl *sdl, int x, int y, t_color color)
{
	unsigned char	*img;
	int				pos;

	img = sdl->image;
	pos = x * sdl->bpp + y * sdl->pitch;
	img[pos] = color.c.b;
	img[pos + 1] = color.c.g;
	img[pos + 2] = color.c.r;
}

t_color		sdl_get_pixel(t_tex *text, int x, int y)
{
	t_color	pixel;

	pixel.rgba = text->pixels[x + y * text->w];
	return (pixel);
}

void		sdl_get_fps(int show_fps)
{
	static struct timeval	last = {0, 0};
	static int				sum_fps = 60;
	struct timeval			new;

	if (show_fps == 0)
		return ;
	gettimeofday(&new, NULL);
	sum_fps += 1;
	if (new.tv_sec - last.tv_sec >= 1)
	{
		ft_putstr("\r         \rFPS : ");
		ft_putnbr(sum_fps);
		sum_fps = 0;
	}
	last.tv_usec = new.tv_usec;
	last.tv_sec = new.tv_sec;
}

int			sdl_update_texture(t_sdl *sdl)
{
	SDL_LockTexture(sdl->texture, NULL, (void **)&sdl->image, &sdl->pitch);
	return (SUCCESS);
}

int			sdl_render(t_sdl *sdl)
{
	SDL_UnlockTexture(sdl->texture);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
	return (SUCCESS);
}
