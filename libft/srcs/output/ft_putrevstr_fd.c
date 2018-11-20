/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putrevstr_fd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:47:43 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 16:43:04 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putrevstr_fd(char const *s, int fd)
{
	size_t	i;

	if (s == NULL)
	{
		ft_putstr_fd(NULL_STR, fd);
		return ;
	}
	i = 0;
	while (s[i] != 0)
		i++;
	while (i > 0)
		write(fd, &s[i-- - 1], 1);
}
