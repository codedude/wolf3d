/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:11:31 by vparis            #+#    #+#             */
/*   Updated: 2019/01/18 17:16:58 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_H
# define TEXT_H

# include "sdl_m.h"
# include "types.h"
# include "ft_type.h"
# include "texture.h"

# define FONT_PATH "data/font/big_pixel.otf"

typedef struct s_text	t_text;

struct				s_text {
	t_tex			font_little;
	t_tex			font_big;
};

int					text_init(t_text *text);
void				text_destroy(t_text *text);
int					text_error(char *info);
void				*text_error_null(char *info);

int					text_load_all(t_text *text);

#endif
