/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 12:06:56 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/18 19:36:10 by jbulant          ###   ########.fr       */
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
		perror("W3dEditor");
		return (False);
	}
	if (fd != -1)
		close(fd);
	return (True);
}

void			save_spawn(t_env *env, int fd)
{
	ft_putstr_fd("Spawn {\n\tpos\t", fd);
	ft_putnbr_fd(env->spawn.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(env->spawn.y, fd);
	ft_putstr_fd("\n\tdir\t", fd);
	ft_putnbr_fd(env->spawn_rotation, fd);
	ft_putstr_fd("\n}\n\n", fd);
}

char			*convert_map_xy(int xy, int *nb_save)
{
	char		*convert;

	if (xy > 0)
		convert = ft_static_itoa(nb_save[xy - 1] + 1);
	else
		convert = ft_static_itoa(0);
	return (convert);
}

void			save_map_content(t_map *map, int *nb_save, int fd)
{
	t_ivec2		i;
	char		*nb;

	i.y = 0;
	while (i.y < map->size.y)
	{
		ft_putchar_fd('\t', fd);
		i.x = 0;
		while (i.x < map->size.x)
		{
			nb = convert_map_xy(map->data[i.y][i.x], nb_save);
			if (map->data[i.y][i.x] < 10)
				ft_putchar_fd(' ', fd);
			ft_putstr_fd(nb, fd);
			if (i.x < map->size.x - 1)
				ft_putchar_fd(' ', fd);
			i.x++;
		}
		i.y++;
		ft_putstr_fd(i.y != map->size.y ? ",\n" : "\n", fd);
	}
}

void			save_map_title(t_map *map, int fd)
{
	ft_putstr_fd("Map ", fd);
	ft_putnbr_fd(map->size.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(map->size.y, fd);
	ft_putstr_fd(" {\n", fd);
}

void			save_map(t_env *env, int *nb_save, int fd)
{
	save_map_title(env->map, fd);
	save_map_content(env->map, nb_save, fd);
	ft_putstr_fd("}\n\n", fd);
}

int				fill_nbsave(int *nb_save, t_env *env)
{
	t_map		*map;
	t_ivec2		i;
	int			saved;

	map = env->map;
	saved = 0;
	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			if (map->data[i.y][i.x] > 0
				&& nb_save[map->data[i.y][i.x] - 1] == 0)
			{
				nb_save[map->data[i.y][i.x] - 1] = 1;
				saved++;
			}
			i.x++;
		}
		i.y++;
	}
	return (saved);
}

int				*save_textures_title(t_env *env, int fd)
{
	int			*nb_save;
	int			saved;

	if ((nb_save = ft_memalloc(sizeof(int) * (size_t)env->sdl.textures_nb)))
	{
		saved = fill_nbsave(nb_save, env);
		ft_putstr_fd("Texture ", fd);
		ft_putnbr_fd(saved, fd);
		ft_putstr_fd(" {\n", fd);
	}
	return (nb_save);
}

void			save_textures(t_env *env, int fd)
{
	int			*nb_save;
	int			i;
	int			save_index;

	if (!(nb_save = save_textures_title(env, fd)))
		return ;
	i = 0;
	save_index = 0;
	while (i < env->sdl.textures_nb)
	{
		if (nb_save[i] == 1)
		{
			nb_save[i] = save_index++;
			ft_putchar_fd('\t', fd);
			ft_putstr_fd(env->sdl.textures[i].name, fd);
			ft_putchar_fd('\n', fd);
		}
		i++;
	}
	ft_putstr_fd("}\n\n", fd);
	save_map(env, nb_save, fd);
	free(nb_save);
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
	save_spawn(env, fd);
	save_textures(env, fd);
	ft_putstr("W3dEditor: ");
	ft_putstr(env->save_file);
	ft_putstr(": file saved\n");
	close(fd);
	env->saved = True;
	return (SUCCESS);
}
