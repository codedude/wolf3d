/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/06 12:06:56 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:54:55 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include "libft.h"
#include "gen_env.h"

void			save_spawn(t_env *env, int fd)
{
	int		rot;

	rot = env->spawn_rotation;
	if (rot)
		rot = 360 - rot;
	ft_putstr_fd("Spawn {\n\tpos\t", fd);
	ft_putnbr_fd(env->spawn.x, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(env->spawn.y, fd);
	ft_putstr_fd("\n\tdir\t", fd);
	ft_putnbr_fd(rot, fd);
	ft_putstr_fd("\n}\n\n", fd);
}

void			print_obj_title(t_env *env, int fd)
{
	ft_putstr_fd("Object ", fd);
	ft_putnbr_fd((int)env->obj.count, fd);
	ft_putstr_fd(" {\n", fd);
}

void			save_objects(t_env *env, int fd)
{
	t_objects_tools	*otools;
	t_object_e		*obj;
	t_u32			i;

	print_obj_title(env, fd);
	otools = &env->obj;
	i = 0;
	while (i < otools->count)
	{
		obj = otools->list[i];
		ft_putstr_fd((obj->is_solid ? "True" : "False"), fd);
		ft_putstr_fd(" : ", fd);
		ft_putnbr_fd((int)obj->id, fd);
		ft_putstr_fd(" : ", fd);
		ft_putnbrf_fd(obj->pos.x, fd, 6);
		ft_putstr_fd(", ", fd);
		ft_putnbrf_fd(obj->pos.y, fd, 6);
		ft_putchar_fd('\n', fd);
		i++;
	}
	ft_putstr_fd("}\n\n", fd);
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
	save_objects(env, fd);
	save_map(env, fd);
	ft_putstr("W3dEditor: ");
	ft_putstr(env->save_file);
	ft_putstr(": file saved\n");
	close(fd);
	env->saved = True;
	return (SUCCESS);
}
