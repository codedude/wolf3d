/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 14:50:43 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 15:27:32 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tmp;
	size_t	size;

	size = ft_strlen(s) + 1;
	tmp = (char *)malloc(sizeof(char) * size);
	if (tmp == NULL)
		return (NULL);
	ft_memccpy_fast((void *)tmp, (void *)s, 0);
	return (tmp);
}
