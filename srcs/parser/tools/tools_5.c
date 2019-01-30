/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 14:14:26 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 14:17:28 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			is_sdigit(int c)
{
	return (c == '+' || c == '-' || ft_isdigit(c));
}

char		*skip_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (str);
}

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

int			is_filechar(int c)
{
	return (c == '/' || c == '_' || ft_isalnum(c) || c == '.');
}
