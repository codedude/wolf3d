/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ischarset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 21:37:50 by vparis            #+#    #+#             */
/*   Updated: 2017/10/06 21:44:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ischarset(int c, char const *charset)
{
	size_t	i;
	char	t;

	t = (char)c;
	i = 0;
	while (charset[i] != 0)
		if (t == charset[i++])
			return (1);
	return (0);
}
