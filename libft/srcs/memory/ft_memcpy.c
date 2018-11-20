/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:11:14 by vparis            #+#    #+#             */
/*   Updated: 2017/12/01 17:08:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	const	*src_t;
	char			*dest_t;
	void			*dest_s;

	if (n < 1 || dest == src || (dest == NULL && src == NULL))
		return (dest);
	dest_s = dest;
	dest_t = (char *)dest;
	src_t = (char const *)src;
	while (--n != 0)
		*dest_t++ = *src_t++;
	*dest_t = *src_t;
	return (dest_s);
}
