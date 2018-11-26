/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 15:45:28 by jbulant           #+#    #+#             */
/*   Updated: 2018/11/26 16:21:47 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "env.h"
#include "raycast.h"

static t_ivec2	init_draw(int line_height, t_sdl *sdl, t_hit_infos *infos)
{
	t_ivec2		draw;

	draw.x = -line_height / 2.0 + sdl->height / 2.0;
	if(draw.x < 0)
		draw.x = 0;
	draw.y = line_height / 2.0 + sdl->height / 2.0;
	if(draw.y >= (int)sdl->height)
		draw.y = sdl->height - 1;
	return (draw);
}

void			rc_render(t_sdl *sdl, t_map *map, t_hit_infos *infos, int x)
{
	t_ivec2		draw;
	int			line_height;
	int			y;

	line_height = (int)((t_float)sdl->height / infos->z);
	draw = init_draw(line_height, sdl, infos);
	int text_id = map->data[(int)infos->map.x][(int)infos->map.y] - 1;
	SDL_Surface *text = sdl_get_texture(text_id);

	double wallX; //where exactly the wall was hit
	if (infos->side == 0)
		wallX = infos->ray.pos.y + infos->z * infos->ray.dir.y;
	else
		wallX = infos->ray.pos.x + infos->z * infos->ray.dir.x;
	wallX -= floor(wallX);

	t_color 			color;
	//x coordinate on the texture
	int texX = (int)(wallX * (double)text->w);
	if(infos->side == 0 && infos->ray.dir.x > 0)
		texX = text->w - texX - 1;
	if(infos->side == 1 && infos->ray.dir.y < 0)
		texX = text->w - texX - 1;
	for(y = draw.x; y<draw.y; y++)
	{
		int d = y * 256 - sdl->height * 128 + line_height * 128;  //256 and 128 factors to avoid floats
		// TODO: avoid the division to speed this up
		int texY = ((d * text->w) / line_height) / 256;

		//Uint32 color = pixels[text->pitch * texY + texX];
		color = sdl_get_pixel(text, texX, texY);
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(infos->side == 1)
			color = (color >> 1) & 8355711;
		sdl->image[x + y * sdl->width] = color;
	}

	//FLOOR CASTING
	double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

	//4 different wall directions possible
	if(infos->side == 0 && infos->ray.dir.x > 0)
	{
		floorXWall = infos->map.x;
		floorYWall = infos->map.y + wallX;
	}
	else if(infos->side == 0 && infos->ray.dir.x < 0)
	{
		floorXWall = infos->map.x + 1.0;
		floorYWall = infos->map.y + wallX;
	}
	else if(infos->side == 1 && infos->ray.dir.y > 0)
	{
		floorXWall = infos->map.x + wallX;
		floorYWall = infos->map.y;
	}
	else
	{
		floorXWall = infos->map.x + wallX;
		floorYWall = infos->map.y + 1.0;
	}

	double distWall, distPlayer, currentDist;

	distWall = infos->z;
	distPlayer = 0.0;

	if (draw.y < 0)
		draw.y = sdl->height; //becomes < 0 when the integer overflows

	//draw the floor from draw.y to the bottom of the screen
	for(y = draw.y; y < (int)sdl->height; y++)
	{
		currentDist = sdl->height / (2.0 * y - sdl->height); //you could make a small lookup table for this instead

		double weight = (currentDist - distPlayer) / (distWall - distPlayer);

		double currentFloorX = weight * floorXWall + (1.0 - weight) * infos->ray.pos.x;
		double currentFloorY = weight * floorYWall + (1.0 - weight) * infos->ray.pos.y;

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
}
