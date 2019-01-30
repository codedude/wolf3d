/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:09:46 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static int			env_init2(t_env *env, char *filename)
{
	t_map		*map;

	map = env->map_info.map;
	env->save_file = filename;
	env->space = 0;
	env->alt = 0;
	if (env->loaded == False)
	{
		env->spawn = IVEC2_INIT(map->size.x / 2, map->size.y / 2);
		env->spawn_rotation = 0;
	}
	env->cpick.kframe = 0;
	button_setactive(env->editor.switch_b[Painter], True);
	mouse_track_init(env);
	palette_init(env);
	init_toolset(&env->toolset);
	return (SUCCESS);
}

static int			load_ui_tex(t_env *env)
{
	static char	*ui_files[UI_FILES_TOTAL] = { UI_F_REPACK };
	t_tex		*ui_tex;
	int			i;

	if (!(ui_tex = (t_tex *)ft_memalloc(sizeof(t_tex) * UI_FILES_TOTAL)))
		return (ERROR);
	env->ui_tex = ui_tex;
	i = 0;
	while (i < UI_FILES_TOTAL)
	{
		if (tex_load(&ui_tex[i], ui_files[i], 1, 1) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int			init_rpanels(t_sdl *sdl, t_rpanel *rpan)
{
	t_panel		*p;
	t_canvas	p_anch;

	p_anch.pos.x = ipercent_of(sdl->width, OBJ_OFF_X);
	p_anch.pos.y = ipercent_of(sdl->height, OBJ_OFF_Y);
	p_anch.size.x = ipercent_of(sdl->width, OBJ_SZ_X);
	p_anch.size.y = ipercent_of(sdl->height, OBJ_SZ_Y);
	p = new_panel((t_u32)sdl->tex_sprite_nb, p_anch, sdl->tex_sprites);
	if (p == NULL)
		return (ERROR);
	panel_set_bgcolor(p, 0x222222);
	panel_set_bordercolor(p, 0xababab);
	rpan->p[Object_Panel] = p;
	p = new_panel((t_u32)sdl->tex_wall_nb, p_anch, sdl->tex_walls);
	if (p == NULL)
		return (ERROR);
	panel_set_bgcolor(p, 0x222222);
	panel_set_bordercolor(p, 0xababab);
	panel_set_highlight(p);
	rpan->p[Texture_Panel] = p;
	rpan->type = Texture_Panel;
	return (SUCCESS);
}

int					env_init(t_env *env, char *filename)
{
	ft_bzero(env, sizeof(*env));
	if (is_valid_mapfile(filename) == False)
		return (ERROR);
	if (sdl_init(&env->sdl, MAP_GEN_NAME, WIN_X, WIN_Y) == ERROR)
	{
		ft_putstr_fd("SDL2 can't start\n", 2);
		return (ERROR);
	}
	if (load_ui_tex(env) == ERROR
	|| init_map_info(env, &env->map_info, filename) == ERROR
	|| init_rpanels(&env->sdl, &env->rpan) == ERROR
	|| env_create_inspect(env) == ERROR
	|| editor_init(env, &env->sdl, &env->editor) == ERROR)
	{
		perror("W3dEditor");
		return (ERROR);
	}
	return (env_init2(env, filename));
}
