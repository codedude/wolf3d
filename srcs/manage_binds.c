/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 16:00:34 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/26 16:11:53 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "env.h"
#include "sdl_m.h"
#include "raycast.h"

t_float	player_speed(t_cam *player, t_float factor)
{
	return ((player->mov_speed + player->acceleration) * factor);
}

void	manage_down(const Uint8	*state, t_cam *player, t_map *map)
{
	if (state[SDL_SCANCODE_A])
	{
		player->pos = straf(map, player->pos, player->dir,
			player_speed(player, -0.75));
	}
	if (state[SDL_SCANCODE_D])
	{
		player->pos = straf(map, player->pos, player->dir,
			player_speed(player, 0.75));
	}
	if (state[SDL_SCANCODE_W])
	{
		player->pos = move_forward(map, player->pos, player->dir,
			player_speed(player, 1.0));
	}
	if (state[SDL_SCANCODE_S])
	{
		player->pos = move_forward(map, player->pos, player->dir,
			player_speed(player, -0.75));
	}
	if (state[SDL_SCANCODE_Q])
	{
      player->dir = vec_rotate(player->dir, -player->rot_speed);
      player->plane = vec_rotate(player->plane, -player->rot_speed);
	}
	if (state[SDL_SCANCODE_E])
	{
      player->dir = vec_rotate(player->dir, player->rot_speed);
      player->plane = vec_rotate(player->plane, player->rot_speed);
	}
}

int		manage_binds(SDL_Event *event, t_cam *player)
{
	int		r;

	r = 1;
	if (event->type == SDL_QUIT)
		r = 0;
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			r = 0;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_LSHIFT
			&& player->acceleration == 0.0)
			player->acceleration = 0.25;
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
    	player->dir = vec_rotate(player->dir,
					player->rot_speed *
					(t_float)(event->motion.xrel * 0.33));
    	player->plane = vec_rotate(player->plane,
					player->rot_speed *
					(t_float)(event->motion.xrel * 0.33));
	}
	return (r);
}
