/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:00:41 by vparis            #+#    #+#             */
/*   Updated: 2018/11/27 18:53:55 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include "libft.h"
# include "libtpool.h"
# include "sdl_m.h"
# include "env.h"

static t_float	*init_lu_table(int height)
{
	t_float		*table;
	int			y;

	height += 0;
	if (!(table = (t_float*)malloc(sizeof(*table) * height)))
		return (NULL);
	y = 0;
	while (y < height)
	{
		table[y] = height / (2.0 * (y - 0) - height);
		y++;
	}
	return (table);
}

static int		wolf_init(t_sdl *sdl, t_map *map, t_cam *cam, char *filename)
{
	if (load_map(map, filename) == ERROR)
		return (ERROR);
	cam->pos = VEC2_INIT((t_float)map->spawn.x, (t_float)map->spawn.y) + 0.5;
	cam->dir = VEC2_INIT(-1., 0.0);
	cam->plane = VEC2_INIT(0.0, 0.8);
	cam->mov_speed = 0.05;
	cam->rot_speed = 0.016;
	cam->acceleration = 0.0;
	cam->height = 0.0;
	if (!(cam->lookup_table = init_lu_table((int)sdl->height)))
		return (ERROR);
	return (SUCCESS);
}

static void		wolf_destroy(t_map *map, t_cam *cam)
{
	(void)cam;
	ft_memdel((void **)&cam->lookup_table);
	map_destroy(map);
	//Delete map
}

int				env_init(t_env *env, char *filename)
{
	if (sdl_init(&env->sdl, WINDOW_NAME, 1280, 720) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if (sdl_init_textures() == ERROR)
	{
		ft_putstr_fd("Can't load textures\n", 2);
		return (ERROR);
	}
	if ((env->tpool = tp_create(THREADS, TP_ON_START)) == NULL)
	{
		ft_putstr_fd("Thread pool can't start\n", 2);
		return (ERROR);
	}
	if (wolf_init(&env->sdl, &env->map, &env->cam, filename) == ERROR)
	{
		ft_putstr_fd("Can't init wolf\n", 2);
		return (ERROR);
	}
	env->show_fps = 0;
	return (SUCCESS);
}

void		env_destroy(t_env *env)
{
	sdl_destroy_textures();
	tp_destroy(&env->tpool);
	sdl_destroy(&env->sdl);
	wolf_destroy(&env->map, &env->cam);
}
