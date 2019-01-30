/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 22:53:54 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 13:09:19 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "env.h"
#include "libft.h"
#include "parser.h"

static int	make_maps(t_env *env, t_map *map)
{
	int			i;
	int			j;
	t_entity	*obj;
	t_anim		*anim;

	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < map->width)
		{
			obj = &map->data[i][j];
			if (obj->type != ENTITY_VOID)
				if (tex_get_wall(&env->sdl, obj->tex_id - 1)->n_sprites > 1)
				{
					anim = anim_new(obj, ANIM_TEXTURE | ANIM_LOOP, False, 2);
					if (anim == NULL)
						return (ERROR);
					alist_push(&env->anims, anim);
				}
		}
	}
	return (SUCCESS);
}

static int	make_sprites(t_env *env)
{
	int			i;
	t_entity	*obj;
	t_tex		*tex;
	t_anim		*anim;

	i = 0;
	while (i < env->objects_nb)
	{
		obj = &env->objects[i];
		tex = tex_get_sprite(&env->sdl, obj->tex_id);
		if (tex->n_sprites > 1)
		{
			anim = anim_new(obj, ANIM_TEXTURE | ANIM_LOOP, False, 2);
			if (anim == NULL)
				return (ERROR);
			alist_push(&env->anims, anim);
		}
		++i;
	}
	return (SUCCESS);
}

static int	make_anims(t_env *env, t_map *map)
{
	if (make_sprites(env) == ERROR || make_maps(env, map) == ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	convert_parsed_data(t_env *env, t_map *map, t_parser *parser)
{
	t_parser_map	*p_map;

	p_map = &parser->map;
	map->data = p_map->data;
	map->floor_id = p_map->floor_id;
	map->ceil_id = p_map->ceil_id;
	map->show_ceil = p_map->show_ceil;
	map->spawn = p_map->spawn;
	map->spawn_rotation = p_map->spawn_rotation;
	map->width = p_map->width;
	map->height = p_map->height;
	env->objects = parser->obj.objects;
	env->objects_nb = parser->obj.objects_nb;
	return (make_anims(env, map));
}

int			load_map(t_env *env, t_map *map, char *mapfile)
{
	int			conf_fd;
	int			ret_value;
	t_parser	parser;

	if (is_valid_filename(mapfile) == ERROR)
		return (ERROR);
	ft_bzero(map, sizeof(*map));
	errno = 0;
	if ((conf_fd = open(mapfile, O_RDONLY | O_NONBLOCK | O_NOFOLLOW)) == -1)
	{
		perror("Wolf3d: ");
		return (ERROR);
	}
	if ((ret_value = parse_map(&env->sdl, &parser, conf_fd)) == SUCCESS)
		ret_value = convert_parsed_data(env, map, &parser);
	close(conf_fd);
	return (ret_value);
}
