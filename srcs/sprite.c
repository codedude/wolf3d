/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 16:52:45 by vparis            #+#    #+#             */
/*   Updated: 2018/10/25 18:06:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include <stdio.h>
# include "SDL.h"
# include "SDL_image.h"
# include "libft.h"
# include "ft_type.h"
# include "sprite.h"

t_sprite_anim		*new_sprite_anim(t_sdl *sdl, char *file, int width, int height)
{
	t_sprite_anim	*tmp;
	SDL_Surface		*surf;

	tmp = (t_sprite_anim *)malloc(sizeof(t_sprite_anim));
	if ((surf = IMG_Load(file)) == NULL)
	{
		ft_putstr("Error : can't load texture from ");
		ft_putendl(file);
		return (NULL);
	}
	tmp->texture = SDL_CreateTextureFromSurface(sdl->renderer, surf);

	tmp->frame = 0;
	tmp->width = width;
	tmp->height = height;
	tmp->speed = 3;
	tmp->x_frame = surf->w / width;
	tmp->n_frame = (surf->h / height) * tmp->x_frame;
	SDL_FreeSurface(surf);
	return (tmp);
}

void				free_sprite_anim(t_sprite_anim *anim)
{
	SDL_DestroyTexture(anim->texture);
	free(anim);
}