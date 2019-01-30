/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 22:26:33 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 13:25:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "entity.h"

int			ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char		*skip_whitespace(char *str)
{
	while (ft_iswhitespace(*str))
		str++;
	return (str);
}

void		destroy_map_data(t_entity ***a_data, int width, int height)
{
	t_entity	**data;
	int			i;
	int			j;

	data = *a_data;
	if (data)
	{
		i = 0;
		while (i < height)
		{
			if (data[i])
			{
				j = 0;
				while (j < width)
				{
					free(data[i][j].e.brick);
					++j;
				}
				free(data[i]);
			}
			++i;
		}
		free(data);
		*a_data = NULL;
	}
}

t_entity	**new_map_data(int width, int height)
{
	t_entity	**data;
	int			i;

	if (!(data = (t_entity **)ft_memalloc(sizeof(*data) * (size_t)height)))
		return (0);
	i = 0;
	while (i < height)
	{
		if (!(data[i] = (t_entity *)ft_memalloc(
			sizeof(t_entity) * (size_t)width)))
		{
			destroy_map_data(&data, width, height);
			return (NULL);
		}
		i++;
	}
	return (data);
}

int			is_filechar(int c)
{
	return (c == '/' || c == '_' || ft_isalnum(c) || c == '.');
}
