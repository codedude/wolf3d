/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lft_plus_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:09:55 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/28 15:02:11 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "types.h"

static size_t	nblen(unsigned int n)
{
	size_t len;

	len = 0;
	while ((n /= 10) > 0)
		len++;
	return (len);
}

char			*ft_static_itoa(int n)
{
	static char		str[12];
	unsigned int	nb;
	size_t			len;

	nb = n < 0 ? (unsigned int)-n : (unsigned int)n;
	len = nblen(nb) + ((n >= 0) ? 1 : 2);
	if (n < 0)
		str[0] = '-';
	str[len] = '\0';
	str[--len] = (nb % 10) + '0';
	while ((nb /= 10))
		str[--len] = (nb % 10) + '0';
	return (str);
}

t_vec2			vec_rotate(t_vec2 dir, t_float radian)
{
	t_float old_x;

	old_x = dir.x;
	dir.x = (t_float)(dir.x * cos(-radian) - dir.y * sin(-radian));
	dir.y = (t_float)(old_x * sin(-radian) + dir.y * cos(-radian));
	return (dir);
}

void			ft_putnbrf_fd(t_float f, int fd, t_u32 prec)
{
	t_float		m;
	char		*str;
	size_t		i;

	if (f < 0.0f)
	{
		ft_putchar_fd('-', fd);
		f = -f;
	}
	ft_putnbr_fd((int)f, fd);
	ft_putchar_fd('.', fd);
	m = f - (int)f;
	str = ft_static_itoa((int)(pow(10.0f, prec) * m));
	i = ft_strlen(str);
	while (i && str[i - 1] == '0')
		i--;
	if (i && str[i] == '0')
		str[i] = '\0';
	ft_putstr_fd(str, fd);
}
