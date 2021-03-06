/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:55:19 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:07:05 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

int				world_ent_analyze(t_parser *parser)
{
	if (parser->a_state & Parse_action_world)
	{
		parser->err_no = EWDEF;
		return (ERROR);
	}
	if (get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_world;
	return (World_parsing);
}

static int		get_obj_type_name(t_parser *parser, size_t wlen)
{
	static char	*name[P_ENT_COUNT] = {
		P_ENT_TOSTRING
	};
	int			i;

	i = 0;
	while (i < P_ENT_COUNT)
	{
		if (wlen == ft_strlen(name[i])
		&& ft_strnequ(name[i], parser->line, wlen))
		{
			parser->line += wlen;
			return (i);
		}
		i++;
	}
	return (-1);
}

int				name_ent_analyze(t_parser *parser)
{
	static int		(*ent_funct[P_ENT_COUNT])(t_parser *) = {
		P_ENT_FUNCT
	};
	size_t			wlen;
	int				i;

	if ((wlen = get_next_word_len(parser, ft_isalpha)) == 0
	|| (i = get_obj_type_name(parser, wlen)) == -1)
		return (Parse_end);
	return (ent_funct[i](parser));
}

int				spawn_ent_analyze(t_parser *parser)
{
	if (parser->a_state & Parse_action_spawn)
	{
		parser->err_no = ESDEF;
		return (Parse_error);
	}
	if (get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_spawn;
	return (Spawn_parsing);
}
