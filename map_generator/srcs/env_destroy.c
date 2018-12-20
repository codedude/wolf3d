/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/19 16:09:02 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"


static void		ask_saving(t_env *env)
{
	char	str[5];
	ssize_t	r;

	ft_putstr("W3dEditor: modification occurs\n");
	ft_putstr("  Would you like to save (Yes/No): ");
	while ((r = read(0, str, 4)) > 0)
	{
		str[r - 1] = '\0';
		ft_strtolower(str);
		if (ft_strequ("yes", str) || ft_strequ("y", str))
		{
			save_file(env);
			break ;
		}
		if (ft_strequ("no", str) || ft_strequ("n", str))
			break ;
		ft_putstr("Please answer by [Yes] or [No]\n");
		ft_putstr("  Would you like to save (Yes/No): ");
	}
}

void			env_destroy(t_env *env)
{
	sdl_destroy_textures(&env->sdl);
	sdl_destroy(&env->sdl);
	if (env->saved == False)
		ask_saving(env);
	destroy_map(env->map);
	panel_destroy(&env->obj_pan);
	panel_destroy(&env->brush_pan);
}
