/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:08:10 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/14 18:39:39 by vparis           ###   ########.fr       */
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
		entity_destroy(map->skybox);
	destroy_map_data(map);
}
