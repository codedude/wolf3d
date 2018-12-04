/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:51:58 by vparis            #+#    #+#             */
/*   Updated: 2018/12/04 15:43:01 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_input.h"
#include "parser.h"

int		read_file(char *filename, t_stack **stack)
{
	volatile int	r;
	int				fd;
	int				n;
	char			*buff;

	if ((fd = open(filename, O_RDONLY | O_NONBLOCK | O_NOFOLLOW)) < 0)
		return (ERROR);
	n = 0;
	while ((r = ft_gnl(fd, &buff)) > 0)
	{
		if (!*buff)
		{
			free(buff);
			continue ;
		}
		ft_stackpush(stack, buff);
		n++;
	}
	close(fd);
	return (r == -1 ? ERROR : n);
}
