/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:04:55 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/14 18:03:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "env.h"
#include "libft.h"
#include "parser.h"
#include "sdl_m.h"
#include "texture.h"

static int	fill_buffer(char *buff, t_parser *parser)
{
	size_t		wlen;

	if ((wlen = get_next_word_len(parser, is_filechar)) == 0
		|| wlen >= PATH_MAX)
		return (ERROR);
	ft_strncpy(buff, parser->line, wlen);
	buff[wlen] = '\0';
	parser->line += wlen;
	return (SUCCESS);
}

int			load_textures(t_env *env, t_parser *parser)
{
	char		buff[PATH_MAX + 1];
	int			i;

	i = 0;
	while (i < env->textures_nb)
	{
		if ((fill_buffer(buff, parser)) == ERROR
		|| tex_load(env->textures + i, buff, 1, 1) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int			texture_content_analyze(t_env *env, t_parser *parser)
{
	env->textures =
		(t_tex *)ft_memalloc((size_t)env->textures_nb * sizeof(t_tex));
	if (env->textures == NULL || load_textures(env, parser) == ERROR)
	{
		parser->err_no = ETGET;
		return (Parse_error);
	}
	if (get_next_clbracket(parser))
		return (Parse_error);
	ft_putstr("Textures: loaded\n");
	return (Name_entity);
}