/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 20:44:11 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 15:19:04 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*tmp;
	char			*tmp_s;
	unsigned int	i;

	if (s == NULL || f == NULL)
		return (NULL);
	tmp = ft_strnew_fast(ft_strlen(s));
	if (tmp == NULL)
		return (NULL);
	tmp_s = tmp;
	i = 0;
	while (*s != 0)
		*tmp++ = (*f)(i++, *s++);
	*tmp = 0;
	return (tmp_s);
}
