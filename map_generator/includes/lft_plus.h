/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lft_plus.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/27 00:05:09 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/27 01:52:25 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LFT_PLUS_H
# define LFT_PLUS_H

# include <stdlib.h>
# include "ft_type.h"
# include "types.h"

t_float			snap_f(t_float snap, t_float height);
t_vec2			vec_snap(t_vec2 snap, t_float height);

void			free_ar_data(void **tab, size_t size);
void			**new_ar_data(size_t height, size_t width);

int				ipercent_of(int of, int percent);

char			*ft_static_itoa(int n);
void			ft_putnbrf_fd(t_float f, int fd, t_u32 prec);

#endif
