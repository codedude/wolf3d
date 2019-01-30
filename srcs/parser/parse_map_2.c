/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:20:15 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 14:21:44 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "entity.h"

static int		check_door(t_parser *parser, t_parser_map *map, t_ivec2 pos)
{
	t_door		*door;
	t_ivec2		pchk[2];

	door = map->data[pos.y][pos.x].e.door;
	if (check_tex_id(parser, door->tex_wall_id) == ERROR
	|| check_door_pos(parser, map, pos, door) == ERROR)
		return (ERROR);
	if (door->orientation == 1)
	{
		pchk[0] = IVEC2_INIT(0, 1);
		pchk[1] = IVEC2_INIT(1, 0);
	}
	else
	{
		pchk[0] = IVEC2_INIT(1, 0);
		pchk[1] = IVEC2_INIT(0, 1);
	}
	if (!ent_is_wall(map, pos - pchk[0]) || !ent_is_wall(map, pos + pchk[0])
	|| (ent_is_wall(map, pos - pchk[1]) && ent_is_wall(map, pos + pchk[1])))
	{
		parser->line_nb = 0;
		parser->err_no = EDWALL;
		return (ERROR);
	}
	return (SUCCESS);
}

static int		check_map_entities(t_parser_map *map, t_parser *parser)
{
	t_ivec2		it;
	t_entity	*ent;

	it.y = 0;
	while (it.y < map->height)
	{
		it.x = 0;
		while (it.x < map->width)
		{
			ent = &map->data[it.y][it.x];
			if (ent->type == ENTITY_WALL)
			{
				if (check_tex_id(parser, ent->tex_id))
					return (ERROR);
			}
			else if (ent->type == ENTITY_DOOR
				&& check_door(parser, map, it) == ERROR)
				return (ERROR);
			it.x++;
		}
		it.y++;
	}
	return (SUCCESS);
}

int				clean_info(t_parser *parser)
{
	if (!(parser->a_state & Parse_action_map)
		|| !(parser->a_state & Parse_action_spawn)
		|| !(parser->a_state & Parse_action_object))
	{
		parser->err_no = EBTYPE;
		return (Parse_error);
	}
	if (check_map_entities(&parser->map, parser) == ERROR
		|| check_spawn(&parser->map, parser) == ERROR)
		return (Parse_error);
	return (SUCCESS);
}
