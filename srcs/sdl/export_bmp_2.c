/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/06 13:44:22 by valentin          #+#    #+#             */
/*   Updated: 2019/01/12 20:02:43 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "export_bmp.h"

static void	get_int(int n, char *buff, int bytes)
{
	buff[0] = (char)((unsigned int)n & 0x000000FF);
	buff[1] = (char)(((unsigned int)n & 0x0000FF00) >> 8);
	if (bytes == 4)
	{
		buff[2] = (char)(((unsigned int)n & 0x00FF0000) >> 16);
		buff[3] = (char)(((unsigned int)n & 0xFF000000) >> 24);
	}
}

void		write_int(int fd, int n, int bytes)
{
	char	buff[4];

	get_int(n, (char *)buff, bytes);
	write(fd, buff, (size_t)bytes);
}

void		write_img(t_sdl *sdl, int fd)
{
	int		i;
	int		j;
	size_t	n;
	char	buff[BMP_BUFF];

	n = 0;
	i = sdl->height - 1;
	while (i >= 0)
	{
		j = 0;
		while (j < sdl->width)
		{
			get_int(*((int *)&sdl->image[i * sdl->pitch + j * sdl->bpp]),
				(char *)&buff[n], 4);
			if ((n += 4) == BMP_BUFF)
			{
				write(fd, buff, BMP_BUFF);
				n = 0;
			}
			++j;
		}
		--i;
	}
	if (n > 0)
		write(fd, buff, n);
}
