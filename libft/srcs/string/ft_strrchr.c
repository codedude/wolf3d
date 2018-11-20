/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 16:47:13 by vparis            #+#    #+#             */
/*   Updated: 2017/10/05 17:05:57 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strrchr(const char *s, int c)
{
	char const	*str;
	char		t;

	t = (char)c;
	str = (char *)ft_memchr_fast((void *)s, 0);
	while (t != *str)
	{
		if (s == str)
			break ;
		str--;
	}
	if (t == *str)
		return ((char *)str);
	return (NULL);
}
