/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrealloc_fast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/27 19:08:46 by vparis            #+#    #+#             */
/*   Updated: 2017/10/27 19:08:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memrealloc_fast(void *src, size_t old, size_t size)
{
	void	*tmp;

	if (size < 1)
	{
		ft_memdel(&src);
		return (NULL);
	}
	if ((tmp = ft_memalloc_fast(size)) == NULL)
		return (NULL);
	ft_memcpy(tmp, src, old);
	ft_memdel(&src);
	return (tmp);
}
