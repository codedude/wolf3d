/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:04:01 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 17:49:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "entity.h"

static int		get_map_content(t_parser_map *map, t_parser *parser)
{
	t_ivec2		it;
	int			val;
	int			id;

	it.y = 0;
	id = 0;
	while (it.y < map->height)
	{
		it.x = 0;
		while (it.x < map->width)
		{
			if (get_and_skipdigit(parser, &val) == ERROR)
				return (ERROR);
			if (val != 0 && map->data[it.y][it.x].type == ENTITY_VOID)
			{
				entity_set_wall(&map->data[it.y][it.x], val, id, 0);
			}
			++id;
			++it.x;
		}
		it.y++;
		if (it.y != map->height && skipchar(parser, ',') == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

static int		get_door_params(t_parser *parser, t_ivec2 *pos,
					int *tex_id, int *orientation)
{
	if (get_and_skipivec2(parser, pos) == ERROR
	|| get_and_skipdigit(parser, orientation) == ERROR
	|| *orientation < 0 || *orientation > 1
	|| get_and_skipdigit(parser, &tex_id[0]) == ERROR
	|| get_and_skipdigit(parser, &tex_id[1]) == ERROR
	|| get_and_skipsdigit(parser, &tex_id[2]) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static t_bool	ivec2_is_inside(t_ivec2 min, t_ivec2 max, t_ivec2 iv2)
{
	if (iv2.x < min.x || iv2.x >= max.x || iv2.y < min.y || iv2.y >= max.y)
		return (False);
	return (True);
}

static int		get_doors(t_parser_map *map, t_parser *parser)
{
	t_entity	*ent;
	t_door		*door;
	t_ivec2		pos;
	int			tex_id[3];
	int			orientation;

	while (skipword(parser, "Door") == SUCCESS)
	{
		if (get_door_params(parser, &pos, tex_id, &orientation) == ERROR
			|| ivec2_is_inside(IVEC2_ZERO,
				IVEC2_INIT(map->width, map->height) - 1, pos) == False
			|| (door = entity_new_door(orientation, tex_id[1] + 1)) == NULL)
			return (ERROR);
		ent = &map->data[pos.y][pos.x];
		entity_merge(ent, (void *)door, ENTITY_DOOR);
		door->item_id = tex_id[2];
		entity_set(ent, tex_id[0] + 1, pos.x + pos.y * map->width, 0);
	}
	return (SUCCESS);
}

int				map_content_analyze(t_parser *parser)
{
	t_parser_map	*map;

	map = &parser->map;
	if ((map->data = new_map_data(map->width, map->height)) == NULL
	|| get_doors(map, parser) == ERROR
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
