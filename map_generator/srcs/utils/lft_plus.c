/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lft_plus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:09:55 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/28 15:06:39 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "libft.h"
#include "types.h"

int				ipercent_of(int of, int percent)
{
	return (of * percent / 100);
}

t_float			snap_f(t_float snap, t_float height)
{
	t_float		mod;

	mod = fmodf(snap, height);
	if (mod >= height / 2.0f)
		return (snap - mod + height);
	return (snap - mod);
}

t_vec2			vec_snap(t_vec2 snap, t_float height)
{
	return (VEC2_INIT(snap_f(snap.x, height), snap_f(snap.y, height)));
}

void			free_ar_data(void **tab, size_t size)
{
	size_t		i;

	if (!tab)
		return ;
	i = 0;
	while (i < size)
	{
		free(tab[i]);
		++i;
	}
	free(tab);
}

void			**new_ar_data(size_t height, size_t width)
{
	void	**data;
	size_t	i;

	if (!(data = (void **)ft_memalloc(sizeof(void *) * height)))
		return (NULL);
	i = 0;
	while (i < height)
	{
		if (!(data[i] = ft_memalloc(width)))
		{
			free_ar_data(data, height);
			return (NULL);
		}
		++i;
	}
	return (data);
}
