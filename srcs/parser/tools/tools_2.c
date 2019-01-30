/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 22:26:33 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:17:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

int				get_and_skipdigit(t_parser *parser, int *get)
{
	char	*line;

	if (!(line = get_next_word(parser, ft_isdigit))
	|| (*get = ft_atoi(line)) < 0)
		return (ERROR);
	parser->line = skip_digit(line);
	return (SUCCESS);
}

static char		*skip_sign(char *start)
{
	if (*start == '+' || *start == '-')
	{
		if (!ft_isdigit(start[1]))
			return (NULL);
		return (start + 1);
	}
	return (start);
}

int				get_and_skipsdigit(t_parser *parser, int *get)
{
	char	*line;

	if (!(line = get_next_word(parser, is_sdigit)))
		return (ERROR);
	*get = ft_atoi(line);
	if (!(line = skip_sign(line)))
		return (ERROR);
	parser->line = skip_digit(line);
	return (SUCCESS);
}

int				get_and_skipfdigit(t_parser *parser, t_float *get)
{
	char	*line;
	char	*end_nb;
	char	old_char;
	int		ret;

	if (!(line = get_next_word(parser, is_sdigit))
	|| !(end_nb = skip_sign(line))
	|| !(end_nb = skip_digit(end_nb))
	|| *end_nb != '.'
	|| !(end_nb = skip_digit(end_nb + 1)))
		return (ERROR);
	old_char = *end_nb;
	*end_nb = '\0';
	if ((ret = ft_atof_s(line, get)) == ERROR)
		parser->line = line;
	else
		parser->line = end_nb;
	*end_nb = old_char;
	return (SUCCESS);
}

int				get_and_skipvec2(t_parser *parser, t_vec2 *get)
{
	t_float		x;
	t_float		y;

	if (get_and_skipfdigit(parser, &x) == ERROR
	|| skipchar(parser, ',') == ERROR
	|| get_and_skipfdigit(parser, &y) == ERROR)
		return (ERROR);
	get->x = x;
	get->y = y;
	return (SUCCESS);
}
