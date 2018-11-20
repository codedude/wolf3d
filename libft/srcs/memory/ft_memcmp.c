/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:11:38 by vparis            #+#    #+#             */
/*   Updated: 2017/12/03 18:22:50 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char const	*s1_t;
	unsigned char const	*s2_t;

	if (n < 1)
		return (0);
	s1_t = (unsigned char const *)s1;
	s2_t = (unsigned char const *)s2;
	while (--n > 0)
	{
		if (*s1_t != *s2_t)
			break ;
		s1_t++;
		s2_t++;
	}
	return (*s1_t - *s2_t);
}
