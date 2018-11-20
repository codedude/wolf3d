/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 11:47:58 by vparis            #+#    #+#             */
/*   Updated: 2017/11/12 15:36:04 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char const *s, int fd)
{
	char	nl;

	if (s == NULL)
	{
		ft_putendl_fd(NULL_STR, fd);
		return ;
	}
	nl = 10;
	write(fd, s, ft_strlen(s));
	write(fd, &nl, 1);
}
