/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:42:18 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:40:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "types.h"
#include "libft.h"
#include "ft_type.h"
#include "libft.h"
#include "env.h"

void			text_destroy(t_text *text)
{
	tex_destroy_pixels(&text->font_little);
	tex_destroy_pixels(&text->font_big);
	TTF_Quit();
}

static TTF_Font	*text_load_font(char *filename, int font_size)
{
	return (TTF_OpenFont(filename, font_size));
}

static void		text_init_tab(char texte[96])
{
	int		i;

	i = 0;
	while (i < 95)
	{
		texte[i] = (char)(i + 32);
		++i;
	}
	texte[i] = 0;
}

static int		text_load_font_surf(t_tex *tex, char *filename, int size,
					SDL_Color color)
{
	TTF_Font	*font;
	SDL_Surface	*surf;
	SDL_Surface	*tmp;
	char		texte[96];

	if ((font = text_load_font(filename, size)) == NULL)
		return (text_error("Can't load font"));
	text_init_tab(texte);
	if ((tmp = TTF_RenderText_Solid(font, texte, color)) == NULL)
	{
		ft_putendl_fd("Can't draw test in surface", 2);
		return (ERROR);
	}
	surf = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888, 0);
	SDL_FreeSurface(tmp);
	TTF_SizeText(font, "A", &(tex->w), &(tex->h));
	TTF_CloseFont(font);
	tex->n_sprites = (int)ft_strlen(texte);
	tex->n_cols = tex->n_sprites;
	if (sdl_convert_data(tex, surf) == ERROR)
		return (ERROR);
	SDL_FreeSurface(surf);
	return (SUCCESS);
}

int				text_load_all(t_text *text)
{
	if (text_load_font_surf(&(text->font_little), FONT_PATH, 24,
		(SDL_Color){255, 255, 255, 255}) == ERROR)
		return (ERROR);
	if (text_load_font_surf(&(text->font_big), FONT_PATH, 48,
		(SDL_Color){255, 255, 255, 255}) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
