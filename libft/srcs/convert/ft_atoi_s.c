/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/20 17:58:31 by vparis            #+#    #+#             */
/*   Updated: 2018/03/20 17:58:48 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static inline int	ft_atoi_s_sign(char c)
{
	if (c == '-')
		return (-1);
	else if (c == '+')
		return (1);
	return (0);
}

int					ft_atoi_s(const char *str, int *nb)
{
	long int	n;
	int			i;
	int			sign;

	i = 0;
	n = 0;
	if ((sign = ft_atoi_s_sign(str[0])) != 0)
		i++;
	while (ft_isdigit(str[i]))
	{
		n = n * 10 + (str[i++] - '0');
		if ((n > (long int)INT_MAX && sign != -1)
			|| (sign == -1 && n > ((long int)INT_MAX + 1)))
		{
			*nb = (sign == -1) ? INT_MIN : INT_MAX;
			return (ERROR);
		}
	}
	if (sign == -1 && (n *= -1) < (long int)INT_MIN)
	{
		*nb = INT_MIN;
		return (ERROR);
	}
	*nb = (int)n;
	return ((str[i] != 0) ? ERROR : SUCCESS);
}
