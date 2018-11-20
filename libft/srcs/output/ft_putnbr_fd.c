/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/04 12:10:48 by vparis            #+#    #+#             */
/*   Updated: 2017/10/05 18:49:30 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char	number[12];
	size_t	i;
	int		r;
	int		nb;

	nb = n;
	i = 0;
	while (n != 0)
	{
		r = n % 10;
		if (nb < 0)
			number[i++] = (char)('0' - r);
		else
			number[i++] = (char)('0' + r);
		n /= 10;
	}
	if (nb == 0)
		number[i++] = '0';
	else if (nb < 0)
		number[i++] = '-';
	number[i] = 0;
	ft_putrevstr_fd(number, fd);
}
