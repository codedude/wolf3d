/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2018/11/22 17:20:25 by vparis            #+#    #+#             */
/*   Updated: 2018/12/17 13:09:07 by vparis           ###   ########.fr       */
=======
/*   Created: 2018/05/02 16:18:38 by vparis            #+#    #+#             */
/*   Updated: 2018/12/27 03:28:50 by jbulant          ###   ########.fr       */
>>>>>>> 935f2ef52abe6a61f552b7f3beb1fecb27471c00
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "sdl_m.h"
#include "libft.h"
#include "types.h"

void		sdl_put_pixel(t_sdl *sdl, int x, int y, t_color color)
{
	unsigned char	*img;
	int				pos;

	img = sdl->image;
	pos = x * sdl->bpp + y * sdl->pitch;
	img[pos] = color.c.b;
	img[pos + 1] = color.c.g;
	img[pos + 2] = color.c.r;
}

t_color		sdl_get_pixel(t_texture *text, int x, int y)
{
	t_color	pixel;

<<<<<<< HEAD
	pixel.rgba = text->data[x + y * text->w];
	return (pixel);
=======
	if ((tmp = sdl_load_image(filename)) == NULL)
		return (ERROR);
	if ((surf = SDL_ConvertSurfaceFormat(tmp, SDL_PIXELFORMAT_RGB888, 0))
		== NULL)
		return (ERROR);
	SDL_FreeSurface(tmp);
	texture->h = surf->h;
	texture->w = surf->w;
	if ((texture->data = sdl_convert_data(surf)) == NULL
	|| ((texture->name = ft_strdup(filename)) == NULL))
		return (ERROR);
	SDL_FreeSurface(surf);
	return (SUCCESS);
>>>>>>> 935f2ef52abe6a61f552b7f3beb1fecb27471c00
}

void		sdl_get_fps(int show_fps)
{
	static struct timeval	last = {0, 0};
	static int				sum_fps = 60;
	struct timeval			new;

	if (show_fps == 0)
		return ;
	gettimeofday(&new, NULL);
	sum_fps += 1;
	if (new.tv_sec - last.tv_sec >= 1)
	{
		ft_putstr("\r         \rFPS : ");
		ft_putnbr(sum_fps);
		sum_fps = 0;
	}
	last.tv_usec = new.tv_usec;
	last.tv_sec = new.tv_sec;
}

int			sdl_update_texture(t_sdl *sdl)
{
	SDL_LockTexture(sdl->texture, NULL, (void **)&sdl->image, &sdl->pitch);
	return (SUCCESS);
}

int			sdl_render(t_sdl *sdl)
{
	SDL_UnlockTexture(sdl->texture);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
	return (SUCCESS);
}
<<<<<<< HEAD
=======

int					sdl_init_sprites(t_sdl *sdl)
{
	t_stack		*stack;
	int			n;

	sdl->sprites = NULL;
	stack = NULL;
	if ((n = read_file(SPRITES_CONF_FILE, &stack)) <= 0
		|| (sdl->sprites =
			(t_sprite *)ft_memalloc((size_t)n * sizeof(t_sprite)))
		== NULL)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	sdl->sprites_nb = n;
	if (sdl_load_sprites(sdl, &stack) == ERROR)
	{
		ft_stackclear(&stack);
		return (ERROR);
	}
	return (SUCCESS);
}

void				sdl_destroy_textures(t_sdl *sdl)
{
	int	i;

	if (sdl->textures == NULL)
		return ;
	i = 0;
	while (i < sdl->textures_nb)
	{
		free(sdl->textures[i].data);
		free(sdl->textures[i].name);
		i++;
	}
	free(sdl->textures);
	sdl->textures_nb = 0;
	sdl->textures = NULL;
}

void				sdl_destroy_sprites(t_sdl *sdl)
{
		int	i;

	if (sdl->sprites == NULL)
		return ;
	i = 0;
	while (i < sdl->sprites_nb)
	{
		free(sdl->sprites[i].texture.data);
		free(sdl->sprites[i].texture.name);
		i++;
	}
	free(sdl->sprites);
	sdl->sprites_nb = 0;
	sdl->sprites = NULL;
}
>>>>>>> 935f2ef52abe6a61f552b7f3beb1fecb27471c00
