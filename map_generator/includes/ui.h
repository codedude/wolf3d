/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 16:50:42 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 14:59:53 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "ft_type.h"
# include "sdl_m.h"
# include "sdl_plus.h"
# include "types.h"

/*
**		Forward declaration
*/

typedef struct s_panel		t_panel;
typedef struct s_button		t_button;
typedef struct s_checkbox	t_checkbox;
typedef struct s_slider		t_slider;

/*
**		Panels
*/

struct			s_panel {
	t_tex		*tex;
	t_u32		nb_elem;
	t_u32		cursor;
	t_canvas	anchor;
	t_u32		viewable_elem;
	t_canvas	elem_anchor;
	t_ivec2		elem_pos;
	t_color		bg_col;
	t_bool		draw_bg;
	t_color		border_col;
	t_bool		draw_border;
	int			hightlight;
	t_u32		view_min;
	t_u32		view_max;
};

t_color			*new_texdata(t_tex *tex, t_ivec2 size);

t_panel			*new_panel(t_u32 nb_elem, t_canvas anchor, t_tex *elems);
void			panel_destroy(t_panel **pan);
void			panel_set_anchor(t_panel *pan, t_canvas anchor);
void			panel_set_bgcolor(t_panel *pan, t_u32 color);
void			panel_set_bordercolor(t_panel *pan, t_u32 color);
void			panel_set_highlight(t_panel *pan);

void			panel_decrease_view(t_panel *pan);
void			panel_increase_view(t_panel *pan);
void			panel_change_view(t_panel *pan, int move);
void			panel_update_cursor(t_panel *pan, t_u32 new_curs);

t_bool			panel_isinside(t_panel *pan, t_ivec2 point);
int				panel_get_index_by_pos(t_panel *pan, t_ivec2 point);
t_canvas		panel_get_elem_anchor(t_panel *pan, int i);

void			panel_draw(t_sdl *sdl, t_color_pick *cpick, t_panel *pan);

/*
**		Buttons
*/

struct			s_button {
	t_canvas	anchor;
	t_color		*tex;
	t_bool		is_active;
	void		*param;
	void		(*trigger)(void*);
};

t_button		*button_new(t_canvas anchor, t_tex *tex, void *param,
						void (*trigger)(void*));
void			button_setactive(t_button *button, t_bool active);
void			button_destroy(t_button **button);
void			destroy_button_array(t_button **buttons, t_u32 count);

t_bool			button_hover(t_button *button, t_ivec2 pos);
void			button_trigger(t_button *button);

void			button_draw(t_sdl *sdl, t_color_pick *cpick, t_button *button);

void			button_switch(t_button **b_list, t_u32 b_count, t_u32 swtch_id);

/*
**		CheckBox
*/

enum			e_cbox_state {
	Unchecked,
	Check,
	Unavailable
};

struct			s_checkbox {
	t_color		*tex;
	t_canvas	anchor;
	void		*param;
	int			(*get_state)(void *);
	void		(*reverse_state)(void *);
};

t_checkbox		*checkbox_new(t_canvas anchor, t_tex *tex);
void			checkbox_setup(t_checkbox *cbox, void *param,
					void (*reverse_state)(void*), int (*get_state)(void *));
void			checkbox_destroy(t_checkbox **cbox);

t_bool			checkbox_hover(t_checkbox *cbox, t_ivec2 pos);
void			checkbox_clic(t_checkbox *cbox);

void			checkbox_draw(t_sdl *sdl, t_color_pick *cpick,
					t_checkbox *cbox);

/*
**		Slider
*/

enum			e_direction {
	Dir_Horizontal,
	Dir_Vertical
};

struct			s_slider {
	t_color		*slid_img;
	t_ivec2		slid_img_size;
	t_color		*curs_img;
	t_ivec2		curs_img_size;
	t_ivec2		pos;
	t_bool		draw_bar;
	int			direction;
	int			size;
	t_float		step;
	t_float		min_val;
	t_float		max_val;
	t_float		range;
	t_float		val;
};

t_slider		*slider_new(t_ivec2 pos, t_tex *imgs[2],
						t_ivec2 img_size[2]);
void			slider_setup(t_slider *slider, int direction,
						t_vec2 range, t_float step);
void			slider_destroy(t_slider **slider);
t_bool			slider_hover(t_slider *slider, t_ivec2 pos);
void			slider_update_bypos(t_slider *slider, t_ivec2 pos);

void			slider_draw(t_sdl *sdl, t_color_pick *cpick, t_slider *slider);

#endif
