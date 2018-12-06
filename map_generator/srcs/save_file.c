/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 12:06:56 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/06 12:46:34 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "gen_env.h"

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
		perror("W3dEditor: ");
		return (False);
	}
	if (fd != -1)
		close(fd);
	return (True);
}

static void		print_spawner(int found)
{
	if (found == 1)
		return ;
	else if (found == 0)
		ft_putstr_fd("W3dEditor: Warning: no spawner found\n", 2);
	else
		ft_putstr_fd("W3dEditor: Warning: too many spawners found\n", 2);
}

static void		map_to_save(t_map *map, int spawner_id, int fd)
{
	int		spawner_found;
	t_ivec2	i;

	spawner_found = 0;
	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			if (map->data[i.y][i.x] - 1 == spawner_id)
				spawner_found++;
			if (map->data[i.y][i.x] < 10)
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(ft_static_itoa(map->data[i.y][i.x]), fd);
			if (i.x < map->size.x - 1)
				ft_putchar_fd(' ', fd);
			i.x++;
		}
		ft_putchar_fd('\n', fd);
		i.y++;
	}
	print_spawner(spawner_found);
}

int				save_file(t_env *env)
{
	int			fd;

	errno = 0;
	if (!env->save_file
	|| (fd = open(env->save_file, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1)
	{
		if (errno != 0)
			perror("W3dEditor: ");
		return (ERROR);
	}
	map_to_save(env->map, env->spawner_id, fd);
	ft_putstr("W3dEditor: ");
	ft_putstr(env->save_file);
	ft_putstr(": file saved\n");
	close(fd);
	env->saved = True;
	return (SUCCESS);
}
