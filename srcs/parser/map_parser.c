/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:08:10 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/21 03:40:01 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "env.h"
#include "parser.h"
#include "entity.h"

void			map_destroy(t_map *map)
{
	if (map->skybox)
		entity_destroy(map->skybox, False);
	destroy_map_data(&map->data, map->width, map->height);
}
