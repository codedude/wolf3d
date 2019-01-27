/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mw_painter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:42:01 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:42:20 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static int		remove_wall(t_env *env, t_entity *ent)
{
	if (ent->type != ENTITY_VOID)
	{
		if (ent == env->inspector.door_edit.selected)
			env->inspector.door_edit.selected = NULL;
		entity_destroy(ent, True);
		return (1);
	}
	return (0);
}

static void		mw_update_map(t_env *env, t_map *map, int **mask, t_ivec2 i)
{
	t_entity	*ent;
	int			save[3];
	int			n;

	n = mask[i.y][i.x];
	if (n == 0)
		return ;
	ft_bzero(save, sizeof(save));
	ent = &map->data[i.y][i.x];
	if (n == -1)
		save[0] = remove_wall(env, ent);
	else
	{
		if ((save[1] = (ent->type == ENTITY_VOID)))
			ent->type = ENTITY_WALL;
		if ((save[2] = (ent->tex_id + 1 != n)))
			ent->tex_id = n - 1;
	}
	n = 0;
	while (n < 3)
		env->saved |= save[n++];
}

void			t_mw_painter(t_env *env)
{
	t_ivec2		i;
	t_map		*map;
	t_map_info	*m_inf;

	env->mouse.is_editing = False;
	m_inf = &env->map_info;
	map = m_inf->map;
	i.y = 0;
	while (i.y < map->size.y)
	{
		i.x = 0;
		while (i.x < map->size.x)
		{
			mw_update_map(env, map, m_inf->tmp_data, i);
			i.x++;
		}
		i.y++;
	}
}
