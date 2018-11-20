/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:11:27 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 15:26:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char const	*s_t;
	unsigned char		c_t;

	if (n < 1)
		return (NULL);
	s_t = (unsigned char const *)s;
	c_t = (unsigned char const)c;
	while (--n > 0)
	{
		if (c_t == *s_t)
			return ((void *)s_t);
		s_t++;
	}
	if (c_t == *s_t)
		return ((void *)s_t);
	return (NULL);
}
