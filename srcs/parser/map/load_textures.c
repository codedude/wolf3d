/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 22:18:01 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/15 22:48:22 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include "parser.h"

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
		|| sdl_load_texture(env->textures + i, buff) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}
