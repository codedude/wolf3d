/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 19:05:21 by valentin          #+#    #+#             */
/*   Updated: 2018/02/26 12:02:32 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATH_H
# define FT_MATH_H

# include "ft_type.h"

# define ZERO_INT	(0)
# define ZERO_FLOAT	(0.0)
# ifndef M_PI
#  define M_PI		(3.141592653589793)
# endif
# define DEG_TO_RAD (M_PI / 180.)
# define RAD_TO_DEG (180. / M_PI)

t_u32				ft_abs(t_i32 n);
t_i32				ft_min(t_i32 a, t_i32 b);
t_i32				ft_max(t_i32 a, t_i32 b);
t_i32				ft_min3(t_i32 a, t_i32 b, t_i32 c);
t_i32				ft_max3(t_i32 a, t_i32 b, t_i32 c);
t_u32				ft_factorial(t_u32 n);
t_u32				ft_fibonacci(t_u32 n);
t_i32				ft_power(t_i32 n, t_i32 power);
t_u32				ft_sqrt(t_u32 n);
int					ft_isprime(t_u32 n);
t_u32				ft_find_next_prime(t_u32 n);
t_f64				deg_to_rad(t_f64 x);
t_f64				rad_to_deg(t_f64 x);
t_f64				ft_cos(t_f64 x);
t_f64				ft_sin(t_f64 x);
t_f64				ft_tan(t_f64 x);

#endif
