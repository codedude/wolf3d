/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_analyze_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:55:19 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:14:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

static int		map_ent_paramaters(t_parser_map *map, t_parser *parser)
{
	if (parser->a_state & Parse_action_map)
	{
		parser->err_no = ETDEF;
		return (ERROR);
	}
	if (get_and_skipdigit(parser, &map->width) == ERROR
	|| get_and_skipdigit(parser, &map->height) == ERROR)
	{
		parser->err_no = EMPAR;
		return (ERROR);
	}
	return (SUCCESS);
}

int				map_ent_analyze(t_parser *parser)
{
	if (map_ent_paramaters(&parser->map, parser) == ERROR
	|| get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_map;
	return (Map_parsing);
}

static int		object_ent_paramaters(t_parser_obj *obj, t_parser *parser)
{
	if (parser->a_state & Parse_action_object)
	{
		parser->err_no = EODEF;
		return (ERROR);
	}
	if (get_and_skipdigit(parser, &obj->objects_nb) == ERROR)
	{
		parser->err_no = EOPAR;
		return (ERROR);
	}
	return (SUCCESS);
}

int				object_ent_analyze(t_parser *parser)
{
	if (object_ent_paramaters(&parser->obj, parser) == ERROR
	|| get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_object;
	return (Object_parsing);
}
