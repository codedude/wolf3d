/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bmp.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/30 16:43:13 by vparis            #+#    #+#             */
/*   Updated: 2019/01/21 17:12:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_BMP_H
# define EXPORT_BMP_H

# include "sdl_m.h"
# include "types.h"

/*
** Max map filsize : 4Mo
*/

# define BMP_BUFF			4096
# define BMP_FILENAME		"data/screenshots/w3d_XXX.bmp"
# define BMP_FILENAME_SIZE	28
# define BMP_PARAM_POS		21

void			write_img(t_sdl *sdl, int fd);
void			write_int(int fd, int n, int bytes);
int				save_img(t_sdl *sdl);

#endif
