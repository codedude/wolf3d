/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:07:37 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 19:28:15 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int		world_content_getarg(t_parser *parser, char *word, int *id)
{
	size_t	wlen;

	if ((wlen = get_next_word_len(parser, ft_isalpha)) == 0
	|| !ft_strnequ(word, parser->line, wlen))
		return (Parse_error);
	parser->line += wlen;
	if (get_and_skipdigit(parser, id) == ERROR
	|| *id >= parser->sdl->tex_wall_nb)
		return (Parse_error);
	return (SUCCESS);
}

static int		get_draw_ceil(t_parser *parser)
{
	if (skipchar(parser, ':') == SUCCESS)
	{
		if (skipword(parser, "True") == SUCCESS)
			parser->map.show_ceil = True;
		else if (skipword(parser, "False") == SUCCESS)
			parser->map.show_ceil = False;
		else
			return (ERROR);
	}
	else
		parser->map.show_ceil = True;
	return (SUCCESS);
}

int				world_content_analyze(t_parser *parser)
{
	if (world_content_getarg(parser, "Floor", &parser->map.floor_id) == ERROR
	|| world_content_getarg(parser, "Ceil", &parser->map.ceil_id) == ERROR
	|| get_draw_ceil(parser) == ERROR)
	{
		parser->err_no = EWGET;
		return (Parse_error);
	}
	if (get_next_clbracket(parser))
		return (Parse_error);
	ft_putstr("World: loaded\n");
	return (Name_entity);
}
