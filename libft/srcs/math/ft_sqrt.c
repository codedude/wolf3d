/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 12:03:00 by vparis            #+#    #+#             */
/*   Updated: 2017/11/06 20:26:31 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_u32		ft_sqrt(t_u32 n)
{
	t_u64	start;
	t_u64	end;
	t_u64	mid;
	t_u64	nb;

	if (n < 1)
		return (0);
	if (n == 1)
		return (1);
	nb = (t_u64)n;
	start = 0;
	end = nb / 2;
	while (start <= end)
	{
		mid = (start + end) / 2;
		if (mid * mid == nb)
			return ((t_u32)mid);
		if (mid * mid < nb)
			start = mid + 1;
		else
			end = mid - 1;
	}
	return (0);
}
