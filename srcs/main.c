/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/25 15:29:49 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/01 21:59:02 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "sprite.h"
#include "raycast.h"


t_vec		vec_rotate(t_vec dir, t_float speed)
{
    t_float old_x;

	old_x = dir.x;
	dir.x = dir.x * cos(-speed) - dir.y * sin(-speed);
	dir.y = old_x * sin(-speed) + dir.y * cos(-speed);
	return (dir);
}

void	manage_down(const Uint8	*state, t_player *player)
{
	if (state[SDL_SCANCODE_W])
	{
		player->pos = move_forward(player->pos, player->dir, player->mov_speed);
	}
	if (state[SDL_SCANCODE_A])
	{
		player->pos = straf(player->pos, player->dir, -player->mov_speed);
	}
	if (state[SDL_SCANCODE_S])
	{
		player->pos = move_forward(player->pos, player->dir, -player->mov_speed);
	}
	if (state[SDL_SCANCODE_D])
	{
		player->pos = straf(player->pos, player->dir, player->mov_speed);
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

int		manage_binds(SDL_Event *event)
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
	return (r);
}

void	frame_update(t_sprite_anim	*anim)
{
	static int	counter = 0;

	if (counter == anim->speed)
	{
		anim->frame = (anim->frame + 1) % anim->n_frame;
		counter = 0;
	}
	else
		counter++;
}

void	frame_render(t_sdl *sdl, t_sprite_anim *anim)
{
	SDL_Rect dest = {200, 200, anim->width, anim->height};
	SDL_Rect src = {
		(anim->frame % anim->x_frame) * anim->width,
		(anim->frame / anim->x_frame) * anim->height,
		anim->width, anim->height
	};
	SDL_RenderCopy(sdl->renderer, anim->texture, &src, &dest);
}

t_player	new_player(void)
{
	t_player	player;

	ft_bzero(&player, sizeof(player));
	player.pos = VEC_INIT(15.0, 12.0);
	player.dir = VEC_INIT(-1., 0.0);
	player.plane = VEC_INIT(0.0, 0.66);
	player.mov_speed = .1;
	player.rot_speed = .033;
	return (player);
}

void	loop(t_sdl *sdl, t_sprite_anim	*anim)
{
	int			loop;
	SDL_Event	event;
	const Uint8	*state;
	t_player	player;

	player = new_player();
	loop = 1;
	while (loop == 1)
	{
		SDL_PumpEvents();
		state = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event))
			loop = manage_binds(&event);
		manage_down(state, &player);
		if (loop != 1)
		{
			sdl_destroy(sdl);
			break ;
		}

		sdl_clear(sdl);
		raycast(sdl, &player);
		//frame_update(anim);
		//frame_render(sdl, anim);
		sdl_render(sdl);
	}
}

int		main(void)
{
	t_sdl			sdl;
	t_sprite_anim	*anim;

	if (sdl_init(&sdl, WIDTH, HEIGHT) == ERROR || sdl_init_textures() == ERROR)
	{
		printf("SDL can't start\n");
		exit(1);
	}
	anim = new_sprite_anim(&sdl, "bomb.png", 100, 100);

	loop(&sdl, anim);

	sdl_destroy_textures();
	free_sprite_anim(anim);
	return (0);
}
