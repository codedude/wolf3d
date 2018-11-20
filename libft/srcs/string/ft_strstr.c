/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:51:42 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 15:28:49 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	char const	*sb;
	char const	*sl;

	if (*needle == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		sb = haystack;
		sl = needle;
		while (*sb == *sl && *sb != 0)
		{
			sb++;
			sl++;
		}
		if (*sl == 0)
			return ((char *)haystack);
		if (*sb == 0)
			return (NULL);
		haystack++;
	}
	return (NULL);
}
