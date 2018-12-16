/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_binds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 02:51:25 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

void		manage_down(const Uint8	*state, t_env *env)
{
	if (state[SDL_SCANCODE_X])
	{
		env->zoom *= 1.01;
	}
	if (state[SDL_SCANCODE_Z])
	{
		env->zoom /= 1.01;
	}
}

int			manage_binds(SDL_Event *event, t_env *env)
{
	int		r;

	r = 1;
	if (event->type == SDL_QUIT)
		return (0);
	else if (event->type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_ESCAPE)
			return (0);
		else if (event->key.keysym.sym == SDLK_SPACE)
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			env->space = False;
		}
		else if (event->key.keysym.sym == SDLK_LALT)
			env->alt = False;
		else if (event->key.keysym.sym == SDLK_LCTRL)
			env->ctrl = False;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_SPACE)
		{
			if (env->mouse1 == 1)
				SDL_SetRelativeMouseMode(SDL_TRUE);
			env->space = True;
		}
		else if (event->key.keysym.sym == SDLK_LCTRL)
			env->ctrl = True;
		else if (event->key.keysym.sym == SDLK_r)
			env->map_pos = map_to_center(env);
		else if (event->key.keysym.sym == SDLK_y
			&& env->map->size.x < MAX_SIZE_X)
			env->map->size.x++;
		else if (event->key.keysym.sym == SDLK_t
			&& env->map->size.x > MIN_SIZE_X)
			env->map->size.x--;
		else if (event->key.keysym.sym == SDLK_h
			&& env->map->size.y < MAX_SIZE_Y)
			env->map->size.y++;
		else if (event->key.keysym.sym == SDLK_g
			&& env->map->size.y > MIN_SIZE_Y)
			env->map->size.y--;
		else if (event->key.keysym.sym == SDLK_LALT)
			env->alt = True;
		else if (event->key.keysym.sym == SDLK_s)
		{
			if (env->ctrl == True)
				save_file(env);
			else
				env->brush = env->spawner_id;
		}
	}
	else if (event->type == SDL_MOUSEMOTION)
	{
		if (env->space && env->mouse1)
		{
			env->map_pos.x += event->motion.xrel;
			env->map_pos.y += event->motion.yrel;
		}
	}
	else if (event->type == SDL_MOUSEBUTTONDOWN)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			if (env->space == 1)
					SDL_SetRelativeMouseMode(SDL_TRUE);
				env->mouse1 = True;
		}
		else if (event->button.button == SDL_BUTTON_RIGHT)
			env->mouse2 = True;
	}
	else if (event->type == SDL_MOUSEBUTTONUP)
	{
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			t_ivec2	mpos;

			mpos = get_mouse_pos();
			env->map->data[env->spawn.y][env->spawn.x] = 0;
			if (is_bounded(mpos, env->brush_canvas))
				switch_brush(mpos, env);
			SDL_SetRelativeMouseMode(SDL_FALSE);
			env->mouse1 = False;
		}
		else if (event->button.button == SDL_BUTTON_RIGHT)
			env->mouse2 = False;
	}
	else if (event->type == SDL_MOUSEWHEEL)
	{
		int		dir;
		t_ivec2	mpos;

		if (event->wheel.y < 0)
			dir = 1;
		else if (event->wheel.y > 0)
			dir = -1;
		else
			dir = 0;
		mpos = get_mouse_pos();
		if (is_bounded(mpos, env->brush_canvas))
		{
			env->brush_c_offset = clamp_int(env->brush_c_offset + dir * 40,
											0, env->max_bcoffset);
		}
		else
		{
			env->brush = env->brush + dir;
			if (env->brush > env->brush_box->tex_id)
				env->brush = 0;
			else if (env->brush < 0)
				env->brush = env->brush_box->tex_id;
			update_c_offset(env);
		}
	}
	return (r);
}
