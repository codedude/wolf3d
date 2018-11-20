/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 18:00:41 by vparis            #+#    #+#             */
/*   Updated: 2018/11/20 19:25:21 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdlib.h>
# include "libft.h"
# include "libtpool.h"
# include "sdl_m.h"
# include "env.h"

int map_tmp[24][24] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/*
*	TODO : load from file
*/

static int	load_map(t_map *map)
{
	int	i;

	map->spawn = IVEC2_INIT(15, 12);
	map->width = 24;
	map->height = 24;
	if ((map->data = (int **)malloc(map->height * sizeof(int *))) == NULL)
		return (ERROR);
	i = 0;
	while (i < map->height)
	{
		if ((map->data[i] = (int *)malloc(map->width * sizeof(int )))
			== NULL)
			return (ERROR);
		ft_memcpy((void *)map->data[i], (void *)map_tmp[i],
			map->width * sizeof(int));
		i++;
	}
	return (SUCCESS);
}
static int	wolf_init(t_map *map, t_cam *cam)
{
	if (load_map(map) == ERROR)
		return (ERROR);
	cam->pos = VEC2_INIT((t_float)map->spawn.x, (t_float)map->spawn.y);
	cam->dir = VEC2_INIT(-1., 0.0);
	cam->plane = VEC2_INIT(0.0, 0.8);
	cam->mov_speed = 0.1;
	cam->rot_speed = 0.033;
	return (SUCCESS);
}

static void	wolf_destroy(t_map *map, t_cam *cam)
{
	(void)map;
	(void)cam;
	//Delete map
}

int			env_init(t_env *env)
{
	if (sdl_init(&env->sdl, WINDOW_NAME, WIDTH, HEIGHT) == ERROR)
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
	if (wolf_init(&env->map, &env->cam) == ERROR)
	{
		ft_putstr_fd("Can't init wolf\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

void		env_destroy(t_env *env)
{
	sdl_destroy_textures();
	tp_destroy(&env->tpool);
	sdl_destroy(&env->sdl);
	wolf_destroy(&env->map, &env->cam);
}
