/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 21:45:56 by vparis            #+#    #+#             */
/*   Updated: 2017/10/07 03:16:59 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	size_t	i;
	int		nb;
	char	r;
	char	number[12];

	nb = n;
	i = 0;
	while (nb != 0)
	{
		r = (char)(nb % 10);
		number[i++] = (char)((r < 0) ? '0' - r : '0' + r);
		nb /= 10;
	}
	if (n == 0)
		number[i++] = '0';
	else if (n < 0)
		number[i++] = '-';
	number[i] = '\0';
	ft_strrev(number);
	return (ft_strdup(number));
}
