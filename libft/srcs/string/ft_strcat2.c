/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 18:28:46 by vparis            #+#    #+#             */
/*   Updated: 2017/10/07 19:09:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcat2(char *dest, const char *src1, const char *src2)
{
	char	*s;

	if (dest == NULL)
		return (NULL);
	s = dest;
	while (*dest != 0)
		dest++;
	if (src1 != NULL)
		while (*src1 != 0)
			*dest++ = *src1++;
	if (src2 != NULL)
		while (*src2 != 0)
			*dest++ = *src2++;
	*dest = 0;
	return (s);
}
