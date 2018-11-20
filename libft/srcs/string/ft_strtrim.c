/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 20:43:53 by vparis            #+#    #+#             */
/*   Updated: 2017/11/08 20:57:42 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	size_t	start;
	size_t	end;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	start = i;
	i = ft_strlen(s);
	if (start != i && i > 0)
	{
		i--;
		while (ft_isspace(s[i]))
			i--;
		end = i + 1;
	}
	else
	{
		start = 0;
		end = 0;
	}
	return (ft_strsub(s, (unsigned int)start, end - start));
}
