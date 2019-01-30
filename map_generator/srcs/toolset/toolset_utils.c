/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolset_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/31 00:47:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/30 15:28:18 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void			toolset_use_fx(t_env *env)
{
	t_toolset	*toolset;

	toolset = &env->toolset;
	if (toolset->use_tmp)
	{
		toolset->map_fx[toolset->tmp_type](env);
		toolset->use_tmp = False;
	}
	else
		toolset->map_fx[toolset->type](env);
}

void			toolset_set_type(t_toolset *toolset, t_u32 type)
{
	toolset->type = type;
}

void			toolset_set_tmp_type(t_toolset *toolset, t_u32 type)
{
	toolset->tmp_type = type;
	toolset->use_tmp = True;
}

t_u32			toolset_get_type(t_toolset *toolset)
{
	if (toolset->use_tmp == True)
		return (toolset->tmp_type);
	return (toolset->type);
}
