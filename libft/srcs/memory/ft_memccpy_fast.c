/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy_fast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 15:30:29 by vparis            #+#    #+#             */
/*   Updated: 2017/10/05 15:59:05 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Fast memccpy, be sure buffers are valid and c is present
*/

void		*ft_memccpy_fast(void *dest, const void *src, int c)
{
	char const		*src_t;
	char			*dest_t;
	char			t;

	dest_t = (char *)dest;
	src_t = (char const *)src;
	t = (char)c;
	while (t != *src_t)
		*dest_t++ = *src_t++;
	*dest_t++ = *src_t;
	return (dest_t);
}
