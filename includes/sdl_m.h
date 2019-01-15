/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_m.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:24:09 by vparis            #+#    #+#             */
/*   Updated: 2019/01/15 16:14:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_M_H
# define SDL_M_H

# include "SDL.h"
# include "types.h"
# include "texture.h"

/*
** forward declaration
*/

typedef struct s_tex	t_tex;

# define KEY_ESCAPE		SDLK_ESCAPE
# define KEY_FPS		SDLK_1
# define KEY_SAVE		SDLK_2
# define KEY_RELOAD		SDLK_3
# define KEY_SEPIA		SDLK_4
# define KEY_BW			SDLK_5
# define KEY_SPEED		SDLK_6
# define KEY_MODE		SDLK_SPACE

typedef struct		s_sdl {
	t_tex			*tex_walls;
	t_tex			*tex_sprites;
	int				tex_wall_nb;
	int				tex_sprite_nb;
	t_float			canvas_h;
	t_float			half_canvas_h;
	unsigned char	*image;
	int				pitch;
	int				bpp;
	t_float			*z_buffer;
	t_float			canvas_w;
	int				width;
	int				height;
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
void				sdl_print_infos(t_sdl *sdl);

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

int					sdl_update_texture(t_sdl *sdl);
int					sdl_render(t_sdl *sdl);
void				sdl_put_pixel(t_sdl *sdl, int x, int y, t_color color);
t_color				sdl_get_pixel(t_tex *text, int x, int y, int key);
void				sdl_get_fps(int show_fps);

/*
** sdl_load_image.c
*/

SDL_Surface			*sdl_load_image(char *filename);
int					sdl_convert_data(t_tex *tex, SDL_Surface *surf);

#endif
