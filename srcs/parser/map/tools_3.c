/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 22:20:22 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 02:47:27 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "ft_input.h"

int			parser_gnl(t_parser *parser)
{
	int		gnl_ret;
	char	*comment;

	free(parser->base_line);
	parser->line = NULL;
	gnl_ret = get_next_line(parser->conf_fd, &parser->base_line);
	if (gnl_ret == 1)
	{
		parser->line_nb++;
		parser->line = parser->base_line;
		if ((comment = ft_strchr(parser->line, '#')))
			*comment = '\0';
		if (!*parser->line)
			return (parser_gnl(parser));
	}
	else
		parser->base_line = NULL;
	return (gnl_ret);
}

char		*get_next_word(t_parser *parser, int (*cmp)(int))
{
	while (!cmp(*parser->line))
	{
		if (ft_iswhitespace(*parser->line))
			parser->line = skip_whitespace(parser->line);
		else if (!*parser->line)
		{
			if (parser_gnl(parser) != 1)
				return (0);
		}
		else
			return (NULL);
	}
	return (parser->line);
}

int			skipchar(t_parser *parser, char c)
{
	while (*parser->line != c)
	{
		if (ft_iswhitespace(*parser->line))
			parser->line = skip_whitespace(parser->line);
		else if (!*parser->line)
		{
			if (parser_gnl(parser) != 1)
				return (ERROR);
		}
		else
			return (ERROR);
	}
	parser->line++;
	return (SUCCESS);
}

size_t		get_next_word_len(t_parser *parser, int (*cmp)(int))
{
	char		*line;
	size_t		len;

	len = 0;
	if ((line = get_next_word(parser, cmp)) == NULL)
		return (0);
	while (line[len] && cmp(line[len]))
		len++;
	parser->line = line;
	return (len);
}
