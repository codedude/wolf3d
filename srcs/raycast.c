/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:57:36 by vparis            #+#    #+#             */
/*   Updated: 2018/11/22 18:25:10 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"



t_vec2	move_forward(t_map *map, t_vec2 from, t_vec2 to, t_float speed)
{
	t_vec2	ret;

	ret = from + to * speed;
	ret = clamp_vec2(ret, 0, \
				VEC2_INIT((t_float)map->width - 0.0001,
					(t_float)map->height - 0.0001));
	if (map->data[(int)from.x][(int)ret.y] != 0)
		ret.y = from.y;
	if (map->data[(int)ret.x][(int)from.y] != 0)
		ret.x = from.x;
	return (ret);
}

t_vec2	straf(t_map *map, t_vec2 from, t_vec2 to, t_float speed)
{
	to = VEC2_INIT(to.y, -to.x);
	return (move_forward(map, from, to, speed));
}

void	draw_line(t_sdl *sdl, int x, t_ivec2 range, int color)
{
	int		i;

	i = range.x;
	while (i < range.y)
	{
		sdl->image[x + i * sdl->width] = color;
		i++;
	}
}

void	render(t_sdl *sdl, t_cam *cam, t_map *map, t_ivec2 range)
{
	int			x;
	int			y;
	t_hit_infos	infos;

	infos.ray.pos = cam->pos;
	x = range.x;
	while (x < range.y)
	{
		infos.map = VEC2_INIT(floor(cam->pos.x), floor(cam->pos.y));
		infos.ray.dir = cam->dir + cam->plane *
			(2.0 * x / (t_float)WIDTH - 1.0);
		raycast(&infos, map);


		//Calculate height of line to draw on screen
		int lineHeight = (int)((t_float)HEIGHT / infos.z);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2.0 + HEIGHT / 2.0;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2.0 + HEIGHT / 2.0;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		int text_id = map->data[(int)infos.map.x][(int)infos.map.y] - 1;
		SDL_Surface *text = sdl_get_texture(text_id);

		double wallX; //where exactly the wall was hit
		if (infos.side == 0)
			wallX = infos.ray.pos.y + infos.z * infos.ray.dir.y;
		else
			wallX = infos.ray.pos.x + infos.z * infos.ray.dir.x;
		wallX -= floor(wallX);

		t_color 			color;
		//x coordinate on the texture
		int texX = (int)(wallX * (double)text->w);
		if(infos.side == 0 && infos.ray.dir.x > 0)
			texX = text->w - texX - 1;
		if(infos.side == 1 && infos.ray.dir.y < 0)
			texX = text->w - texX - 1;
		for(y = drawStart; y<drawEnd; y++)
		{
			int d = y * 256 - HEIGHT * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			// TODO: avoid the division to speed this up
			int texY = ((d * text->w) / lineHeight) / 256;

			//Uint32 color = pixels[text->pitch * texY + texX];
			color = sdl_get_pixel(text, texX, texY);
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(infos.side == 1)
				color = (color >> 1) & 8355711;
			sdl->image[x + y * sdl->width] = color;
		}

		//FLOOR CASTING
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(infos.side == 0 && infos.ray.dir.x > 0)
		{
			floorXWall = infos.map.x;
			floorYWall = infos.map.y + wallX;
		}
		else if(infos.side == 0 && infos.ray.dir.x < 0)
		{
			floorXWall = infos.map.x + 1.0;
			floorYWall = infos.map.y + wallX;
		}
		else if(infos.side == 1 && infos.ray.dir.y > 0)
		{
			floorXWall = infos.map.x + wallX;
			floorYWall = infos.map.y;
		}
		else
		{
			floorXWall = infos.map.x + wallX;
			floorYWall = infos.map.y + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = infos.z;
		distPlayer = 0.0;

		if (drawEnd < 0)
			drawEnd = HEIGHT; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(y = drawEnd; y < HEIGHT; y++)
		{
			currentDist = HEIGHT / (2.0 * y - HEIGHT); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * infos.ray.pos.x;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * infos.ray.pos.y;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * text->w) % text->w;
			floorTexY = (int)(currentFloorY * text->h) % text->h;

			//floor
			color = (sdl_get_pixel(sdl_get_texture(3), floorTexX, floorTexY) >> 1)
				& 8355711;
			sdl->image[x + y * sdl->width] = color;

			color = (sdl_get_pixel(sdl_get_texture(5), floorTexX, floorTexY) >> 1)
				& 8355711;
			sdl->image[x + (sdl->height - y) * sdl->width] = color;
		}

		//draw the pixels of the stripe as a vertical line
		x++;
	}
}

int			start_render(void *data)
{
	t_algo		*algo;
	t_env		*env;

	algo = (t_algo *)data;
	env = algo->env;
	render(&env->sdl, &env->cam, &env->map,
		IVEC2_INIT((int)algo->start, (int)algo->end));
	return (SUCCESS);
}