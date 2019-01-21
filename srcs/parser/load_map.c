/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 22:53:54 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/21 03:46:11 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "env.h"
#include "libft.h"
#include "parser.h"

static void		convert_parsed_data(t_env *env, t_map *map, t_parser *parser)
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
}

int				load_map(t_env *env, t_map *map, char *mapfile)
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
		convert_parsed_data(env, map, &parser);
	close(conf_fd);
	return (ret_value);
}
