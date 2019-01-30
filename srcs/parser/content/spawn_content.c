/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spawn_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:07:37 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/21 03:23:01 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int		spawn_get_pos(t_parser *parser)
{
	int		x;
	int		y;

	if (get_and_skipsdigit(parser, &x) == ERROR
	|| get_and_skipsdigit(parser, &y) == ERROR)
		return (Parse_error);
	parser->map.spawn = IVEC2_INIT(x, y);
	return (SUCCESS);
}

static int		spawn_get_rotation(t_parser *parser)
{
	int		r;

	if (get_and_skipsdigit(parser, &r) == ERROR)
		return (Parse_error);
	while (r < 0)
		r += 360;
	parser->map.spawn_rotation = (t_float)(r % 360);
	return (SUCCESS);
}

static int		spawn_content_getarg(t_parser *parser, char *word,
									int (*get)(t_parser *))
{
	size_t	wlen;

	if ((wlen = get_next_word_len(parser, ft_isalpha)) == 0)
		return (Parse_error);
	if (!ft_strnequ(word, parser->line, wlen))
		return (Parse_error);
	parser->line += wlen;
	return (get(parser));
}

int				spawn_content_analyze(t_parser *parser)
{
	if (spawn_content_getarg(parser, "pos", spawn_get_pos) == ERROR
	|| spawn_content_getarg(parser, "dir", spawn_get_rotation) == ERROR)
	{
		parser->err_no = ESGET;
		return (Parse_error);
	}
	if (get_next_clbracket(parser))
		return (Parse_error);
	ft_putstr("Spawn: loaded\n");
	return (Name_entity);
}
