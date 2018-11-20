/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 21:45:45 by vparis            #+#    #+#             */
/*   Updated: 2017/11/08 18:56:04 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_str(const char *str, int *id)
{
	int sign;
	int i;

	i = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	else if (!ft_isdigit(str[i]))
		sign = 0;
	*id = i;
	return (sign);
}

int			ft_atoi(const char *nptr)
{
	int i;
	int n;
	int sign;

	i = 0;
	n = 0;
	sign = check_str(nptr, &i);
	if (sign == 0)
		return (n);
	while (ft_isdigit(nptr[i]))
		n = n * 10 + nptr[i++] - '0';
	return (n * sign);
}
