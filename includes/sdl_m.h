/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_m.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:24:09 by vparis            #+#    #+#             */
/*   Updated: 2018/11/20 18:36:01 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_M_H
# define SDL_M_H

# include <stdlib.h>
# include "SDL.h"
# include "libft.h"
# include "ft_type.h"

# define KEY_ESCAPE		SDLK_ESCAPE
# define KEY_FPS		SDLK_1
# define KEY_SAVE		SDLK_2
# define KEY_RELOAD		SDLK_3
# define KEY_SEPIA		SDLK_4
# define KEY_BW			SDLK_5
# define KEY_SPEED		SDLK_6
# define KEY_MODE		SDLK_SPACE

typedef struct		s_textures {
	int				id;
	char			*filename;
	SDL_Surface		*texture;
}					t_textures;

typedef struct		s_sdl {
	t_u32			*image;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
	size_t			width;
	size_t			height;
	size_t			size_line;
	size_t			size_buffer;
	SDL_Window		*window;
}					t_sdl;

/*
** sdl1.c
*/

int					sdl_init(t_sdl *sdl, const char *title, int width,
						int height);
int					sdl_reset(t_sdl *sdl);
int					sdl_destroy(t_sdl *sdl);
int					sdl_render(t_sdl *sdl);
int					sdl_clear(t_sdl *sdl);

/*
** sdl2.c
*/

int					sdl_create_buffer(t_sdl *sdl);
int					sdl_create_texture(t_sdl *sdl);
int					sdl_create_renderer(t_sdl *sdl);
int					sdl_create_screen(t_sdl *sdl, int width, int height);
int					sdl_resize(t_sdl *sdl, int width, int height);

/*
** sdl3.c
*/

int					sdl_init_textures(void);
void				sdl_destroy_textures(void);
SDL_Surface			*sdl_get_texture(int id);

#endif
