/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:47:11 by vparis            #+#    #+#             */
/*   Updated: 2017/10/05 17:06:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strchr(const char *s, int c)
{
	char const	*str;
	char		t;

	t = (char)c;
	str = (char *)s;
	while (t != *str)
	{
		if (*str == 0)
			break ;
		str++;
	}
	if (t == *str)
		return ((char *)str);
	return (NULL);
}
