/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 22:53:54 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 17:12:36 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "env.h"
#include "libft.h"
#include "parser.h"


int				load_map(t_env *env, t_map *map, char *mapfile)
{
	int		conf_fd;
	int		ret_value;

	if (is_valid_filename(mapfile) == ERROR)
		return (ERROR);
	ft_bzero(map, sizeof(*map));
	errno = 0;
	if ((conf_fd = open(mapfile, O_RDONLY | O_NOFOLLOW)) == -1)
	{
		perror("Wolf3d: ");
		return (ERROR);
	}
	ret_value = parse_map(env, conf_fd);
	close(conf_fd);
	return (ret_value);
}
