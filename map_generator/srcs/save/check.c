/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 12:06:56 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:54:50 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "gen_env.h"

static t_bool	is_valid_filename(char *filename)
{
	char		*point;

	if (!(point = ft_strrchr(filename, '.')) || !ft_strequ(point, ".w3d"))
	{
		ft_putstr_fd("W3dEditor: map format error\n", 2);
		return (False);
	}
	return (True);
}

t_bool			is_valid_mapfile(char *filename)
{
	int			fd;

	if (is_valid_filename(filename) == False)
		return (False);
	errno = 0;
	if ((fd = open(filename, O_RDWR)) == -1
	&& errno != ENOENT)
	{
		perror("W3dEditor");
		return (False);
	}
	if (fd != -1)
		close(fd);
	return (True);
}
