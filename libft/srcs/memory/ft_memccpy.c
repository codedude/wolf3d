/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 22:55:09 by valentin          #+#    #+#             */
/*   Updated: 2018/01/30 23:01:51 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Semi-Secure and optimize memccpy
** Check bad pointer and bad size
** TODO : check overlapping
*/

void		*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char const		*src_t;
	char			*dest_t;
	char			t;

	if (n < 1)
		return (NULL);
	dest_t = (char *)dest;
	src_t = (char const *)src;
	t = (char)c;
	while (--n != 0 && t != *src_t)
		*dest_t++ = *src_t++;
	*dest_t++ = *src_t;
	if (t != *src_t)
		return (NULL);
	return (dest_t);
}
