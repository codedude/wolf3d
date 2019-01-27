/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_rpanels.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 01:09:43 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:09:20 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sdl_m.h"
#include "gen_env.h"
#include "libft.h"

static t_tex	*get_sprite_texture(t_sdl *sdl, int i)
{
	return (&sdl->tex_sprites[i]);
}

static t_color		**create_obj_tex(void *vsdl, t_ivec2 size)
{
	t_u32		nb;
	t_sdl		*sdl;

	sdl = (t_sdl*)vsdl;
	nb = (t_u32)sdl->tex_sprite_nb;
	return (new_panel_tex(sdl, nb, size, get_sprite_texture));
}

static t_tex	*get_sdl_textures(t_sdl *sdl, int i)
{
	return (sdl->tex_walls + i);
}

static t_color		**create_wall_tex(void *vsdl, t_ivec2 size)
{
	t_u32		nb;
	t_sdl		*sdl;

	sdl = (t_sdl*)vsdl;
	nb = (t_u32)sdl->tex_wall_nb;
	return (new_panel_tex(sdl, nb, size, get_sdl_textures));
}

int					init_rpanels(t_sdl *sdl, t_rpanel *rpan)
{
	t_panel		*p;
	t_canvas	p_anch;

	p_anch.pos.x =  ipercent_of(sdl->width, OBJ_OFF_X);
	p_anch.pos.y = ipercent_of(sdl->height, OBJ_OFF_Y);
	p_anch.size.x =  ipercent_of(sdl->width, OBJ_SZ_X);
	p_anch.size.y = ipercent_of(sdl->height, OBJ_SZ_Y);
	p = new_panel((t_u32)sdl->tex_sprite_nb, p_anch,
					sdl, create_obj_tex, sdl->tex_sprites);
	if (p == NULL)
		return (ERROR);
	panel_set_bgcolor(p, 0x222222);
	panel_set_bordercolor(p, 0xababab);
	rpan->p[Object_Panel] = p;
	p = new_panel((t_u32)sdl->tex_wall_nb, p_anch,
					sdl, create_wall_tex, sdl->tex_walls);
	if (p == NULL)
		return (ERROR);
	panel_set_bgcolor(p, 0x222222);
	panel_set_bordercolor(p, 0xababab);
	panel_set_highlight(p);
	rpan->p[Texture_Panel] = p;
	rpan->type = Texture_Panel;
	return (SUCCESS);
}
