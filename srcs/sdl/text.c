/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 15:42:18 by vparis            #+#    #+#             */
/*   Updated: 2019/01/18 18:22:37 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "types.h"
#include "libft.h"
#include "ft_type.h"
#include "libft.h"
#include "texture.h"
#include "text.h"

int			text_error(char *info)
{
	ft_putendl_fd(info, 2);
	ft_putendl_fd(TTF_GetError(), 2);
	return (ERROR);
}

void		*text_error_null(char *info)
{
	ft_putendl_fd(info, 2);
	ft_putendl_fd(TTF_GetError(), 2);
	return (NULL);
}

int			text_init(t_text *text)
{
	if (TTF_Init() == -1)
		return (text_error("Can't init TTF"));
	if (text_load_all(text) == ERROR)
		return (text_error("Can't init fonts"));
	return (SUCCESS);
}

void		text_destroy(t_text *text)
{
	tex_destroy_pixels(&text->font_little);
	//tex_destroy_pixels(&text->font_big);
	TTF_Quit();
}

TTF_Font	*text_load_font(char *filename, int font_size)
{
	return (TTF_OpenFont(filename, font_size));
}

int			text_load_all(t_text *text)
{
	TTF_Font	*font;
	SDL_Surface	*surf;
	SDL_Surface	*tmp;

	if ((font = text_load_font("data/font/monofonto.ttf", 50)) == NULL)
		return (text_error("Can't load font"));

	int i = 0;
	int h, w;

	char texte[256];
	i = 0;
	while (i < (127 - 32))
	{
		texte[i] = i + 32;
		++i;
	}
	texte[i] = 0;
	printf("%s\n", texte);

	char t[2];
	t[1] = 0;
	i = 0;
	while (texte[i] != 0)
	{
		t[0] = texte[i];
		TTF_SizeText(font, t, &w, &h);
		printf("%d, %d\n", w, h);
		++i;
	}

	SDL_Color color = {255,255,255,255};
	if ((tmp = TTF_RenderText_Solid(font, texte,
		color)) == NULL)
	{
		ft_putendl_fd("Can't draw test in surface", 2);
		return (ERROR);
	}
	surf = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888, 0);
	SDL_FreeSurface(tmp);
	TTF_SizeText(font, "A", &(text->font_little.w), &(text->font_little.h));
	TTF_CloseFont(font);
	text->font_little.n_sprites = ft_strlen(texte);
	text->font_little.n_cols = text->font_little.n_sprites;
	if (sdl_convert_data(&text->font_little, surf) == ERROR)
		return (ERROR);
	SDL_FreeSurface(surf);
	return (SUCCESS);
}
