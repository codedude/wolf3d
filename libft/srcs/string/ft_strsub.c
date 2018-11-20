/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 20:43:58 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 15:20:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*tmp;

	if (s == NULL)
		return (NULL);
	tmp = ft_strnew_fast(len);
	if (tmp == NULL)
		return (NULL);
	tmp = ft_strncpy(tmp, s + start, len);
	tmp[len] = 0;
	return (tmp);
}
