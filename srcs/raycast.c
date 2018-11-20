/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:57:36 by vparis            #+#    #+#             */
/*   Updated: 2018/11/20 16:40:55 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft.h"
#include "sdl_m.h"
#include "SDL.h"
#include "raycast.h"

#define MAP_WIDTH 24
#define MAP_HEIGHT 24

int worldMap[WIDTH][HEIGHT] =
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

t_float	fclamp(t_float f, t_float min, t_float max)
{
	if (f < min)
		return (min);
	else if (f > max)
		return (max);
	return (f);
}

t_vec	vec_clamp(t_vec clamp, t_vec min, t_vec max)
{
	t_vec	ret;

	ret.x = fclamp(clamp.x, min.x, max.x);
	ret.y = fclamp(clamp.y, min.y, max.y);
	return (ret);
}

t_vec	move_forward(t_vec from, t_vec to, t_float speed)
{
	t_vec	ret;

	ret = from + to * speed;
	ret = vec_clamp(ret, 0, \
				VEC_INIT((t_float)WIDTH - 0.0001, (t_float) HEIGHT - 0.0001));
	if (worldMap[(int)from.x][(int)ret.y] != 0)
		ret.y = from.y;
	if (worldMap[(int)ret.x][(int)from.y] != 0)
		ret.x = from.x;
	return (ret);
}

t_vec	straf(t_vec from, t_vec to, t_float speed)
{
	to = VEC_INIT(to.y, -to.x);
	return (move_forward(from, to, speed));
}

void	draw_line(t_sdl *sdl, int x, int y_min, int y_max, t_color color)
{
	SDL_SetRenderDrawColor(sdl->renderer,
		color[0] * 255, color[1] * 255, color[2] * 255,
		SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(sdl->renderer, x, y_min, x, y_max);
}

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
    int bpp = surface->format->BytesPerPixel;
    /* Here p is the address to the pixel we want to retrieve */
    Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch(bpp) {
    case 1:
        return *p;

    case 2:
        return *(Uint16 *)p;

    case 3:
        if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
            return *(Uint32 *)p;

    default:
        return 0;       /* shouldn't happen, but avoids warnings */
    }
}

void	raycast(t_sdl *sdl, t_player *player)
{
	t_ray	ray;
	int		x;
	t_float	x_projected;
	t_vec	map_pos;
	t_vec	side_dist;
	t_vec	delta_dist;
	t_vec	step;
	int		hit;
	int		side;
	int		y;
	t_float	wall_z;

	ray.pos = player->pos;
	ray.dir = VEC_ZERO;
	x = 0;
	while (x < WIDTH)
	{
		map_pos = VEC_INIT(floor(player->pos.x), floor(player->pos.y));
		x_projected = 2 * x / (t_float)WIDTH - 1.0;
		ray.dir = player->dir + player->plane * x_projected;
		delta_dist = VEC_INIT(fabs(1.0 / ray.dir.x), fabs(1.0 / ray.dir.y));

		if (ray.dir.x < 0.0)
		{
			step.x = -1.0;
			side_dist.x = (ray.pos.x - map_pos.x) * delta_dist.x;
		}
		else
		{
			step.x = 1.0;
			side_dist.x = (map_pos.x + 1.0 - ray.pos.x) * delta_dist.x;
		}
		if (ray.dir.y < 0.0)
		{
			step.y = -1.0;
			side_dist.y = (ray.pos.y - map_pos.y) * delta_dist.y;
		}
		else
		{
			step.y = 1.0;
			side_dist.y = (map_pos.y + 1.0 - ray.pos.y) * delta_dist.y;
		}

		hit = 0;
		while (hit == 0)
		{
			if (side_dist.x < side_dist.y)
			{
				side_dist.x += delta_dist.x;
				map_pos.x += step.x;
				side = 0;
			}
			else
			{
				side_dist.y += delta_dist.y;
				map_pos.y += step.y;
				side = 1;
			}
			if (worldMap[(int)map_pos.x][(int)map_pos.y] > 0)
				hit = 1;
		}

		if (side == 0)
			wall_z = (map_pos.x - ray.pos.x + (1.0 - step.x) / 2.0) / ray.dir.x;
		else
			wall_z = (map_pos.y - ray.pos.y + (1.0 - step.y) / 2.0) / ray.dir.y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)((t_float)HEIGHT / wall_z);
		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2.0 + HEIGHT / 2.0;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2.0 + HEIGHT / 2.0;
		if(drawEnd >= HEIGHT)
			drawEnd = HEIGHT - 1;

		/*
		//choose wall color
		t_color color;
		switch()
		{
			case 1:  color = COLOR_INIT(1.0, 0.0, 0.0, 0.0);  break; //red
			case 2:  color = COLOR_INIT(0.0, 1.0, 0.0, 0.0);  break; //green
			case 3:  color = COLOR_INIT(0.0, 0.0, 1.0, 0.0);   break; //blue
			case 4:  color = COLOR_INIT(1.0, 1.0, 0.0, 0.0);  break; //white
			default: color = COLOR_INIT(0.8, 0.8, 0.5, 0.0); break; //grey
		}
		//give x and y sides different brightness
		if (side == 1)
		{
			color /= 2.0;
		}
		draw_line(sdl, x, drawStart, drawEnd, color);
		*/
		int text_id = worldMap[(int)map_pos.x][(int)map_pos.y] - 1;
		SDL_Surface *text = sdl_get_texture(text_id);

		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = ray.pos.y + wall_z * ray.dir.y;
		else
			wallX = ray.pos.x + wall_z * ray.dir.x;
		wallX -= floor(wallX);

		unsigned char	c[4];
		Uint32 			color;
		//x coordinate on the texture
		int texX = (int)(wallX * (double)text->w);
		if(side == 0 && ray.dir.x > 0)
			texX = text->w - texX - 1;
		if(side == 1 && ray.dir.y < 0)
			texX = text->w - texX - 1;
		for(y = drawStart; y<drawEnd; y++)
		{
			int d = y * 256 - HEIGHT * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
			// TODO: avoid the division to speed this up
			int texY = ((d * text->w) / lineHeight) / 256;

			//Uint32 color = pixels[text->pitch * texY + texX];
			color = getpixel(text, texX, texY);
			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
			if(side == 1)
				color = (color >> 1) & 8355711;

			*(Uint32*)c = color;
			//printf("%d\n", color);
			SDL_SetRenderDrawColor(sdl->renderer,
				c[0], c[1], c[2],
				SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(sdl->renderer, x, y);
		}

		//FLOOR CASTING
		double floorXWall, floorYWall; //x, y position of the floor texel at the bottom of the wall

		//4 different wall directions possible
		if(side == 0 && ray.dir.x > 0)
		{
			floorXWall = map_pos.x;
			floorYWall = map_pos.y + wallX;
		}
		else if(side == 0 && ray.dir.x < 0)
		{
			floorXWall = map_pos.x + 1.0;
			floorYWall = map_pos.y + wallX;
		}
		else if(side == 1 && ray.dir.y > 0)
		{
			floorXWall = map_pos.x + wallX;
			floorYWall = map_pos.y;
		}
		else
		{
			floorXWall = map_pos.x + wallX;
			floorYWall = map_pos.y + 1.0;
		}

		double distWall, distPlayer, currentDist;

		distWall = wall_z;
		distPlayer = 0.0;

		if (drawEnd < 0)
			drawEnd = HEIGHT; //becomes < 0 when the integer overflows

		//draw the floor from drawEnd to the bottom of the screen
		for(y = drawEnd; y < HEIGHT; y++)
		{
			currentDist = HEIGHT / (2.0 * y - HEIGHT); //you could make a small lookup table for this instead

			double weight = (currentDist - distPlayer) / (distWall - distPlayer);

			double currentFloorX = weight * floorXWall + (1.0 - weight) * ray.pos.x;
			double currentFloorY = weight * floorYWall + (1.0 - weight) * ray.pos.y;

			int floorTexX, floorTexY;
			floorTexX = (int)(currentFloorX * text->w) % text->w;
			floorTexY = (int)(currentFloorY * text->h) % text->h;

			//floor
			color = (getpixel(sdl_get_texture(3), floorTexX, floorTexY) >> 1)
				& 8355711;
			*(Uint32*)c = color;
			SDL_SetRenderDrawColor(sdl->renderer, c[0], c[1], c[2],
				SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(sdl->renderer, x, y);

			color = (getpixel(sdl_get_texture(5), floorTexX, floorTexY) >> 1)
				& 8355711;
			*(Uint32*)c = color;
			SDL_SetRenderDrawColor(sdl->renderer, c[0], c[1], c[2],
				SDL_ALPHA_OPAQUE);
			SDL_RenderDrawPoint(sdl->renderer, x, HEIGHT - y);
		}

		//draw the pixels of the stripe as a vertical line
		x++;
	}
}
