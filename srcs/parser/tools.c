/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 22:26:33 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/14 17:50:52 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "entity.h"

int		ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char	*skip_whitespace(char *str)
{
	while (ft_iswhitespace(*str))
		str++;
	return (str);
}

void	destroy_map_data(t_map *map)
{
	int		i;
	int		j;

	if (map->data)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->data[i])
			{
				j = 0;
				while (j < map->width)
				{
					free(map->data[i][j].e.brick);
					++j;
				}
				free(map->data[i]);
			}
			++i;
		}
		free(map->data);
		map->data = NULL;
}
}

int		new_map_data(t_map *map)
{
	int			i;

	if (!(map->data
		= (t_entity **)ft_memalloc(sizeof(t_entity *) * (size_t)map->height)))
		return (0);
	i = 0;
	while (i < map->height)
	{
		if (!(map->data[i]
			= (t_entity *)ft_memalloc(sizeof(t_entity) * (size_t)map->width)))
		{
			destroy_map_data(map);
			return (0);
		}
		i++;
	}
	return (1);
}

int		is_filechar(int c)
{
	return (c == '/' || c == '_' || ft_isalnum(c) || c == '.');
}
