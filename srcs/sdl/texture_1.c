/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 16:41:50 by vparis            #+#    #+#             */
/*   Updated: 2019/01/25 10:33:45 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "sdl_m.h"
#include "types.h"
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

static int		tex_parse_line(char **line_split, t_tex *tex, int type)
{
	int			params[2];
	char		*path;

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
	if (type == 0)
		path = concat_path_file("data/texture/", line_split[0]);
	else
		path = concat_path_file("data/sprite/", line_split[0]);
	if (path == NULL)
		return (ERROR);
	if (tex_load(tex, path, params[0], params[1]) == ERROR)
		return (ERROR);
	free(path);
	return (SUCCESS);
}

static int		tex_load_file_content(t_stack **stack, t_tex *tex, int n,
					int type)
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
		r = tex_parse_line(line_split, &tex[i], type);
		ft_strsplit_free(line_split);
		if (r == ERROR)
			return (ERROR);
		++i;
	}
	return (SUCCESS);
}

int				tex_load_file(char *filename, t_tex **tex,
					int *tex_nb, int type)
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
	if (tex_load_file_content(&stack, *tex, n, type) == ERROR)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	return (SUCCESS);
}

int				tex_load_all(t_sdl *sdl)
{
	if (tex_load_file(TEX_WALL_FILE, &sdl->tex_walls, &sdl->tex_wall_nb, 0)
		== ERROR)
		return (ERROR);
	if (tex_load_file(TEX_SPRITE_FILE, &sdl->tex_sprites,
			&sdl->tex_sprite_nb, 1) == ERROR)
		return (ERROR);
	if (tex_load(&sdl->tex_skybox, TEX_SKYBOX_FILE, 1, 1) == ERROR)
		return (ERROR);
	return (SUCCESS);
}
