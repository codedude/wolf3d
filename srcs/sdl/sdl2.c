/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/01 17:23:17 by vparis            #+#    #+#             */
/*   Updated: 2019/01/31 09:54:26 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "SDL2/SDL.h"
#include "SDL2/SDL_hints.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_video.h"
#include "env.h"
#include "ft_math.h"
#include "ft_type.h"
#include "libft.h"
#include "sdl_m.h"
#include <stdlib.h>

int sdl_create_renderer(t_sdl *sdl) {
	Uint32 flags = SDL_RENDERER_ACCELERATED;
	if (sdl->vsync == True)
		flags |= SDL_RENDERER_PRESENTVSYNC;
	if ((sdl->renderer = SDL_CreateRenderer(sdl->window, -1, flags)) == NULL) {
		ft_putstr("Renderer could not be created ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	SDL_SetRenderDrawColor(sdl->renderer, 255, 255, 255, 255);
	return (SUCCESS);
}

int sdl_toggle_vsync(t_sdl *sdl) {
	if (sdl->vsync == True) {

		SDL_RenderSetVSync(sdl->renderer, 0);
		sdl->vsync = False;
	} else {
		SDL_RenderSetVSync(sdl->renderer, 1);
		sdl->vsync = True;
	}
	return (SUCCESS);
}

int sdl_create_texture(t_sdl *sdl) {
	if ((sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGB888,
	                                      SDL_TEXTUREACCESS_STREAMING,
	                                      sdl->width, sdl->height)) == NULL) {
		ft_putstr("Texture could not be created ! SDL_Error : ");
		ft_putendl(SDL_GetError());
		return (ERROR);
	}
	return (SUCCESS);
}

int sdl_create_buffer(t_sdl *sdl) {
	SDL_LockTexture(sdl->texture, NULL, (void **)&sdl->image, &sdl->pitch);
	sdl->bpp = sdl->pitch / sdl->width;
	sdl->size_buffer = (size_t)(sdl->height * sdl->pitch);
	ft_bzero(sdl->image, sdl->size_buffer);
	SDL_UnlockTexture(sdl->texture);
	if ((sdl->z_buffer =
	         (t_float *)malloc((size_t)sdl->width * sizeof(t_float))) == NULL) {
		ft_putendl("Z buffer cannot be created !");
		return (ERROR);
	}
	return (SUCCESS);
}

/*
** Multiplier le ratio_y pour varier la fov !
** 90 = vue normal
*/

int sdl_create_screen(t_sdl *sdl) {
	sdl->canvas_h = (t_float)sdl->height;
	sdl->canvas_w = (t_float)sdl->width;
	sdl->ratio_y =
	    (sdl->canvas_w / sdl->canvas_h) / 2.0f * atanf(MY_PI / 180.0f * 120.0f);
	sdl->half_canvas_h = sdl->canvas_h / 2.0f;
	sdl->vsync = False;
	if (sdl_create_renderer(sdl) == ERROR || sdl_create_texture(sdl) == ERROR ||
	    sdl_create_buffer(sdl) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

int sdl_resize(t_sdl *sdl, int width, int height, int scale) {
	sdl->width = width;
	sdl->height = height;
	sdl->scale = scale;
	SDL_SetWindowSize(sdl->window, width * scale, height * scale);
	SDL_SetWindowPosition(sdl->window, SDL_WINDOWPOS_CENTERED,
	                      SDL_WINDOWPOS_CENTERED);
	return (SUCCESS);
}

int sdl_inc_window_size(t_sdl *sdl) {
	sdl->scale = clamp_int((sdl->scale + 1) % 7, 1, 6);
	sdl_resize(sdl, sdl->width, sdl->height, sdl->scale);
	return (SUCCESS);
}

int sdl_dec_window_size(t_sdl *sdl) {
	sdl->scale = sdl->scale - 1;
	if (sdl->scale == 0) {
		sdl->scale = 6;
	}
	sdl_resize(sdl, sdl->width, sdl->height, sdl->scale);
	return (SUCCESS);
}
