/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 21:45:48 by vparis            #+#    #+#             */
/*   Updated: 2017/11/08 18:55:59 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_char_pos(char const *base, char c)
{
	int i;

	i = 0;
	while (base[i] != 0)
		if (c == base[i++])
			return (i - 1);
	return (-1);
}

static int	check_str(char const *str, char const *base, size_t *id)
{
	int		sign;
	size_t	i;

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
	else if (!ft_ischarset(str[i], base))
		sign = 0;
	*id = i;
	return (sign);
}

static int	check_base(char const *base)
{
	size_t	r;
	size_t	i;
	size_t	t;

	r = ft_strlen(base);
	if (r < 2 || r > 92)
		return (0);
	i = 0;
	while (base[i] != 0)
	{
		if (!ft_isgraph(base[i]) || base[i] == '+' || base[i] == '-')
			return (0);
		t = i + 1;
		while (base[t] != 0)
		{
			if (base[i] == base[t])
				return (0);
			t++;
		}
		i++;
	}
	return ((int)r);
}

int			ft_atoi_base(char const *nptr, char const *base)
{
	int			r;
	int			sign;
	int			size;
	int			n;
	size_t		i;

	size = check_base(base);
	sign = check_str(nptr, base, &i);
	if (sign == 0 || size < 2)
		return (0);
	n = 0;
	while (nptr[i] != 0)
	{
		r = get_char_pos(base, nptr[i++]);
		if (r == -1)
			break ;
		n = n * size + r;
	}
	return (n * sign);
}
