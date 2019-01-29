/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:23:17 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 18:53:20 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "gen_env.h"
#include "entity.h"
#include "types.h"
#include "parser.h"

static void		convert_ent(t_entity *ent, int id)
{
	ent->id = id;
	ent->tex_id--;
	if (ent->type == ENTITY_DOOR)
		ent->e.door->tex_wall_id--;
}

static void		convert_parsed_map(t_env *env, t_map *map, t_parser *parser)
{
	t_ivec2		it;
	t_entity	*ent;
	t_entity	*p_ent;
	int			id;

	map->size = IVEC2_INIT(parser->map.width, parser->map.height);
	it.y = 0;
	while (it.y < map->size.y)
	{
		it.x = 0;
		while (it.x < map->size.x)
		{
			ent = &map->data[it.y][it.x];
			p_ent = &parser->map.data[it.y][it.x];
			id = ent->id;
			ft_memcpy(ent, p_ent, sizeof(*ent));
			convert_ent(ent, id);
			if (ent->type == ENTITY_DOOR && ent->e.door->item_id >= 0)
				env->obj.list[ent->e.door->item_id]->unlock_door = ent;
			it.x++;
		}
		free(parser->map.data[it.y]);
		it.y++;
	}
	free(parser->map.data);
}

static void		convert_parsed_obj(t_env *env, t_parser *parser)
{
	t_objects_tools	*otools;
	t_entity		*ent;
	int				i;

	otools = &env->obj;
	otools->count = 0;
	i = 0;
	while (i < parser->obj.objects_nb)
	{
		ent = &parser->obj.objects[i];
		add_new_object(otools, ent->e.object->pos,
			!ent->crossable, (t_u32)ent->tex_id);
		otools->list[i]->scale = ent->e.object->scale;
		otools->list[i]->y_pos = ent->e.object->z;
		i++;
	}
	free(parser->obj.objects);
}

static void		convert_parsed_data(t_env *env, t_map *map, t_parser *parser)
{
	t_parser_map	*p_map;

	p_map = &parser->map;
	convert_parsed_obj(env, parser);
	convert_parsed_map(env, map, parser);
	env->inspector.world.id[WButton_Floor] = (t_u32)p_map->floor_id;
	env->inspector.world.id[WButton_Ceil] = (t_u32)p_map->ceil_id;
	env->inspector.world.draw_ceil = (t_u32)p_map->show_ceil;
	env->spawn = p_map->spawn;
	env->spawn_rotation = 360 - (int)p_map->spawn_rotation;
	env->loaded = True;
}

int				load_map(t_env *env, char *filename)
{
	int			conf_fd;
	t_parser	parser;
	t_map		*map;

	if ((map = map_new(IVEC2_INIT(DEF_SZ_X, DEF_SZ_Y))) == NULL)
		return (ERROR);
	env->loaded = False;
	env->map_info.map = map;
	if ((conf_fd = open(filename, O_RDONLY | O_NONBLOCK | O_NOFOLLOW)) != -1)
	{
		if (parse_map(&env->sdl, &parser, conf_fd) == SUCCESS)
			convert_parsed_data(env, map, &parser);
		close(conf_fd);
	}
	return (SUCCESS);
}
