/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 22:26:33 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/15 22:41:00 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "parser.h"

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

void	del_int_2d_array(int **ar, int h)
{
	int		i;

	if (!ar)
		return ;
	i = 0;
	while (i < h)
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

int		**int_new_2darray(int x, int y)
{
	int		**ar;
	int		i;

	if (!(ar = (int**)ft_memalloc(sizeof(int *) * (unsigned int) y)))
		return (NULL);
	i = 0;
	while (i < y)
	{
		if (!(ar[i] = (int *)malloc(sizeof(int) * (unsigned int) x)))
		{
			del_int_2d_array(ar, y);
			return (NULL);
		}
		i++;
	}
	return (ar);
}

int		is_filechar(int c)
{
	return (c == '/' || c == '_' || ft_isalnum(c) || c == '.');
}
