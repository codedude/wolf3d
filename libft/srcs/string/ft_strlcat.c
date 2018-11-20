/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:51:22 by vparis            #+#    #+#             */
/*   Updated: 2017/11/08 20:06:39 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	char		*d;
	char const	*s;
	size_t		d_len;
	size_t		n;

	d = dest;
	s = src;
	n = size;
	while (*d != 0 && n-- != 0)
		d++;
	d_len = (size_t)(d - dest);
	n = size - d_len;
	if (n == 0)
		return (d_len + ft_strlen(s));
	while (*s != 0)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = 0;
	return (d_len + (size_t)(s - src));
}
