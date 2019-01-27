/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inspector_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/26 22:47:49 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/26 22:55:27 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

int					env_create_inspect(t_env *env)
{
	t_canvas	anchor;

	anchor.size.x = ipercent_of(env->sdl.width, INSPECT_SZ_X);
	anchor.size.y = ipercent_of(env->sdl.height, INSPECT_SZ_Y);
	anchor.pos.y = ipercent_of(env->sdl.height, INSPECT_TOP_P_Y);
	anchor.pos.x = ipercent_of(env->sdl.width, INSPECT_TOP_P_X);
	if (create_painter_inpector(env, anchor) == ERROR
	|| create_world_inpector(env, anchor) == ERROR
	|| create_door_inpector(env, anchor) == ERROR
	|| create_object_edit_inpector(env, anchor) == ERROR)
		return (ERROR);
	env->editor.mode = Painter;
	return (env_create_mprops(env));
}
