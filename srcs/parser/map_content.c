/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:04:01 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/14 17:57:23 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parser.h"
#include "entity.h"

static int		get_map_content(t_map *map, t_parser *parser)
{
	t_ivec2		it;
	int			val;

	it.y = 0;
	while (it.y < map->height)
	{
		it.x = 0;
		while (it.x < map->width)
		{
			if (get_and_skipdigit(parser, &val) == ERROR)
				return (ERROR);
			entity_set(&map->data[it.y][it.x], val, val, 0);
			++it.x;
		}
		it.y++;
		if (it.y != map->height && skipchar(parser, ',') == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

int				map_content_analyze(t_env *env, t_parser *parser)
{
	t_map		*map;

	map = &env->map;
	if (!new_map_data(map) || get_map_content(map, parser) == ERROR)
	{
		parser->err_no = EMGET;
		return (Parse_error);
	}
	if (get_next_clbracket(parser))
		return (Parse_error);
	ft_putstr("Map: loaded\n");
	return (Name_entity);
}
