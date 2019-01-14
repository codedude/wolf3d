/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:08:10 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/14 16:49:00 by vparis           ###   ########.fr       */
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
	int		i;
	int		j;

	if (map->data)
	{
		i = 0;
		while (i < map->height)
		{
			j = 0;
			while (j < map->width)
			{
				free(map->data[i][j].e.brick);
				++j;
			}
			free(map->data[i]);
			++i;
		}
		free(map->data);
		map->data = NULL;
	}
}
