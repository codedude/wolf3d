/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_m.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:24:09 by vparis            #+#    #+#             */
/*   Updated: 2019/01/25 10:35:31 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_M_H
# define SDL_M_H

# include "SDL.h"
# include "SDL_mixer.h"
# include "SDL_image.h"
# include "SDL_ttf.h"
# include "types.h"

/*
** forward declaration
*/

# define KEY_ESCAPE		SDLK_ESCAPE
# define KEY_FPS		SDLK_1
# define KEY_SAVE		SDLK_2
# define KEY_RELOAD		SDLK_3
# define KEY_SEPIA		SDLK_4
# define KEY_BW			SDLK_5
# define KEY_SPEED		SDLK_6
# define KEY_MODE		SDLK_SPACE

typedef struct s_env	t_env;
typedef struct s_text	t_text;
typedef struct s_tex	t_tex;
typedef struct s_sdl	t_sdl;

/*
** TEXTURE
*/

/*
** w and h = size of ONE sprite
** n_sprites = total nb of sprites in the texture
*/

# define TEX_WALL_FILE		"data/texture/textures.conf"
# define TEX_SPRITE_FILE	"data/sprite/sprites.conf"
# define TEX_SKYBOX_FILE	"data/skybox.png"

struct				s_tex {
	t_pixel			**pixels;
	int				w;
	int				h;
	int				n_sprites;
	int				n_cols;
};

int					tex_load(t_tex *tex, char *filename, int n_sprites,
						int n_cols);
int					tex_load_all(t_sdl *sdl);
void				tex_destroy_all(t_sdl *sdl);
void				tex_destroy_pixels(t_tex *tex);
t_tex				*tex_get_wall(t_sdl *sdl, int id);
t_tex				*tex_get_sprite(t_sdl *sdl, int id);

/*
** TEXT
*/

# define FONT_PATH "data/font/monofonto.ttf"

struct				s_text {
	t_tex			font_little;
	t_tex			font_big;
};

int					text_init(t_text *text);
void				text_destroy(t_text *text);
int					text_error(char *info);
void				*text_error_null(char *info);

int					text_load_all(t_text *text);
void				text_write(t_env *env, int x, int y, char *str);


typedef struct		s_sdl {
	t_tex			*tex_walls;
	t_tex			*tex_sprites;
	t_tex			tex_skybox;
	t_text			text;
	int				tex_wall_nb;
	int				tex_sprite_nb;
	t_float			canvas_h;
	t_float			half_canvas_h;
	unsigned char	*image;
	int				pitch;
	int				bpp;
	t_float			*z_buffer;
	t_float			canvas_w;
	t_float			ratio_y;
	t_float			deltatime;
	int				fps;
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
void				sdl_get_fps(t_sdl *sdl);

/*
** sdl_load_image.c
*/

SDL_Surface			*sdl_load_image(char *filename);
int					sdl_convert_data(t_tex *tex, SDL_Surface *surf);

#endif
