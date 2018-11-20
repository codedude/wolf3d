/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:11:24 by vparis            #+#    #+#             */
/*   Updated: 2017/11/25 17:46:09 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	memcpy_tmp(char *dest, char *src, size_t n)
{
	char	tmp[1024];
	size_t	size;

	if (n < 1)
		return ;
	while (n > 0)
	{
		size = (n > 1024) ? 1024 : n;
		ft_memcpy(tmp, src, size);
		ft_memcpy(dest, tmp, size);
		n -= size;
	}
}

void		*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*src_t;
	char	*dest_t;

	src_t = (char *)src;
	dest_t = (char *)dest;
	if (src_t > dest_t + n || src_t + n < dest_t)
		ft_memcpy(dest, src, n);
	else
		memcpy_tmp(dest_t, src_t, n);
	return (dest);
}
