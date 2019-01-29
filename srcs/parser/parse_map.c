/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:02:08 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 18:12:38 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "entity.h"

static void		init_parser(t_parser *parser, t_sdl *sdl, int conf_fd)
{
	parser->p_state = Name_entity;
	parser->a_state = Parse_action_default;
	parser->conf_fd = conf_fd;
	parser->err_no = 0;
	parser->line_nb = 0;
	parser->line = NULL;
	parser->base_line = NULL;
	parser->sdl = sdl;
	if (parser_gnl(parser) != 1)
		parser->p_state = Parse_error;
}

static void		print_parser_errno(t_parser *parser, char *header)
{
	static char	*err_msg[ERRMSG_CNT] = { ERRMSG_STR };

	if (header)
		ft_putstr_fd(header, 2);
	if (parser->line_nb > 0)
	{
		ft_putstr_fd("line ", 2);
		ft_putnbr_fd(parser->line_nb, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err_msg[parser->err_no], 2);
}

static int		check_spawn(t_parser_map *map, t_parser *parser)
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

static int		check_tex_id(t_parser *parser, int tex_id)
{
	if (tex_id < 0 || tex_id > parser->sdl->tex_wall_nb)
	{
		parser->line_nb = 0;
		parser->err_no = EBTEX;
		return (ERROR);
	}
	return (SUCCESS);
}

static int		check_door_pos(t_parser *parser, t_parser_map *map, t_ivec2 pos,
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

static t_bool	ent_is_wall(t_parser_map *map, t_ivec2 pos)
{
	if (map->data[pos.y][pos.x].type == ENTITY_WALL)
		return (True);
	return (False);
}

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

static int		clean_info(t_parser *parser)
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

int				parse_map(t_sdl *sdl, t_parser *parser, int conf_fd)
{
	static int	(*action_state[])(t_parser *) = {
		P_CONTENT_FUNCT
	};

	ft_bzero(parser, sizeof(*parser));
	init_parser(parser, sdl, conf_fd);
	while (parser->p_state != Parse_error && parser->p_state != Parse_end)
		parser->p_state = action_state[parser->p_state](parser);
	if (parser->p_state == Parse_error
		|| clean_info(parser) == Parse_error)
	{
		destroy_map_data(&parser->map.data,
			parser->map.width, parser->map.height);
		print_parser_errno(parser, "Wolf3d: ");
		free(parser->base_line);
		return (ERROR);
	}
	return (SUCCESS);
}
