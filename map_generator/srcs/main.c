/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/04 01:03:08 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

int				sdl_clear_color(t_sdl *sdl, unsigned int color)
{
	t_ivec2		i;

	i.y = 0;
	while (i.y < sdl->height)
	{
		i.x = 0;
		while (i.x < sdl->width)
		{
			sdl->image[i.x + i.y * sdl->width] = color;
			i.x++;
		}
		i.y++;
	}
	return (SUCCESS);
}

t_map		*create_new_map(t_ivec2 size)
{
	t_map	*map;
	int		i;

	if (!(map = (t_map*)malloc(sizeof(*map))))
		return (NULL);
	map->size = size;
	if (!(map->data = (int **)ft_memalloc(sizeof(int *) * MAX_SIZE_Y)))
		return (NULL);
	i = 0;
	while (i < MAX_SIZE_Y)
	{
		if (!(map->data[i] = (int *)ft_memalloc(sizeof(int) * MAX_SIZE_X)))
			return (NULL);
		i++;
	}
	return (map);
}

void		destroy_map(t_map *map)
{
	int		i;

	if (!map)
		return ;
	if (map->data)
	{
		i = 0;
		while (i < MAX_SIZE_Y)
		{
			if (map->data[i])
				free(map->data[i]);
			i++;
		}
		free(map->data);
	}
	free(map);
}

t_ivec2		map_to_center(t_env *env)
{
	t_ivec2		offset;
	t_ivec2		center;

	center = env->grid.pos + (env->grid.size / 2);
	offset.x = (int)(((t_float)env->map->size.x
					* (t_float)env->node_size * env->zoom) / 2.0);
	offset.y = (int)(((t_float)env->map->size.y
					* (t_float)env->node_size * env->zoom) / 2.0);
	center -= offset;
	return (center);
}

void		init_grid(t_env *env, t_sdl *sdl)
{
	env->grid.size.x = ipercent_of(sdl->width, GRID_PERC_X - (GRID_OFF_X * 2));
	env->grid.size.y = ipercent_of(sdl->height, 100 - (GRID_OFF_Y * 2));
	env->grid.pos.x = ipercent_of(sdl->width, GRID_OFF_X);
	env->grid.pos.y = ipercent_of(sdl->height, GRID_OFF_Y);
	if (env->grid.pos.y < env->grid.pos.x)
		env->node_size = env->grid.pos.y;
	else
		env->node_size = env->grid.pos.x;
	env->zoom = 1.0;
	env->map_pos = map_to_center(env);
	env->space = 0;
	env->alt = 0;
	env->mouse2 = 0;
}

unsigned int	get_brush_color(int tex_index)
{
	static unsigned int		color[TEX_COUNT];
	static unsigned int		loaded = False;
	char					c[3];
	int						i;

	if (loaded == False)
	{
		i = 0;
		while (i < TEX_COUNT)
		{
			c[0] = (char)(255.0 * ((t_float)(i + 2) / (t_float)TEX_COUNT + 3));
			c[1] = (char)(255.0 * ((t_float)(i + 2) / (t_float)TEX_COUNT));
			c[2] = (char)(255.0 * ((t_float)(i + 2) * 1.5 / (t_float)TEX_COUNT));
			color[i] = (unsigned int)(c[0] | (c[1] << 8) | (c[2] << 16));
			i++;
		}
		loaded = True;
	}
	return (color[tex_index]);
}

void		init_brush(t_env *env, t_sdl *sdl)
{
	int			y;
	t_tex_pbox	*box;

	if (sdl->width < sdl->height)
		env->brush_prev.size = ipercent_of(sdl->width, BRUSH_C_SIZE);
	else
		env->brush_prev.size = ipercent_of(sdl->height, BRUSH_C_SIZE);
	env->brush_prev.pos.x = env->brush_box->canvas.pos.x;
	env->brush_prev.pos.y = env->brush_canvas.pos.y + env->brush_canvas.size.y;
	env->brush_prev.pos.y += env->brush_prev.size.y / 2;
	box =  env->brush_box;
	y = env->brush_box->canvas.pos.y;
	while ((box = box->next))
	{
		if (box->canvas.pos.y < y)
			y = box->canvas.pos.y;
	}
	env->max_bcoffset = (env->brush_box->canvas.pos.y - y)
				- env->brush_canvas.size.y
				+ (int)(env->brush_box->canvas.size.y * 1.5);
}

t_tex_pbox	*create_brush_boxes(t_sdl *sdl)
{
	t_tex_pbox	*box;
	t_tex_pbox	*new;
	SDL_Surface	*surf;
	int			i;
	int			pos_y;

	i = 0;
	box = NULL;
	pos_y = ipercent_of(sdl->height, GRID_OFF_Y * 2);
	while ((surf = sdl_get_texture(i)))
	{
		if ((new = new_tex_previewbox(sdl, surf, i)))
		{
			tex_previewbox_add(&box, new);
			new->canvas.pos.x = ipercent_of(sdl->width,
									100 - (100 - GRID_PERC_X) / 2);
			new->canvas.pos.y = pos_y + (int)(box->canvas.size.y * 1.5) * i;
			new->canvas.pos.x -= box->canvas.size.x;
		}
		i++;
	}
	return (box);
}

int			env_init(t_env *env)
{
	if (sdl_init(&env->sdl, MAP_GEN_NAME, 1280, 720) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if (sdl_init_textures() == ERROR)
	{
		ft_putstr_fd("Can't load textures\n", 2);
		return (ERROR);
	}
	if (!(env->map = create_new_map(IVEC2_INIT(DEF_SIZE_X, DEF_SIZE_Y)))
	|| !(env->brush_box = create_brush_boxes(&env->sdl)))
	{
		perror("Wolf3d: ");
		return (ERROR);
	}
	init_grid(env, &env->sdl);
	env->brush = 0;
	env->brush_canvas.size.x = ipercent_of(env->sdl.width, BRUSH_PAN_SIZE_X);
	env->brush_canvas.size.y = ipercent_of(env->sdl.height, BRUSH_PAN_SIZE_Y);
	env->brush_canvas.pos.x = ipercent_of(env->sdl.width, BRUSH_PAN_OFF_X);
	env->brush_canvas.pos.y = ipercent_of(env->sdl.height, BRUSH_PAN_OFF_Y);
	init_brush(env, &env->sdl);
	env->mouse1 = 0;
	env->space = 0;
	env->brush_c_offset = 0;
	env->spawner_id = env->brush_box->tex_id + 1;
	return (SUCCESS);
}

void		env_destroy(t_env *env)
{
	sdl_destroy_textures();
	sdl_destroy(&env->sdl);
	destroy_map(env->map);
	destroy_tex_previewbox(env->brush_box);
}

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

void		switch_brush(t_ivec2 mpos, t_env *env)
{
	t_tex_pbox		*box;
	t_canvas		canvas;

	box = env->brush_box;
	canvas.size = box->canvas.size;
	canvas.pos.x = box->canvas.pos.x;
	while (box)
	{
		canvas.pos.y = box->canvas.pos.y - env->brush_c_offset;
		if (is_bounded(mpos, canvas))
		{
			env->brush = box->tex_id;
			break ;
		}
		box = box->next;
	}
}

t_bool		is_visible_brush(t_env *env, t_tex_pbox **found)
{
	t_tex_pbox	*box;
	int			y;

	box = env->brush_box;
	while (box && box->tex_id != env->brush)
		box = box->next;
	*found = box;
	y = box->canvas.pos.y - env->brush_c_offset;
	if (y > env->brush_canvas.pos.y && y + box->canvas.size.y
						< env->brush_canvas.pos.y + env->brush_canvas.size.y)
		return (True);
	return (False);
}

int			get_new_brush_c_offset(t_env *env, t_tex_pbox *box)
{
	int		elem_shown;
	t_float	offset;

	offset = (t_float)box->canvas.size.y * 1.5;
	elem_shown = (int)((t_float)env->brush_canvas.size.y / offset);
	if (box->canvas.pos.y + box->canvas.size.y >= env->brush_canvas.pos.y + env->brush_canvas.size.y)
		return ((int)((t_float)((box->tex_id + 1) - elem_shown) * offset));
	return ((int)((t_float)(box->tex_id) * offset));
}

void		update_c_offset(t_env *env)
{
	t_tex_pbox	*box;

	if (is_visible_brush(env, &box))
		return ;
	if (box == env->brush_box)
		env->brush_c_offset = env->max_bcoffset;
	else if (box->tex_id == 0)
		env->brush_c_offset = 0;
	else
		env->brush_c_offset = get_new_brush_c_offset(env, box);
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
		if (event->key.keysym.sym == SDLK_SPACE)
		{
			SDL_SetRelativeMouseMode(SDL_FALSE);
			env->space = False;
		}
		if (event->key.keysym.sym == SDLK_LALT)
			env->alt = False;
	}
	else if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_SPACE)
		{
			if (env->mouse1 == 1)
				SDL_SetRelativeMouseMode(SDL_TRUE);
			env->space = True;
		}
		else if (event->key.keysym.sym == SDLK_r)
			env->map_pos = map_to_center(env);
		else if (event->key.keysym.sym == SDLK_t
			&& env->map->size.x < MAX_SIZE_X)
			env->map->size.x++;
		else if (event->key.keysym.sym == SDLK_y
			&& env->map->size.x > MIN_SIZE_X)
			env->map->size.x--;
		else if (event->key.keysym.sym == SDLK_g
			&& env->map->size.y < MAX_SIZE_Y)
			env->map->size.y++;
		else if (event->key.keysym.sym == SDLK_h
			&& env->map->size.y > MIN_SIZE_Y)
			env->map->size.y--;
		else if (event->key.keysym.sym == SDLK_LALT)
			env->alt = True;
		else if (event->key.keysym.sym == SDLK_s)
		env->brush = env->spawner_id;
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

int		ipercent_of(int of, int percent)
{
	return (of * percent / 100);
}

void		put_pixel_to_image(t_sdl *sdl, t_ivec2 pos, unsigned int color)
{
	if (pos.x >= 0 && pos.x < sdl->width)
	{
		if (pos.y >= 0 && pos.y < sdl->height)
		{
			sdl->image[pos.x + pos.y *sdl->width] = color;
		}
	}
}

void		draw_line(t_sdl *sdl, t_ivec2 pos, unsigned int color,
					int size_dir[2])
{
	t_ivec2		end;

	end = pos;
	if (size_dir[1] == 0)
		while (pos.x < end.x + size_dir[0])
		{
			put_pixel_to_image(sdl, pos, color);
			pos.x++;
		}
	else
		while (pos.y < end.y + size_dir[0])
		{
			put_pixel_to_image(sdl, pos, color);
			pos.y++;
		}
}

t_bool		is_bounded(t_ivec2 pos, t_canvas canvas)
{
	if (pos.x >= canvas.pos.x && pos.x < canvas.pos.x + canvas.size.x
	&& pos.y >= canvas.pos.y && pos.y < canvas.pos.y + canvas.size.y)
		return (True);
	return (False);
}

void		put_pixel_inside_canvas(t_sdl *sdl, t_canvas canvas, t_ivec2 pos,
								unsigned int color)
{
	canvas.pos += 1;
	if (canvas.size.x > 1)
		canvas.size -= 2;
	if (canvas.size.x == 0 || is_bounded(pos, canvas))
		put_pixel_to_image(sdl, pos, color);
}

void		draw_canvas_border(t_sdl *sdl, t_canvas canvas, t_canvas parent,
							unsigned int color)
{
	t_ivec2		pos;
	t_ivec2		end;

	pos = canvas.pos;
	end = pos + canvas.size;
	while (pos.x < end.x)
	{
		put_pixel_inside_canvas(sdl, parent, pos, color);
		put_pixel_inside_canvas(sdl, parent, IVEC2_INIT(pos.x, end.y), color);
		pos.x++;
	}
	pos = canvas.pos;
	while (pos.y < end.y)
	{
		put_pixel_inside_canvas(sdl, parent, pos, color);
		put_pixel_inside_canvas(sdl, parent, IVEC2_INIT(end.x, pos.y), color);
		pos.y++;
	}
}


void		draw_canvas_fill(t_sdl *sdl, t_canvas canvas, t_canvas parent,
							unsigned int color)
{
	t_ivec2		pos;
	t_ivec2		end;

	pos.x = canvas.pos.x;
	end = pos + (canvas.size);
	while (++pos.x < end.x)
	{
		pos.y = canvas.pos.y + 1;
		while (pos.y < end.y)
		{
			put_pixel_inside_canvas(sdl, parent, pos, color);
			pos.y++;
		}
	}
}

void		draw_node_tex(t_sdl *sdl, t_env *env, t_canvas canvas, t_ivec2 mapi)
{
	SDL_Surface	*surf;
	t_ivec2		i;
	t_ivec2		px;

	if (env->map->data[mapi.y][mapi.x] == 0)
	{
		draw_canvas_fill(sdl, canvas, env->grid, 0x853030);
		return ;
	}
	else if (env->map->data[mapi.y][mapi.x] - 1 == env->spawner_id)
	{
		draw_canvas_fill(sdl, canvas, env->grid, 0x303085);
		return ;
	}
	surf = sdl_get_texture(env->map->data[mapi.y][mapi.x] - 1);
	i.y = 0;
	while (i.y < canvas.size.y)
	{
		px.y = (int)((t_float)surf->h * ((t_float)i.y / (t_float)canvas.size.y));
		i.x = 0;
		while (i.x < canvas.size.x)
		{
			px.x = (int)((t_float)surf->w * ((t_float)i.x / (t_float)canvas.size.x));
			put_pixel_inside_canvas(sdl, env->grid,
							canvas.pos + i, sdl_get_pixel(surf, px.x, px.y).c);
			i.x++;
		}
		i.y++;
	}
}

void		draw_node(t_env *env, t_sdl *sdl, t_ivec2 i)
{
	t_canvas		canvas;
	t_ivec2			node_size;

	node_size = IVEC2_INIT((int)((t_float)env->node_size * env->zoom),
						((int)((t_float)env->node_size * env->zoom)));
	canvas.pos = env->map_pos + (i * node_size);
	canvas.size = node_size;
	draw_node_tex(sdl, env, canvas, i);
	draw_canvas_border(sdl, canvas, env->grid, 0);
}

int			get_min_index(t_env *env, int pos[2], int max, int g_size)
{
	int		min;

	if (pos[0] >= pos[1] + g_size)
		min = max;
	else if (pos[0] > pos[1])
		min = 0;
	else
	{
		min = pos[1] - pos[0];
		min = (int)((t_float)min / ((t_float)env->node_size * env->zoom));
	}
	return (min);
}

t_ivec2		get_node_min(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		i;

	i = 0;
	bounds = get_map_boundaries(env);
	i.x = get_min_index(env, (int[2]){bounds.pos.x, env->grid.pos.x},
						env->map->size.x, env->grid.size.x);
	i.y = get_min_index(env, (int[2]){bounds.pos.y, env->grid.pos.y},
						env->map->size.y, env->grid.size.y);
	return (i);
}

int			get_max_index(t_env *env, int pos[2], int size[2])
{
	int		factor;
	int		max;

	factor = (int)((t_float)size[0] * ((t_float)env->node_size * env->zoom));
	if (pos[0] + factor <= pos[1])
		max = 0;
	else if (pos[0] + factor < pos[1] + size[1])
		max = size[0];
	else
	{
		max = (pos[0] + factor) - (pos[1] + size[1]);
		max = (int)((t_float)max / ((t_float)env->node_size * env->zoom));
		max = size[0] - max;
	}
	return (max);
}

t_ivec2		get_node_max(t_env *env, t_map *map)
{
	t_ivec2		i;

	i.x = get_max_index(env, (int[2]){env->map_pos.x, env->grid.pos.x},
							(int[2]){env->map->size.x, env->grid.size.x});
	i.y = get_max_index(env, (int[2]){env->map_pos.y, env->grid.pos.y},
							(int[2]){env->map->size.y, env->grid.size.y});
	return (IVEC2_INIT(map->size.x, map->size.y));
}

void		draw_grid_lines(t_env *env, t_sdl *sdl)
{
	t_ivec2		i;
	t_ivec2		i_min;
	t_ivec2		i_max;

	i_min = get_node_min(env);
	i_max = get_node_max(env, env->map);
	i.y = i_min.y;
	while (i.y < i_max.y)
	{
		i.x = i_min.x;
		while (i.x < i_max.x)
		{
			draw_node(env, sdl, i);
			i.x++;
		}
		i.y++;
	}
}

void		draw_brushes(t_tex_pbox *box, t_canvas parent, t_sdl *sdl,
						t_env *env)
{
	t_ivec2		i;
	t_ivec2		px;
	t_color		color;
	t_canvas	current;

	if (!box)
		return ;
	draw_brushes(box->next, parent, sdl, env);
	current = box->canvas;
	current.pos.y -= env->brush_c_offset;
	if (current.pos.y >= parent.pos.y + parent.size.y
	|| current.pos.y + current.size.y < parent.pos.y)
		return ;
	i.y = 0;
	while (i.y < current.size.y)
	{
		i.x = 0;
		while (i.x < current.size.x)
		{
			px = current.pos + i;
			color = box->tex_data[i.x + i.y * current.size.y];
			if ((int)env->brush != box->tex_id)
				color.c = (color.c >> 2) & 0x3f3f3f;
			put_pixel_inside_canvas(sdl, parent, px, color.c);
			i.x++;
		}
		i.y++;
	}
}

void		draw_brush_preview(t_env *env, t_sdl *sdl)
{
	t_ivec2		px;
	t_canvas	canvas;
	t_ivec2		i;
	SDL_Surface	*surf;

	draw_canvas_border(sdl, env->grid, CANVAS_INIT(0, 0), 0x777777);
	if (env->brush == env->spawner_id)
	{
		draw_canvas_fill(sdl, env->brush_prev, CANVAS_INIT(0, 0),
						0x303080);
		return ;
	}
	surf = sdl_get_texture(env->brush);
	canvas = env->brush_prev;
	canvas.size -= 1;
	i.y = 0;
	while (i.y < canvas.size.y)
	{
		px.y = (int)((t_float)surf->h
				* ((t_float)i.y / (t_float)canvas.size.y));
		i.x = 0;
		while (i.x < canvas.size.x)
		{
			px.x = (int)((t_float)surf->w
				* ((t_float)i.x / (t_float)canvas.size.x));
			put_pixel_inside_canvas(sdl, CANVAS_INIT(0, 0), canvas.pos + i + 1,
									sdl_get_pixel(surf, px.x, px.y).c);
			i.x++;
		}
		i.y++;
	}
}

void		draw_grid(t_env *env, t_sdl *sdl)
{
	t_ivec2		g_pos;

	sdl_clear_color(sdl, 0x101010);
	g_pos = IVEC2_INIT(ipercent_of(sdl->width, GRID_OFF_X),
					ipercent_of(sdl->height, GRID_OFF_Y));
	draw_canvas_fill(sdl, env->grid, CANVAS_INIT(0, 0), 0x252525);
	draw_grid_lines(env, sdl);
	draw_brush_preview(env, sdl);
	draw_canvas_border(sdl, env->brush_prev, CANVAS_INIT(0, 0), 0x777777);
	draw_canvas_fill(sdl, env->brush_canvas, CANVAS_INIT(0, 0), 0x252525);
	draw_canvas_border(sdl, env->brush_canvas, CANVAS_INIT(0, 0), 0x777777);
	draw_brushes(env->brush_box, env->brush_canvas, sdl, env);
}

t_bool		drawing_node(t_env *env, t_ivec2 mpos, t_ivec2 node)
{
	t_canvas	canvas;

	canvas.size = (int)((t_float)env->node_size * env->zoom);
	canvas.pos = env->map_pos + node * canvas.size;
	if (is_bounded(mpos, canvas))
		return (True);
	return (False);
}

t_canvas	get_map_boundaries(t_env *env)
{
	t_canvas	bounds;

	bounds.pos = env->map_pos;
	bounds.size = env->map->size * env->node_size;
	bounds.size.x = (int)((t_float)bounds.size.x * env->zoom);
	bounds.size.y = (int)((t_float)bounds.size.y * env->zoom);
	return (bounds);
}

t_ivec2		mpos_to_map_index(t_canvas bounds, t_ivec2 mpos, t_env *env)
{
	mpos -= bounds.pos;
	mpos.x = (int)((t_float)mpos.x / ((t_float)env->node_size * env->zoom));
	mpos.y = (int)((t_float)mpos.y / ((t_float)env->node_size * env->zoom));
	return (mpos);
}

void		disable_old_spawn(t_map *map, int brush)
{
	t_ivec2		i;
	int			found;

	found = 0;
	i.y = 0;
	while (!found && i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
		// printf("%d %d\n", brush - 1, env->spawner_id);
			if (map->data[i.y][i.x] == brush)
			{
				map->data[i.y][i.x] = 0;
				found = 1;
				break ;
			}
			i.x++;
		}
		i.y++;
	}
}

void		draw_on_map(t_env *env, int brush)
{
	t_canvas	bounds;
	t_ivec2		mpos;

	mpos = get_mouse_pos();
	bounds = get_map_boundaries(env);
	if (is_bounded(mpos, env->grid) && is_bounded(mpos, bounds))
	{
		mpos = mpos_to_map_index(bounds, mpos, env);
		if (brush - 1 == env->spawner_id)
			disable_old_spawn(env->map, brush);
		env->map->data[mpos.y][mpos.x] = brush;
	}
}

t_ivec2		get_mouse_pos(void)
{
	int			x;
	int			y;

	SDL_PumpEvents();
	SDL_GetMouseState(&x, &y);
	return (IVEC2_INIT(x, y));
}

void		pick_tile(t_env *env)
{
	t_canvas	bounds;
	t_ivec2		mpos;

	mpos = get_mouse_pos();
	bounds = get_map_boundaries(env);
	if (is_bounded(mpos, env->grid) && is_bounded(mpos, bounds))
	{
		mpos = mpos_to_map_index(bounds, mpos, env);
		if ((int)env->map->data[mpos.y][mpos.x] > 0)
			env->brush = (int)env->map->data[mpos.y][mpos.x] - 1;
	}
}

void		update_actions(t_env *env)
{
	if (env->mouse2)
		return (draw_on_map(env, 0));
	if (!env->mouse1 || env->space)
		return ;
	if (env->alt)
		pick_tile(env);
	else
		draw_on_map(env, (int)(env->brush + 1));
}

void		loop(t_env *env)
{
	int			loop;
	SDL_Event	event;
	const Uint8	*state;

	loop = 1;
	while (loop == 1)
	{
		SDL_PumpEvents();
		state = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&event))
			loop = manage_binds(&event, env);
		manage_down(state, env);
		if (loop != 1)
			break ;
		update_actions(env);
		draw_grid(env, &env->sdl);
		sdl_render(&env->sdl);
	}
}

int			main(void)
{
	t_env	env;

	if (env_init(&env) == ERROR)
		return (EXIT_FAILURE);
	loop(&env);
	env_destroy(&env);
	return (EXIT_SUCCESS);
}
