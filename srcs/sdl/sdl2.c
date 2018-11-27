/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:23:17 by vparis            #+#    #+#             */
/*   Updated: 2018/11/27 15:22:19 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "libft.h"
#include "sdl_m.h"

int			sdl_create_renderer(t_sdl *sdl)
{
	if ((sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		ft_putstr("Renderer could not be created ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, 255);
	return (SUCCESS);
}

int			sdl_create_texture(t_sdl *sdl)
{
	if ((sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
		SDL_TEXTUREACCESS_STATIC, sdl->width, sdl->height)) == NULL)
	{
		ft_putstr("Texture could not be created ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	return (SUCCESS);
}

int			sdl_create_buffer(t_sdl *sdl)
{
	sdl->size_line = sdl->width * sizeof(t_u32);
	sdl->size_buffer = sdl->height * sdl->size_line;
	if ((sdl->image = (t_color *)malloc(sdl->size_buffer)) == NULL)
	{
		ft_putendl("Image buffer cannot be created !");
		return (ERROR);
	}
	if ((sdl->z_buffer = (t_float *)malloc(sdl->width * sizeof(t_float)))
		== NULL)
	{
		ft_putendl("Z buffer cannot be created !");
		return (ERROR);
	}
	return (SUCCESS);
}

int			sdl_create_screen(t_sdl *sdl, int width, int height)
{
	sdl->width = width;
	sdl->height = height;
	if (sdl_create_renderer(sdl) == ERROR
		|| sdl_create_texture(sdl) == ERROR
		|| sdl_create_buffer(sdl) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int			sdl_resize(t_sdl *sdl, int width, int height)
{
	sdl_reset(sdl);
	SDL_SetWindowSize(sdl->window, width, height);
	if (sdl_create_screen(sdl, width, height) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
