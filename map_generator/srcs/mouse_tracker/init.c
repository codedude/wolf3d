/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/22 01:30:18 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 00:29:07 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

void			mouse_track_init(t_env *env)
{
		t_mousetrack *mtrack;

		mtrack = &env->mouse;
		ft_bzero(mtrack, sizeof(*mtrack));
		init_get_area(mtrack);
		init_trigger_area(mtrack);
		init_update_area(mtrack);
}
