/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_nonprint_fd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 12:11:03 by vparis            #+#    #+#             */
/*   Updated: 2017/11/08 15:54:31 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_print_hex_fd(char c, char const *base, int fd)
{
	unsigned char	uc;

	uc = (unsigned char)c;
	ft_putchar_fd('\\', fd);
	ft_putchar_fd(base[uc / 16], fd);
	ft_putchar_fd(base[uc % 16], fd);
}

void		ft_putstr_nonprint_fd(char const *str, int fd)
{
	size_t	i;
	char	c;

	i = 0;
	while (str[i] != 0)
	{
		c = str[i];
		if (c < 32 || c > 126)
			ft_print_hex_fd(c, CHARSET_BASE_16L, fd);
		else
			ft_putchar_fd(c, fd);
		i++;
	}
}
