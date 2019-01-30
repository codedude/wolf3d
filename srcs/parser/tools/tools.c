/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 22:26:33 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:18:42 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"
#include "entity.h"

int			get_and_skipivec2(t_parser *parser, t_ivec2 *get)
{
	int		x;
	int		y;

	if (get_and_skipsdigit(parser, &x) == ERROR
	|| get_and_skipsdigit(parser, &y) == ERROR)
		return (ERROR);
	*get = IVEC2_INIT(x, y);
	return (SUCCESS);
}

int			skipchar(t_parser *parser, char c)
{
	if (get_next_char(parser, c) == ERROR)
		return (ERROR);
	parser->line++;
	return (SUCCESS);
}

int			skipword(t_parser *parser, char *word)
{
	size_t		wlen;

	wlen = ft_strlen(word);
	if (get_next_char(parser, *word) == ERROR
	|| !ft_strnequ(parser->line, word, wlen)
	|| (!ft_iswhitespace(parser->line[wlen])
		&& parser->line[wlen] != ':' && parser->line[wlen] != '\0'))
		return (ERROR);
	parser->line += wlen;
	return (SUCCESS);
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
