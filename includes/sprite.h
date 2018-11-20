/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 14:24:09 by vparis            #+#    #+#             */
/*   Updated: 2018/10/25 18:58:26 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPRITE_H
# define SPRITE_H

# include <stdlib.h>
# include "SDL.h"
# include "libft.h"
# include "ft_type.h"
# include "sdl_m.h"

typedef struct		s_sprite_anim {
	SDL_Texture		*texture;
	int				frame;
	int				x_frame;
	int				n_frame;
	int				width;
	int				height;
	int				speed;
}					t_sprite_anim;

t_sprite_anim		*new_sprite_anim(t_sdl *sdl, char *file, int width,
						int height);
void				free_sprite_anim(t_sprite_anim *anim);

#endif
