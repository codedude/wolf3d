/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr_fast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:59:51 by vparis            #+#    #+#             */
/*   Updated: 2017/10/07 11:51:33 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Fast implementation of memchr
** BE SURE to find  the char c
*/

void	*ft_memchr_fast(const void *s, int c)
{
	unsigned char const *s_t;
	unsigned char		c_t;

	s_t = (unsigned char const *)s;
	c_t = (unsigned char)c;
	while (c_t != *s_t)
		s_t++;
	return ((void *)s_t);
}
