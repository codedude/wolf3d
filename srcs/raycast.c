/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 18:57:36 by vparis            #+#    #+#             */
/*   Updated: 2018/11/20 19:09:15 by vparis           ###   ########.fr       */
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

void	raycast(t_sdl *sdl, t_cam *cam, t_map *map, t_ivec2 range)
{
	t_ray	ray;
	int		x;
	t_float	x_projected;
	t_vec2	map_pos;
	t_vec2	side_dist;
	t_vec2	delta_dist;
	t_vec2	step;
	int		hit;
	int		side;
	int		y;
	t_float	wall_z;

	ray.pos = cam->pos;
	ray.dir = VEC2_ZERO;
	x = range.x;
	while (x < range.y)
	{
		map_pos = VEC2_INIT(floor(cam->pos.x), floor(cam->pos.y));
		x_projected = 2 * x / (t_float)WIDTH - 1.0;
		ray.dir = cam->dir + cam->plane * x_projected;
		delta_dist = VEC2_INIT(fabs(1.0 / ray.dir.x), fabs(1.0 / ray.dir.y));

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
			if (map->data[(int)map_pos.x][(int)map_pos.y] > 0)
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
		int text_id = map->data[(int)map_pos.x][(int)map_pos.y] - 1;
		SDL_Surface *text = sdl_get_texture(text_id);

		double wallX; //where exactly the wall was hit
		if (side == 0)
			wallX = ray.pos.y + wall_z * ray.dir.y;
		else
			wallX = ray.pos.x + wall_z * ray.dir.x;
		wallX -= floor(wallX);

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
			sdl->image[x + y * sdl->width] = (int)color;
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
			sdl->image[x + y * sdl->width] = (int)color;

			color = (getpixel(sdl_get_texture(5), floorTexX, floorTexY) >> 1)
				& 8355711;
			sdl->image[x + (sdl->height - y) * sdl->width] = (int)color;
		}

		//draw the pixels of the stripe as a vertical line
		x++;
	}
}

int			compute_raycast(void *data)
{
	t_algo		*algo;
	t_env		*env;

	algo = (t_algo *)data;
	env = algo->env;
	raycast(&env->sdl, &env->cam, &env->map,
		IVEC2_INIT((int)algo->start, (int)algo->end));
	return (SUCCESS);
}