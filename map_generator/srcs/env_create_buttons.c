/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_create_buttons.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 22:59:30 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/11 04:29:54 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void				TMP_color_buttons(t_env *env)
{
	static t_u32		col[Max_action] = {0x50aa50, 0x5050aa, 0xaa5050, 0xaaa050};
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


static void			buttact_draw_wall(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_setactive(env->act_buttons[Set_Spawn], False);
	button_setactive(env->act_buttons[Erase_Wall], False);
	button_setactive(env->act_buttons[Edit_Obj], False);
	env->inspector.mod = Brush_Select;
	env->rpan.type = Texture_Panel;
	toggle_action(env, Draw_Wall);
}

static void			buttact_set_spawn(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_setactive(env->act_buttons[Draw_Wall], False);
	button_setactive(env->act_buttons[Erase_Wall], False);
	button_setactive(env->act_buttons[Edit_Obj], False);
	env->inspector.mod = Player_Radar;
	env->rpan.type = Texture_Panel;
	toggle_action(env, Set_Spawn);
}

static void			buttact_erase_wall(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_setactive(env->act_buttons[Draw_Wall], False);
	button_setactive(env->act_buttons[Set_Spawn], False);
	button_setactive(env->act_buttons[Edit_Obj], False);
	env->inspector.mod = Brush_Select;
	env->rpan.type = Texture_Panel;
	toggle_action(env, Erase_Wall);
}

static void			buttact_edit_obj(void *v_env)
{
	t_env *env;

	env = (t_env*)v_env;
	button_setactive(env->act_buttons[Draw_Wall], False);
	button_setactive(env->act_buttons[Set_Spawn], False);
	button_setactive(env->act_buttons[Erase_Wall], False);
	env->inspector.mod = Object_Edit;
	env->rpan.type = Object_Panel;
	toggle_action(env, Edit_Obj);
}

int					env_create_buttons(t_env *env)
{
	t_ivec2		offset;
	t_canvas	anchor;

	offset.x = ipercent_of(env->sdl.width, BUTTON_OFFSET);
	offset.y = ipercent_of(env->sdl.height, BUTTON_OFFSET);
	anchor.size.x = ipercent_of(env->sdl.width, BUTTON_SIZE);
	anchor.size.y = ipercent_of(env->sdl.height, BUTTON_SIZE);
	anchor.pos.y = ipercent_of(env->sdl.height, BUTTON_TOP_POS_Y);
	anchor.pos.x = ipercent_of(env->sdl.width, BUTTON_TOP_POS_X);
	env->act_buttons[Draw_Wall] = button_new(anchor, NULL, env,
											buttact_draw_wall);
	anchor.pos.x -= offset.x;
	env->act_buttons[Set_Spawn] = button_new(anchor, NULL, env,
											buttact_set_spawn);
	anchor.pos.x -= offset.x;
	env->act_buttons[Erase_Wall] = button_new(anchor, NULL, env,
											buttact_erase_wall);
	anchor.pos += offset;
	env->act_buttons[Edit_Obj] = button_new(anchor, NULL, env,
											buttact_edit_obj);
	TMP_color_buttons(env);
	return  (env_create_inspect(env));
}
