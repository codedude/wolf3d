/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:21:29 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 14:25:40 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "entity.h"

int		check_spawn(t_parser_map *map, t_parser *parser)
{
	int		check;

	if (map->spawn.x < 0 || map->spawn.x >= map->width
	|| map->spawn.y < 0 || map->spawn.y >= map->height)
		check = 1;
	else if (map->data[map->spawn.y][map->spawn.x].type != ENTITY_VOID)
		check = 2;
	else
		return (SUCCESS);
	parser->line_nb = 0;
	parser->err_no = check == 1 ? ESOOR : ESONW;
	return (ERROR);
}

int		check_tex_id(t_parser *parser, int tex_id)
{
	if (tex_id < 0 || tex_id > parser->sdl->tex_wall_nb)
	{
		parser->line_nb = 0;
		parser->err_no = EBTEX;
		return (ERROR);
	}
	return (SUCCESS);
}

int		check_door_pos(t_parser *parser, t_parser_map *map, t_ivec2 pos,
							t_door *door)
{
	if ((pos.x == 0 || pos.x == map->width - 1
		|| pos.y == 0 || pos.y == map->height - 1)
		|| door->item_id >= parser->obj.objects_nb)
	{
		parser->line_nb = 0;
		parser->err_no = EDBOR;
		return (ERROR);
	}
	else if (door->item_id < 0)
		door->item_id = -1;
	else
		parser->obj.objects[door->item_id].e.object->collectable = 1;
	return (SUCCESS);
}

t_bool	ent_is_wall(t_parser_map *map, t_ivec2 pos)
{
	if (map->data[pos.y][pos.x].type == ENTITY_WALL)
		return (True);
	return (False);
}
