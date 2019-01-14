/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/08 15:49:30 by vparis            #+#    #+#             */
/*   Updated: 2019/01/12 20:15:01 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include "types.h"

# define MAX_OFFSET		600
# define MAX_DEPTH		30.0
# define EFFECT_MASK			0xff
# define EFFECT_MASK_DEPTH		0xff00
# define EFFECT_MASK_COLOR		0xff0000
# define EFFECT_NONE	0
# define EFFECT_SIDE	0x01
# define EFFECT_DEPTH	0x0100
# define EFFECT_FOG		0x0200
# define EFFECT_WATER	0x0400
# define EFFECT_SEPIA	0x010000
# define EFFECT_BAW		0x020000

# define FOG_AMBIENT	VEC3_INIT(153.0, 211.0, 137.0)
# define WATER_AMBIENT	VEC3_INIT(136.0, 210.0, 208.0)

typedef struct s_cam	t_cam;

struct				s_cam {
	t_vec3			(*depth_filter)(t_vec3 color, t_float depth);
	t_vec3			(*color_filter)(t_vec3 color);
	t_vec2			pos;
	t_vec2			dir;
	t_vec2			plane;
	t_float			height;
	t_float			z;
	t_float			z_pos;
	t_float			z_default;
	int				side_filter;
};

#endif