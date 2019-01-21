/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 01:21:17 by vparis            #+#    #+#             */
/*   Updated: 2019/01/21 16:17:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"

t_tex			*tex_get_wall(t_sdl *sdl, int id)
{
	return (&sdl->tex_walls[id]);
}

t_tex			*tex_get_sprite(t_sdl *sdl, int id)
{
	return (&sdl->tex_sprites[id]);
}

void			tex_destroy_pixels(t_tex *tex)
{
	int		i;

	i = 0;
	while (i < tex->n_sprites)
	{
		free(tex->pixels[i]);
		++i;
	}
	free(tex->pixels);
}

void			tex_destroy_all(t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i < sdl->tex_wall_nb)
	{
		tex_destroy_pixels(&sdl->tex_walls[i]);
		++i;
	}
	i = 0;
	while (i < sdl->tex_sprite_nb)
	{
		tex_destroy_pixels(&sdl->tex_sprites[i]);
		++i;
	}
	free(sdl->tex_walls);
	free(sdl->tex_sprites);
	sdl->tex_walls = NULL;
	sdl->tex_sprites = NULL;
}
