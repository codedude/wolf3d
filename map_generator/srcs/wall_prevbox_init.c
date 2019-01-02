/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_prevbox_init.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 23:01:17 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/21 23:12:38 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gen_env.h"
#include "libft.h"

static t_texture	*get_sdl_textures(t_sdl *sdl, int i)
{
	return (sdl->textures + i);
}

static t_color		**create_wall_tex(void *vsdl, t_ivec2 size)
{
	t_u32		nb;
	t_sdl		*sdl;

	sdl = (t_sdl*)vsdl;
	nb = (t_u32)sdl->textures_nb;
	return (new_panel_tex(sdl, nb, size, get_sdl_textures));
}


int					init_wall_pbox(t_panel **pan, t_sdl *sdl)
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
