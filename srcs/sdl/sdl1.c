/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:23:03 by vparis            #+#    #+#             */
/*   Updated: 2019/01/08 23:05:47 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "libft.h"
#include "sdl_m.h"
#include "texture.h"

static int		sdl_init2(t_sdl *sdl, const char *title, int width,
					int height)
{
	if ((sdl->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED, width, height,
		SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI)) == NULL)
	{
		ft_putstr_fd("Window could not be created ! SDL_Error : ", 2);
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	if (sdl_create_screen(sdl, width, height) == ERROR)
		return (ERROR);
	if (tex_load_all(sdl) == ERROR)
	{
		ft_putstr_fd("Can't init textures and sprites\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

int				sdl_init(t_sdl *sdl, const char *title, int width,
					int height)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		ft_putstr_fd("SDL could not initialize ! SDL_Error : ", 2);
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	if (sdl_init2(sdl, title, width, height) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int				sdl_reset(t_sdl *sdl)
{
	if (sdl->z_buffer != NULL)
	{
		free(sdl->z_buffer);
		sdl->z_buffer = NULL;
	}
	tex_destroy_all(sdl);
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->renderer);
	return (SUCCESS);
}

int				sdl_destroy(t_sdl *sdl)
{
	sdl_reset(sdl);
	SDL_DestroyWindow(sdl->window);
	SDL_Quit();
	return (SUCCESS);
}

void			sdl_print_infos(t_sdl *sdl)
{
	SDL_version	compiled;
	SDL_version	linked;

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	ft_putstr("We compiled against SDL version ");
	ft_putnbr(compiled.major);
	ft_putchar('.');
	ft_putnbr(compiled.minor);
	ft_putchar('.');
	ft_putnbr(compiled.patch);
	ft_putstr("\nAnd we are linking against SDL version ");
	ft_putnbr(linked.major);
	ft_putchar('.');
	ft_putnbr(linked.minor);
	ft_putchar('.');
	ft_putnbr(linked.patch);
	ft_putchar('\n');
	if (sdl->window != NULL)
	{
		ft_putstr("Pixel format of the window : ");
		ft_putendl(
			SDL_GetPixelFormatName(SDL_GetWindowPixelFormat(sdl->window)));
	}
}
