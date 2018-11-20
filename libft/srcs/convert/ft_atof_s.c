/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 01:05:08 by valentin          #+#    #+#             */
/*   Updated: 2018/04/25 02:52:28 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_math.h"

static int	ft_atof_s_divi(size_t len)
{
	int	divi;

	divi = 1;
	while (len--)
		divi *= 10;
	return (divi);
}

static void	compute_d(int d[2], char *str, t_f64 *n, int sign)
{
	int	divi;

	divi = ft_atof_s_divi(ft_strlen(str));
	if (sign < 0)
		*n = (t_f64)d[0] - (t_f64)d[1] / (t_f64)divi;
	else
		*n = (t_f64)d[0] + (t_f64)d[1] / (t_f64)divi;
}

int			ft_atof_s(char *str, t_f64 *n)
{
	char	**parts;
	int		d[2];
	int		sign;

	if ((parts = ft_strsplit(str, '.')) == NULL)
		return (ERROR);
	if (parts[1] == NULL)
	{
		ft_strsplit_free(parts);
		return (ERROR);
	}
	sign = (parts[0][0] == '-') ? -1 : 1;
	if (ft_atoi_s(parts[0], &d[0]) == ERROR
		|| ft_atoi_s(parts[1], &d[1]) == ERROR)
	{
		*n = ZERO_FLOAT;
		ft_strsplit_free(parts);
		return (ERROR);
	}
	else
		compute_d(d, parts[1], n, sign);
	ft_strsplit_free(parts);
	return (SUCCESS);
}
