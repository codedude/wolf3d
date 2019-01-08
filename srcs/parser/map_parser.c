/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 20:08:10 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/08 23:07:30 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"
#include "env.h"
#include "parser.h"

static char		*file_get_content(char *filename)
{
	char		*content;
	char		*tmp;
	char		buff[4096];
	int			fd;
	int			read_ret;

	if ((fd = open(filename, O_RDONLY | O_NOFOLLOW)) == -1)
		return (NULL);
	content = NULL;
	while ((read_ret = (int)read(fd, buff, sizeof(buff) - 1)) > 0)
	{
		buff[read_ret] = '\0';
		if ((tmp = content))
		{
			content = ft_strjoin(tmp, buff);
			free(tmp);
		}
		else
			content = ft_strdup(buff);
	}
	close(fd);
	return (content);
}

static int		parse_failed(t_map *map, char *content, char *errmsg)
{
	ft_putstr_fd("Wolf3d: ", 2);
	ft_putendl_fd(errmsg, 2);
	map_destroy(map);
	ft_strdel(&content);
	return (ERROR);
}

static int		count_numbers(const char *str)
{
	int 		wc;

	wc = 0;
	while (*str)
	{
		while (*str == ' ')
			str++;
		if (!*str)
			break ;
		wc++;
		while (ft_isdigit(*str))
			str++;
		if (*str && *str != ' ')
			return (-1);
	}
	return (wc);
}

static int		get_map_wh(t_map *map, char *content)
{
	char		*endl;
	int			x;

	map->height = 0;
	map->width = -1;
	while (*content)
	{
		if ((endl = ft_strchr(content, '\n')))
			*endl = '\0';
		if ((x = count_numbers(content)) == -1)
			return (ERROR);
		if (x != 0)
		{
			map->height++;
			if (map->width != -1 && x != map->width)
				return (ERROR);
			map->width = x;
		}
		if (!endl)
			break ;
		*endl = '\n';
		content = endl + 1;
	}
	return (SUCCESS);
}

static char		*convert_value(t_env *env, t_map *map, int i, char *start)
{
	int			j;

	j = 0;
	while (j < map->width)
	{
		while (*start == ' ')
			start++;
		if ((map->data[i][j] = ft_atoi(start)) > env->sdl.tex_wall_nb + 1
			&& map->data[i][j] != 99)
			return (NULL);
		else if (map->data[i][j] == 99)
		{
			if (map->spawn.x == -1)
				map->spawn = IVEC2_INIT(j, i);
			else
				return (NULL);
			map->data[i][j] = 0;
		}
		j++;
		while (ft_isdigit(*start))
			start++;
	}
	return (start);

}

static int		parse_map(t_env *env, t_map *map, char *content)
{
	int			i;
	char		*dummy;

	if (get_map_wh(map, content) == ERROR)
		return (parse_failed(map, content, "map format error"));
	if (!(map->data = (int **)ft_memalloc(sizeof(int *) * (size_t)map->height)))
		return (parse_failed(map, content, strerror(errno)));
	i = 0;
	dummy = content;
	map->spawn = IVEC2_INIT(-1, -1);
	while (i < map->height)
	{
		while (*dummy == '\n')
			dummy++;
		if (!(map->data[i] = (int *)malloc(sizeof(int) * (size_t)map->width)))
			return (parse_failed(map, content, strerror(errno)));
		if (!(dummy = convert_value(env, map, i++, dummy)))
			return (parse_failed(map, content, "invalid texture identifier"));
	}
	if (map->spawn.x == -1)
		return (parse_failed(map, content, "no spawn point found"));
	return (SUCCESS);
}

static int		is_valid_filename(char *filename)
{
	char		*point;

	if (!(point = ft_strrchr(filename, '.')) || !ft_strequ(point, ".w3d"))
	{
		ft_putstr_fd("Wolf3d: map format error\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

void			map_destroy(t_map *map)
{
	int			i;

	if (map->data)
	{
		i = 0;
		while (i < map->height)
		{
			ft_memdel((void**)&map->data[i]);
			i++;
		}
		free(map->data);
		map->data = NULL;
	}
}

int				load_map(t_env *env, t_map *map, char *mapfile)
{
	char		*content;

	errno = 0;
	if (is_valid_filename(mapfile) == ERROR)
		return (ERROR);
	if (!(content = file_get_content(mapfile)))
		return (parse_failed(map, content, strerror(errno)));
	ft_bzero(map, sizeof(*map));
	if (parse_map(env, map, content) == ERROR)
		return (ERROR);
	free(content);
	return (SUCCESS);
}
