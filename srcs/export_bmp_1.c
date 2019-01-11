/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/05 11:01:14 by vparis            #+#    #+#             */
/*   Updated: 2019/01/11 12:02:29 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "export_bmp.h"

static void	get_filename(int nb, char *filename)
{
	ft_bzero(filename, BMP_FILENAME_SIZE);
	ft_strcpy(filename, BMP_FILENAME);
	filename[BMP_PARAM_POS] = '0' + (char)(nb / 100);
	filename[BMP_PARAM_POS + 1] = '0' + (char)(nb / 10 - (nb / 100) * 10);
	filename[BMP_PARAM_POS + 2] = '0' + (char)(nb % 10);
}

static int	write_header(int fd, int image_size)
{
	write(fd, "BM", 2);
	write_int(fd, image_size + 54, 4);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x36, 4);
	return (SUCCESS);
}

static int	write_dibheader(t_sdl *sdl, int fd)
{
	write_int(fd, 0x28, 4);
	write_int(fd, sdl->width, 4);
	write_int(fd, sdl->height, 4);
	write_int(fd, 0x01, 2);
	write_int(fd, sdl->bpp * 8, 2);
	write_int(fd, 0x00, 4);
	write_int(fd, sdl->pitch, 4);
	write_int(fd, 0x0B13, 4);
	write_int(fd, 0x0B13, 4);
	write_int(fd, 0x00, 4);
	write_int(fd, 0x00, 4);
	return (SUCCESS);
}

int			save_img(t_sdl *sdl)
{
	char		filename[BMP_FILENAME_SIZE + 1];
	int			fd;
	static int	nb = 0;

	if (nb == 999)
	{
		ft_putendl("Can't save image, limit reached (999)");
		return (SUCCESS);
	}
	get_filename(nb, filename);
	if ((fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0666)) < 0)
		return (ERROR);
	ft_putstr("Saving image... ");
	write_header(fd, (int)sdl->size_buffer);
	write_dibheader(sdl, fd);
	write_img(sdl, fd);
	close(fd);
	nb++;
	ft_putstr("Image saved in ");
	ft_putendl(filename);
	return (SUCCESS);
}
