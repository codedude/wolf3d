/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 12:59:23 by vparis            #+#    #+#             */
/*   Updated: 2019/01/24 12:46:30 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define IVEC2_ZERO				(t_ivec2){0, 0}
# define IVEC3_ZERO				(t_ivec3){0, 0, 0}
# define IVEC4_ZERO				(t_ivec4){0, 0, 0, 0}
# define IVEC2_INIT(a, b)		(t_ivec2){(a), (b)}
# define IVEC3_INIT(a, b, c)	(t_ivec3){(a), (b), (c)}
# define IVEC4_INIT(a, b, c, d)	(t_ivec4){(a), (b), (c), (d)}
# define VEC2_ZERO				(t_vec2){0.0, 0.0}
# define VEC3_ZERO				(t_vec3){0.0, 0.0, 0.0}
# define VEC4_ZERO				(t_vec4){0.0, 0.0, 0.0, 0.0}
# define VEC2_INIT(a, b)		(t_vec2){(a), (b)}
# define VEC3_INIT(a, b, c)		(t_vec3){(a), (b), (c)}
# define VEC4_INIT(a, b, c, d)	(t_vec4){(a), (b), (c), (d)}

typedef double			t_float;
typedef int				t_int;
typedef t_int			t_ivec2 __attribute__((ext_vector_type(2)));
typedef t_int			t_ivec3 __attribute__((ext_vector_type(3)));
typedef t_int			t_ivec4 __attribute__((ext_vector_type(4)));
typedef t_float			t_vec2 __attribute__((ext_vector_type(2)));
typedef t_float			t_vec3 __attribute__((ext_vector_type(3)));
typedef t_float			t_vec4 __attribute__((ext_vector_type(4)));

typedef union			u_color {
	unsigned int		rgba;
	struct {
		unsigned char	b;
		unsigned char	g;
		unsigned char	r;
		unsigned char	a;
	}					c;
}						t_color;

typedef unsigned int	t_pixel;

t_float					clamp_float(t_float clamp, t_float min, t_float max);
t_vec2					clamp_vec2(t_vec2 clamp, t_vec2 min, t_vec2 max);
t_ivec2					clamp_ivec2(t_ivec2 clamp, t_ivec2 min, t_ivec2 max);
char					*concat_path_file(char *path, char *filename);

t_vec2					vec_rotate(t_vec2 v, t_float angle);
t_vec2					vec_rotate_vec(t_vec2 v1, t_vec2 v2);
t_float					vec_dot(t_vec2 v1, t_vec2 v2);
t_float					vec_len(t_vec2 v1);
t_vec2					vec_norm(t_vec2 v1);

#endif
