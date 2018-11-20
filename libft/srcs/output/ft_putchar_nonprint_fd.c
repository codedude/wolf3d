/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_nonprint_fd.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 16:32:59 by vparis            #+#    #+#             */
/*   Updated: 2017/11/08 15:54:06 by vparis           ###   ########.fr       */
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

void		ft_putchar_nonprint_fd(char c, int fd)
{
	ft_print_hex_fd(c, CHARSET_BASE_16L, fd);
}
