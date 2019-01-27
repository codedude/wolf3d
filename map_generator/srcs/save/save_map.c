/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 12:06:56 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:56:17 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "gen_env.h"

static void		save_map_content(t_map *map, int fd)
{
	t_ivec2		i;
	int			val;

	i.y = 0;
	while (i.y < map->size.y)
	{
		ft_putchar_fd('\t', fd);
		i.x = 0;
		while (i.x < map->size.x)
		{
			if (map->data[i.y][i.x].type == ENTITY_WALL)
				val = map->data[i.y][i.x].tex_id + 1;
			else
				val = 0;
			if (val < 10)
				ft_putchar_fd(' ', fd);
			ft_putnbr_fd(val, fd);
			if (i.x < map->size.x - 1)
				ft_putchar_fd(' ', fd);
			i.x++;
		}
		i.y++;
		ft_putstr_fd(i.y != map->size.y ? ",\n" : "\n", fd);
	}
}

static void		save_map_title(t_map *map, int fd)
{
	ft_putstr_fd("Map ", fd);
	ft_putnbr_fd(map->size.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(map->size.y, fd);
	ft_putstr_fd(" {\n", fd);
}

static void		save_door(t_map *map, t_entity *ent, int fd)
{
	if (door_check_neighbour(map, ent))
	{
		ft_putstr_fd("Door ", fd);
		ft_putnbr_fd(ent->id % MAX_SZ_X, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(ent->id / MAX_SZ_X, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(ent->e.door->orientation, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(ent->tex_id, fd);
		ft_putchar_fd(' ', fd);
		ft_putnbr_fd(ent->e.door->tex_wall_id, fd);
		ft_putchar_fd('\n', fd);
	}
	else
		ft_putstr_fd("W3dEditor: Warning: door has too many or not enough neighbours\n", 2);
}

static void		save_map_doors(t_map *map, int fd)
{
	int			x;
	int			y;
	t_entity	*ent;
	y = 1;
	while (y < map->size.y - 1)
	{
		x = 1;
		while (x < map->size.x - 1)
		{
			ent = &map->data[y][x];
			if (ent->type == ENTITY_DOOR)
				save_door(map, ent, fd);
			x++;
		}
		y++;
	}
}

void			save_map(t_env *env, int fd)
{
	save_map_title(env->map_info.map, fd);
	save_map_doors(env->map_info.map, fd);
	save_map_content(env->map_info.map, fd);
	ft_putstr_fd("}\n\n", fd);
}
