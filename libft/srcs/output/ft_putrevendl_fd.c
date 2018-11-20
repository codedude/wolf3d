/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putrevendl_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:48:32 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 16:43:00 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putrevendl_fd(char const *s, int fd)
{
	size_t	i;
	char	nl;

	if (s == NULL)
	{
		ft_putendl_fd(NULL_STR, fd);
		return ;
	}
	i = 0;
	nl = 10;
	while (s[i] != 0)
		i++;
	while (i > 0)
		write(fd, &s[i-- - 1], 1);
	write(fd, &nl, 1);
}
