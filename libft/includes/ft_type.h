/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_type.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/24 19:08:37 by valentin          #+#    #+#             */
/*   Updated: 2018/04/09 17:45:01 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_TYPE_H
# define FT_TYPE_H

/*
** Own defines of stdlibs
*/

# if !defined(SUCCESS) && !defined(ERROR)
#  define SUCCESS			(0)
#  define ERROR				(-1)
# endif

# ifndef NULL
#  define NULL				((void *)0)
# endif

# define STDIN				STDIN_FILENO
# define STDOUT				STDOUT_FILENO
# define STDERR				STDERR_FILENO

# define NULL_STR			"(null)"

/*
** Common charsets, and some usefull constants
*/

# define CHARSET_DIGIT		"0123456789"
# define CHARSET_LALPHA		"abcdefghijklmnopqrstuvwxyz"
# define CHARSET_UALPHA		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
# define CHARSET_SPACE		" \t\n\v\r\f"
# define CHARSET_BASE_2		"01"
# define CHARSET_BASE_8		"01234567"
# define CHARSET_BASE_10	"0123456789"
# define CHARSET_BASE_16L	"0123456789abcdef"
# define CHARSET_BASE_16U	"0123456789ABCDEF"
# define CHARSET_BASE_16	"0123456789abcdefABCDEF"
# define CHARSET_NUMBER		"0123456789-+."
# if !defined(INT_MIN) && !defined(INT_MAX)
#  define INT_MAX			(+2147483647)
#  define INT_MIN			(-INT_MAX -1)
# endif
# if !defined(INT64_MIN) && !defined(INT64_MAX)
#  define INT64_MAX			(+9223372036854775807L)
#  define INT64_MIN			(-INT64_MAX -1L)
# endif

/*
** Own types
*/

typedef void				t_void;
typedef char				t_i8;
typedef unsigned char		t_u8;
typedef unsigned short		t_u16;
typedef short				t_i16;
typedef int					t_i32;
typedef unsigned int		t_u32;
typedef long int			t_i64;
typedef unsigned long int	t_u64;
typedef float				t_f32;
typedef double				t_f64;
typedef long double			t_f128;
typedef enum				e_bool
{
	False, True
}							t_bool;

t_f32						clamp_f32(t_f32 f, t_f32 lmin, t_f32 lmax);
t_f64						clamp_f64(t_f64 f, t_f64 lmin, t_f64 lmax);
t_i32						clamp_i32(t_i32 f, t_i32 lmin, t_i32 lmax);
t_i64						clamp_i64(t_i64 f, t_i64 lmin, t_i64 lmax);

#endif
