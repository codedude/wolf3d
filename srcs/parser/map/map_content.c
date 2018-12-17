/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:04:01 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 17:11:59 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parser.h"

static int		get_map_content(t_map *map, t_parser *parser)
{
	t_ivec2		i;
	int			val;

	i.y = 0;
	while (i.y < map->height)
	{
		i.x = 0;
		while (i.x < map->width)
		{
			if (get_and_skipdigit(parser, &val) == ERROR)
				return (ERROR);
			map->data[i.y][i.x] = val;
			i.x++;
		}
		i.y++;
		if (i.y != map->height && skipchar(parser, ',') == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int				map_content_analyze(t_env *env, t_parser *parser)
{
	t_map		*map;

	map = &env->map;
	if (!(map->data = int_new_2darray(map->width, map->height))
	|| get_map_content(map, parser) == ERROR)
	{
		parser->err_no = EMGET;
		return (Parse_error);
	}
	if (get_next_clbracket(parser))
		return (Parse_error);
	ft_putstr("Map: loaded\n");
	return (Name_entity);
}
