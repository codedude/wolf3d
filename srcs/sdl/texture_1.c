/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:41:50 by vparis            #+#    #+#             */
/*   Updated: 2019/01/15 17:20:37 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_m.h"
#include "types.h"
#include "texture.h"
#include "parser.h"

int				tex_load(t_tex *tex, char *filename, int n_sprites, int n_cols)
{
	SDL_Surface	*surf;
	SDL_Surface	*tmp;
	int			r;

	if ((tmp = sdl_load_image(filename)) == NULL)
		return (ERROR);
	if ((surf = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888, 0))
		== NULL)
		return (ERROR);
	SDL_FreeSurface(tmp);
	tex->w = surf->w / n_cols;
	tex->h = surf->h / (n_sprites / n_cols
		+ (n_sprites % n_cols != 0 ? 1 : 0));
	tex->n_sprites = n_sprites;
	tex->n_cols = n_cols;
	r = sdl_convert_data(tex, surf);
	SDL_FreeSurface(surf);
	return (r);
}

static int		tex_parse_line(char **line_split, t_tex *tex)
{
	int			params[2];

	if (line_split[0] == NULL)
		return (ERROR);
	if (line_split[1] == NULL)
		params[0] = 1;
	else if (ft_atoi_s(line_split[1], &params[0]) == ERROR || params[0] < 1)
		return (ERROR);
	if (line_split[1] != NULL)
	{
		if (line_split[2] == NULL)
			params[1] = 1;
		else if (ft_atoi_s(line_split[2], &params[1]) == ERROR || params[1] < 1)
			return (ERROR);
	}
	else
		params[1] = 1;
	if (tex_load(tex, line_split[0], params[0], params[1]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int		tex_load_file_content(t_stack **stack, t_tex *tex, int n)
{
	char		*tmp;
	char		**line_split;
	int			i;
	int			r;

	i = 0;
	while (i < n)
	{
		if ((tmp = ft_stackpop(stack)) == NULL)
			return (ERROR);
		line_split = ft_strsplit_whitespaces(tmp);
		free(tmp);
		if (line_split == NULL)
			return (ERROR);
		r = tex_parse_line(line_split, &tex[i]);
		ft_strsplit_free(line_split);
		if (r == ERROR)
			return (ERROR);
		++i;
	}
	return (SUCCESS);
}

int				tex_load_file(char *filename, t_tex **tex,
					int *tex_nb)
{
	t_stack		*stack;
	int			n;

	*tex = NULL;
	stack = NULL;
	if ((n = read_file(filename, &stack)) <= 0
		|| (*tex = (t_tex *)ft_memalloc((size_t)n * sizeof(t_tex))) == NULL)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	*tex_nb = n;
	if (tex_load_file_content(&stack, *tex, n) == ERROR)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	return (SUCCESS);
}

int				tex_load_all(t_sdl *sdl)
{
	if (tex_load_file(TEX_WALL_FILE, &sdl->tex_walls, &sdl->tex_wall_nb)
		== ERROR)
		return (ERROR);
	if (tex_load_file(TEX_SPRITE_FILE, &sdl->tex_sprites,
			&sdl->tex_sprite_nb) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
