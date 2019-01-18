/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:49:30 by vparis            #+#    #+#             */
/*   Updated: 2019/01/18 16:57:50 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_H
# define TEXTURE_H

# include "sdl_m.h"
# include "types.h"

# define TEX_WALL_FILE		"data/texture/textures.conf"
# define TEX_SPRITE_FILE	"data/sprite/sprites.conf"

/*
** forward declaration
*/

typedef struct s_sdl	t_sdl;

typedef struct s_tex	t_tex;

/*
** w and h = size of ONE sprite
** n_sprites = total nb of sprites in the texture
*/

struct			s_tex {
	t_pixel		**pixels;
	int			w;
	int			h;
	int			n_sprites;
	int			n_cols;
};

int				tex_load(t_tex *tex, char *filename, int n_sprites, int n_cols);
int				tex_load_all(t_sdl *sdl);
void			tex_destroy_all(t_sdl *sdl);
void			tex_destroy_pixels(t_tex *tex);
t_tex			*tex_get_wall(t_sdl *sdl, int id);
t_tex			*tex_get_sprite(t_sdl *sdl, int id);

#endif
