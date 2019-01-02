/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:23:03 by vparis            #+#    #+#             */
/*   Updated: 2018/12/27 03:27:39 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "SDL.h"
#include "libft.h"
#include "sdl_m.h"

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
	if (sdl_init_textures(sdl) == ERROR)
	{
		ft_putstr_fd("Can't init textures\n", 2);
		return (ERROR);
	}
	if (sdl_init_sprites(sdl) == ERROR)
	{
		ft_putstr_fd("Can't init sprites\n", 2);
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
	sdl_destroy_textures(sdl);
	sdl_destroy_sprites(sdl);
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyRenderer(sdl->renderer);
	return (SUCCESS);
}

int				sdl_destroy(t_sdl *sdl)
{
	sdl_reset(sdl);
	SDL_DestroyWindow(sdl->window);
	SDL_QuitSubSystem(SDL_INIT_VIDEO);
	SDL_Quit();
	return (SUCCESS);
}

int				sdl_update_texture(t_sdl *sdl)
{
	SDL_LockTexture(sdl->texture, NULL, (void **)&sdl->image, &sdl->pitch);
	return (SUCCESS);
}

int				sdl_render(t_sdl *sdl)
{
	SDL_UnlockTexture(sdl->texture);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
	return (SUCCESS);
}
