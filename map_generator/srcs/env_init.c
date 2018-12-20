/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/20 15:51:50 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"


t_texture		*get_sprite_texture(t_sdl *sdl, int i)
{
	return (&sdl->sprites[i].texture);
}

t_color		**create_obj_tex(void *vsdl, t_ivec2 size)
{
	t_u32		nb;
	t_sdl		*sdl;

	sdl = (t_sdl*)vsdl;
	nb = (t_u32)sdl->sprites_nb;
	return (new_panel_tex(sdl, nb, size, get_sprite_texture));
}

int				init_object_pbox(t_panel **pan, t_sdl *sdl)
{
	t_ivec2		pos;
	t_ivec2		size;

	pos.x =  ipercent_of(sdl->width, OBJ_OFF_X);
	pos.y = ipercent_of(sdl->height, OBJ_OFF_Y);
	size.x =  ipercent_of(sdl->width, OBJ_SIZE_X);
	size.y = ipercent_of(sdl->height, OBJ_SIZE_Y);
	(*pan) = new_panel((t_u32)sdl->sprites_nb, CANVAS_INIT(pos, size),
					sdl, create_obj_tex);
	if (!(*pan))
		return (ERROR);
	panel_set_bgcolor((*pan), 0x222222);
	panel_set_bordercolor((*pan), 0xababab);
	return (SUCCESS);
}

t_texture		*get_sdl_textures(t_sdl *sdl, int i)
{
	return (sdl->textures + i);
}

t_color		**create_wall_tex(void *vsdl, t_ivec2 size)
{
	t_u32		nb;
	t_sdl		*sdl;

	sdl = (t_sdl*)vsdl;
	nb = (t_u32)sdl->textures_nb;
	return (new_panel_tex(sdl, nb, size, get_sdl_textures));
}


int				init_wall_pbox(t_panel **pan, t_sdl *sdl)
{
	t_ivec2		pos;
	t_ivec2		size;

	pos.x =  ipercent_of(sdl->width, WTEX_OFF_X);
	pos.y = ipercent_of(sdl->height, WTEX_OFF_Y);
	size.x =  ipercent_of(sdl->width, WTEX_SIZE_X);
	size.y = ipercent_of(sdl->height, WTEX_SIZE_Y);
	*pan = new_panel((t_u32)sdl->textures_nb, CANVAS_INIT(pos, size),
					sdl, create_wall_tex);
	if (!*pan)
		return (ERROR);
	panel_set_bgcolor(*pan, 0x222222);
	panel_set_bordercolor(*pan, 0xababab);
	panel_set_highlight(*pan);
	return (SUCCESS);
}

static void			init_grid(t_env *env, t_sdl *sdl)
{
	env->grid.size.x = ipercent_of(sdl->width, GRID_SIZE_X);
	env->grid.size.y = ipercent_of(sdl->height, GRID_SIZE_Y);
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

static int			env_init2(t_env *env, char *filename)
{
	init_grid(env, &env->sdl);
	env->user_action = Draw_Wall;
	env->save_file = filename;
	env->brush = 0;
	env->mouse1 = 0;
	env->space = 0;
	env->spawn = IVEC2_INIT(env->map->size.x / 2, env->map->size.y / 2);
	env->spawn_rotation = 0;
	env->saved = True;
	init_object_pbox(&env->obj_pan, &env->sdl);
	init_wall_pbox(&env->brush_pan, &env->sdl);
	env->spawner_id = (int)env->brush_pan->nb_elem;
	button_setactive(env->act_buttons[Draw_Wall], True);
	return (SUCCESS);
}

void				buttact_draw_wall(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_setactive(env->act_buttons[Set_Spawn], False);
	button_setactive(env->act_buttons[Erase_Wall], False);
	toggle_action(env, Draw_Wall);
}

void				buttact_set_spawn(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_setactive(env->act_buttons[Draw_Wall], False);
	button_setactive(env->act_buttons[Erase_Wall], False);
	toggle_action(env, Set_Spawn);
}

void				buttact_erase_wall(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_setactive(env->act_buttons[Draw_Wall], False);
	button_setactive(env->act_buttons[Set_Spawn], False);
	toggle_action(env, Erase_Wall);
}

void				TMP_color_buttons(t_env *env)
{
	static t_u32		col[Max_action] = {0x50aa50, 0x5050aa, 0xaa5050};
	t_ivec2				px;
	t_button			*b;
	int					i;

	i = 0;
	while (i < Max_action)
	{
		b = env->act_buttons[i];
		px.y = 0;
		while (px.y < b->anchor.size.y)
		{
			px.x = 0;
			while (px.x < b->anchor.size.x)
			{
				b->tex[px.x + px.y * b->anchor.size.x].rgba = col[i];
				px.x++;
			}
			px.y++;
		}
		i++;
	}
}

int					env_create_buttons(t_env *env)
{
	t_canvas	anchor;

	anchor.size.x = ipercent_of(env->sdl.width, BUTTON_SIZE);
	anchor.size.y = ipercent_of(env->sdl.height, BUTTON_SIZE);
	anchor.pos.y = ipercent_of(env->sdl.height, BUTTON_TOP_POS_Y);
	anchor.pos.x = ipercent_of(env->sdl.width, BUTTON_TOP_POS_X);
	env->act_buttons[Draw_Wall] = button_new(anchor, NULL, env,
											buttact_draw_wall);
	anchor.pos.x -= (int)(anchor.size.x * 1.2);
	env->act_buttons[Set_Spawn] = button_new(anchor, NULL, env,
											buttact_set_spawn);
	anchor.pos.x -= (int)(anchor.size.x * 1.2);
	env->act_buttons[Erase_Wall] = button_new(anchor, NULL, env,
											buttact_erase_wall);
	TMP_color_buttons(env);
	return (SUCCESS);
}

int					env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(*env));
	if (is_valid_mapfile(filename) == False)
		return (ERROR);
	if (sdl_init(&env->sdl, MAP_GEN_NAME, 1280, 720) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if (!(env->map = create_new_map(IVEC2_INIT(DEF_SIZE_X, DEF_SIZE_Y)))
	|| env_create_buttons(env) == ERROR)
	{
		perror("W3dEditor");
		return (ERROR);
	}
	return (env_init2(env, filename));
}
