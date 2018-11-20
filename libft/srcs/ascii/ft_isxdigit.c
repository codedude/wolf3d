/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 14:43:55 by vparis            #+#    #+#             */
/*   Updated: 2017/11/08 15:56:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isxdigit(int c)
{
	size_t	i;
	char	t;

	if (ft_isascii(c) == 0)
		return (0);
	t = (char)c;
	i = 0;
	while (CHARSET_BASE_16[i] != 0)
	{
		if (t == CHARSET_BASE_16[i++])
			return (1);
	}
	return (0);
}
