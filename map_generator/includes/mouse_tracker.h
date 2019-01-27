/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_tracker.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 17:58:31 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:51:48 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOUSE_TRACKER_H
# define MOUSE_TRACKER_H

/*
**		Forward declaration
*/

typedef struct s_mousetrack		t_mousetrack;

typedef struct s_env			t_env;

/*
**		Tracker
*/

enum			e_win_area {
	Map_window,
	Map_properties_buttons,
	Inspector,
	Tools_buttons,
	Right_Panel,
	Max_Win_Area,
	Not_On_Window = Max_Win_Area
};

enum			e_mb_status {
	Mouse_no_clic,
	Mouse_Press,
	Mouse_Hold,
	Mouse_Release
};

struct			s_mousetrack {
	t_bool		(*get_area[Max_Win_Area])(t_env *);
	void		(*trigger[Max_Win_Area])(t_env *);
	void		(*update[Max_Win_Area])(t_env *);
	t_ivec2		last_pos;
	t_ivec2		rel_pos;
	t_ivec2		pos;
	t_ivec2		record_pos_b;
	t_vec2		obj_offset;
	t_u32		area;
	t_bool		b1;
	t_u32		b1_status;
	t_bool		b2;
	t_bool		b2_cancel_b1;
	t_bool		is_editing;
	t_bool		no_trigger;
	t_u32		button_index;
	int			wheel;
};

void			mouse_track_init(t_env *env);

void			mouse_track_update_area(t_env *env);
void			mouse_button_setstate(t_env *env, int button, t_bool state);

t_ivec2			get_mouse_pos(void);
void			update_mouse_pos(t_env *env);

/*
**		Tracker - Update
*/

void			init_update_area(t_mousetrack *mtrack);
void			u_area_mw(t_env *env);

/*
**		Tracker - Trigger
*/

void			init_trigger_area(t_mousetrack *mtrack);
void			t_mw_painter(t_env *env);
void			t_area_mw(t_env *env);
void			t_area_rpan(t_env *env);

/*
**		Tracker - Get Area
*/

void			init_get_area(t_mousetrack *mtrack);
t_bool			g_area_mw(t_env *env);

#endif
