/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 22:26:33 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/15 22:28:46 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

static int		is_sdigit(int c)
{
	return (c == '+' || c == '-' || ft_isdigit(c));
}

static char		*skip_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (str);
}

int				get_and_skipdigit(t_parser *parser, int *get)
{
	char	*line;

	if (!(line = get_next_word(parser, is_sdigit))
	|| (*get = ft_atoi(line)) < 0)
		return (ERROR);
	parser->line = skip_digit(line);
	return (SUCCESS);
}

int				get_and_skipsdigit(t_parser *parser, int *get)
{
	char	*line;

	if (!(line = get_next_word(parser, ft_isdigit))
	|| ((*line == '+' || *line == '-') && ft_isdigit(line[1]))
	|| (*get = ft_atoi(line)) < 0)
		return (ERROR);
	parser->line = skip_digit(line);
	return (SUCCESS);
}
