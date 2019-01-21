/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/21 05:01:18 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "parser.h"
#include "libft.h"

static void			init_grid(t_env *env, t_sdl *sdl)
{
	env->grid.size.x = ipercent_of(sdl->width, GRID_SIZE_X);
	env->grid.size.y = ipercent_of(sdl->height, GRID_SIZE_Y);
	env->grid.pos.x = ipercent_of(sdl->width, GRID_OFF_X);
	env->grid.pos.y = ipercent_of(sdl->height, GRID_OFF_Y);
}

void				map_update_zoom_range(t_env *env, t_map_info *minf)
{
	t_map 			*map;
	t_float			min[2];
	t_float			max[2];

	map = minf->map;
	min[0] = ipercent_of(env->grid.size.x, 98)
			/ (t_float)(map->size.x);
	max[0] = env->grid.size.x / 2.0;
	min[1] = ipercent_of(env->grid.size.y, 98)
			/ (t_float)(map->size.y);
	max[1] = env->grid.size.y / 2.0;
	if (min[0] < min[1])
	{
		minf->zoom_min = min[0];
		minf->zoom_max = max[0];
	}
	else
	{
		minf->zoom_min = min[1];
		minf->zoom_max = max[1];
	}
}

void				map_scale2grid(t_env *env)
{
	t_map_info		*minf;

	minf = &env->map_info;
	map_update_zoom_range(env, minf);
	minf->zoom = minf->zoom_min;
}

void				map_update_center(t_env *env)
{
	t_map_info		*minf;
	t_map 			*map;

	minf = &env->map_info;
	map = minf->map;
	minf->map_center = VEC2_INIT(map->size.x / 2.0, map->size.y / 2.0);
	map_update_zoom_range(env, minf);
}

static void			init_map_info(t_env *env, t_map_info *minf)
{
	t_map 	*map;

	map = minf->map;
	map_scale2grid(env);
	minf->map_center = VEC2_INIT(map->size.x / 2.0, map->size.y / 2.0);
	minf->grid_center = VEC2_INIT(env->grid.size.x / 2.0,
								env->grid.size.y / 2.0);
	minf->pos = 0;
}

static int			init_rpanels(t_env *env, t_rpanel *rpan)
{
	init_object_pbox(&rpan->p[Object_Panel], &env->sdl);
	init_wall_pbox(&rpan->p[Texture_Panel], &env->sdl);
	rpan->type = Texture_Panel;
	return (SUCCESS);
}

static int			env_init2(t_env *env, char *filename)
{
	t_map		*map;

	map = env->map_info.map;
	init_grid(env, &env->sdl);
	env->save_file = filename;
	env->space = 0;
	env->alt = 0;
	if (env->loaded == False)
	{
		env->spawn = IVEC2_INIT(map->size.x / 2, map->size.y / 2);
		env->spawn_rotation = 0;
	}
	env->kframe = 0;
	env->saved = True;
	button_setactive(env->editor.switch_b[Painter], True);
	mouse_track_init(env);
	palette_init(env);
	init_map_info(env, &env->map_info);
	init_toolset(&env->toolset);
	return (SUCCESS);
}

static void		convert_ent(t_entity *ent, int id)
{
	ent->id = id;
	ent->tex_id--;
	if (ent->type == ENTITY_DOOR)
		ent->e.door->tex_wall_id--;
}

static void		convert_parsed_map(t_map *map, t_parser *parser)
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
		i++;
	}
	free(parser->obj.objects);
}

static void		convert_parsed_data(t_env *env, t_map *map, t_parser *parser)
{
	t_parser_map	*p_map;

	p_map = &parser->map;
	convert_parsed_map(map, parser);
	convert_parsed_obj(env, parser);
	env->inspector.world.id[WButton_Floor] = (t_u32)p_map->floor_id;
	env->inspector.world.id[WButton_Ceil] = (t_u32)p_map->ceil_id;
	env->inspector.world.draw_ceil = (t_u32)p_map->show_ceil;
	env->spawn = p_map->spawn;
	env->spawn_rotation = (int)p_map->spawn_rotation;
	env->loaded = True;
}

int				load_map(t_env *env, char *filename)
{
	int			conf_fd;
	t_parser	parser;
	t_map		*map;

	if ((map = map_new(IVEC2_INIT(DEF_SIZE_X, DEF_SIZE_Y))) == NULL)
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

int					env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(*env));
	if (is_valid_mapfile(filename) == False)
		return (ERROR);
	if (sdl_init(&env->sdl, MAP_GEN_NAME, WIN_X, WIN_Y) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	env->map_info.tmp_data = (int**)new_ar_data(MAX_SIZE_Y,
										sizeof(int) * MAX_SIZE_X);
	if (env->map_info.tmp_data == NULL
		|| load_map(env, filename) == ERROR
		|| init_rpanels(env, &env->rpan) == ERROR
		|| env_create_inspect(env) == ERROR
		|| init_editor(env, &env->sdl, &env->editor) == ERROR)
	{
		perror("W3dEditor");
		return (ERROR);
	}
	return (env_init2(env, filename));
}
