/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:51:32 by vparis            #+#    #+#             */
/*   Updated: 2017/10/05 16:34:03 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strncat(char *dest, const char *src, size_t n)
{
	char	*s;

	s = dest;
	while (*dest != 0)
		dest++;
	while (*src != 0 && n-- != 0)
		*dest++ = *src++;
	*dest = 0;
	return (s);
}
