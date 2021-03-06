/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 12:02:56 by vparis            #+#    #+#             */
/*   Updated: 2017/10/07 12:58:53 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_i32		ft_power(t_i32 n, t_i32 power)
{
	t_i32	a;

	if (power < 0)
		return (0);
	else if (power == 0)
		return (1);
	a = n;
	while (--power)
		n *= a;
	return (n);
}
