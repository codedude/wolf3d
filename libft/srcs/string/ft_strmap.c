/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 20:44:12 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 15:19:09 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmap(char const *s, char (*f)(char))
{
	char	*tmp;
	char	*tmp_s;

	if (s == NULL || f == NULL)
		return (NULL);
	tmp = ft_strnew_fast(ft_strlen(s));
	if (tmp == NULL)
		return (NULL);
	tmp_s = tmp;
	while (*s != 0)
		*tmp++ = (*f)(*s++);
	*tmp = 0;
	return (tmp_s);
}
