/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_plus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 18:08:25 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:48:29 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_PLUS_H
# define SDL_PLUS_H

# include "types.h"
# include "ft_type.h"
# include "sdl_m.h"

/*
**		Forward declaration
*/

typedef struct s_canvas		t_canvas;
typedef struct s_color_pick	t_color_pick;

/*
**		Common
*/

int				sdl_clear_color(t_sdl *sdl, unsigned int color);
void			sdl_put_pixel_safe(t_sdl *sdl, t_ivec2 px, t_color c);
t_color			sdl_pixel_pick_from_img(t_sdl *sdl, int x, int y);

t_color			compute_color(t_color_pick *cpick, t_color c);
t_color			tex_px_getscaled(t_tex *tex, int kframe,
					t_ivec2 from, t_ivec2 scale);

# define CANVAS_INIT(x, y)	(t_canvas){(x), (y)}

struct			s_canvas {
	t_ivec2		pos;
	t_ivec2		size;
};

t_bool			is_bounded(t_ivec2 pos, t_canvas canvas);
void			put_pixel_inside_canvas(t_sdl *sdl, t_canvas canvas,
					t_ivec2 pos, unsigned int color);

/*
**		Color picker
*/

struct			s_color_pick {
	t_canvas	canvas_mask;
	t_color		color_mask;
	t_float		cmask_height;
	t_bool		use_col_mask;
	t_bool		use_canvas;
	t_bool		use_transparency;
	t_color		replace;
	t_color		current;
	t_color		ignore_c;
	int			kframe;
};

void			cpick_pick_color_replace(t_sdl *sdl, t_color_pick *cpick,
					t_ivec2 px);

void			cpick_set_color(t_color_pick *cpick, t_u32 color);

void			cpick_set_color_mask(t_color_pick *cpick,
					t_u32 color, t_float height);
void			cpick_unset_color_mask(t_color_pick *cpick);

void			cpick_set_canvas(t_color_pick *cpick, t_canvas canvas);
void			cpick_unset_canvas(t_color_pick *cpick);

void			cpick_set_transparency(t_color_pick *cpick, t_u32 color);
void			cpick_unset_transparency(t_color_pick *cpick);

/*
**		SDL Drawing functions +
*/

void			paint_bucket_tools(t_sdl *sdl, t_color_pick *cpick,
					t_ivec2 pos);

void			draw_canvas_fill(t_sdl *sdl, t_canvas *canvas,
					t_canvas *parent, unsigned int color);
void			draw_canvas_border(t_sdl *sdl, t_canvas canvas,
					t_canvas parent, unsigned int color);

void			draw_line(t_sdl *sdl, t_color_pick *cpick,
					t_ivec2 px1, t_ivec2 px2);
void			draw_vline(t_sdl *sdl, t_color_pick *cpick,
					t_ivec2 from, int y2);
void			draw_hline(t_sdl *sdl, t_color_pick *cpick,
					t_ivec2 from, int x2);

void			sdl_draw_rect(t_sdl *sdl, t_color_pick *cpick,
					t_canvas rect, int line_h);
void			sdl_draw_circle(t_sdl *sdl, t_ivec2 pos,
					t_float radius, t_u32 color);

void			draw_tex(t_sdl *sdl, t_color_pick *cpick,
					t_tex *tex, t_canvas anchor);
void			draw_tex_color(t_sdl *sdl, t_color_pick *cpick,
					t_color *tex, t_canvas anchor);

void			texdata_draw_circle_filled(t_color *tex, t_canvas anchor,
								t_float radius, t_u32 color);
void			texdata_fill_rect(t_color *tex, t_ivec2 t_size,
								t_canvas rect, t_u32 color);
void			texdata_draw_rect(t_color *tex, t_ivec2 t_size,
								t_canvas rect, t_u32 color);
#endif
