/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:41:50 by vparis            #+#    #+#             */
/*   Updated: 2019/01/10 18:21:28 by vparis           ###   ########.fr       */
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
	if ((tex->pixels = sdl_convert_data(surf)) == NULL)
		return (ERROR);
	SDL_FreeSurface(surf);
	return (SUCCESS);
}

static int		tex_load_file_content(t_stack **stack, t_tex *tex, int n)
{
	char		*tmp;
	char		**line_split;
	int			i;
	int			param;
	int			param2;

	i = 0;
	while (i < n)
	{
		if ((tmp = ft_stackpop(stack)) == NULL)
			return (ERROR);
		if ((line_split = ft_strsplit_whitespaces(tmp)) == NULL)
		{
			free(tmp);
			return (ERROR);
		}
		free(tmp);
		if (line_split[0] == NULL)
		{
			ft_strsplit_free(line_split);
			return (ERROR);
		}
		param2 = 1;
		if (line_split[1] == NULL)
			param = 1;
		else if (ft_atoi_s(line_split[1], &param) == ERROR || param < 1)
		{
			ft_strsplit_free(line_split);
			return (ERROR);
		}
		if (line_split[1] != NULL)
		{
			if (line_split[2] == NULL)
				param2 = 1;
			else if (ft_atoi_s(line_split[2], &param2) == ERROR || param < 1)
			{
				ft_strsplit_free(line_split);
				return (ERROR);
			}
		}
		if (tex_load(&tex[i], line_split[0], param, param2) == ERROR)
		{
			ft_strsplit_free(line_split);
			return (ERROR);
		}
		ft_strsplit_free(line_split);
		++i;
	}
	return (SUCCESS);
}

int				tex_load_file(char *filename, t_tex **tex,
					int	*tex_nb)
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

t_tex			*tex_get_wall(t_sdl *sdl, int id)
{
	return (&sdl->tex_walls[id]);
}

t_tex			*tex_get_sprite(t_sdl *sdl, int id)
{
	return (&sdl->tex_sprites[id]);
}

void			tex_destroy_all(t_sdl *sdl)
{
	int	i;

	i = 0;
	while (i < sdl->tex_wall_nb)
	{
		free(sdl->tex_walls[i].pixels);
		++i;
	}
	i = 0;
	while (i < sdl->tex_sprite_nb)
	{
		free(sdl->tex_sprites[i].pixels);
		++i;
	}
	free(sdl->tex_walls);
	free(sdl->tex_sprites);
	sdl->tex_walls = NULL;
	sdl->tex_sprites = NULL;
}
