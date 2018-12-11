/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_m.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:24:09 by vparis            #+#    #+#             */
/*   Updated: 2018/12/11 18:47:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_M_H
# define SDL_M_H

# include "SDL.h"
# include "types.h"

# define TEXTURES_CONF_FILE	"textures/textures.conf"
# define SPRITES_CONF_FILE	"sprites/sprites.conf"

# define KEY_ESCAPE		SDLK_ESCAPE
# define KEY_FPS		SDLK_1
# define KEY_SAVE		SDLK_2
# define KEY_RELOAD		SDLK_3
# define KEY_SEPIA		SDLK_4
# define KEY_BW			SDLK_5
# define KEY_SPEED		SDLK_6
# define KEY_MODE		SDLK_SPACE

typedef struct		s_texture {
	int				w;
	int				h;
	unsigned int	*data;
}					t_texture;

typedef struct		s_sprite {
	t_texture		texture;
}					t_sprite;

typedef struct		s_sdl {
	t_texture		*textures;
	t_sprite		*sprites;
	t_float			canvas_h;
	t_float			half_canvas_h;
	int				textures_nb;
	int				sprites_nb;
	unsigned int	*image;
	t_float			*z_buffer;
	t_float			canvas_w;
	int				width;
	int				height;
	int				size_line;
	size_t			size_buffer;
	SDL_Texture		*texture;
	SDL_Renderer	*renderer;
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

int					sdl_load_texture(t_texture *texture, char *filename);
int					sdl_init_textures(t_sdl *sdl);
int					sdl_init_sprites(t_sdl *sdl);
void				sdl_destroy_textures(t_sdl *sdl);
void				sdl_destroy_sprites(t_sdl *sdl);

/*
** sdl4.c
*/

t_color				sdl_get_pixel(t_texture *text, int x, int y);
void				get_fps(int show_fps);

#endif
