/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clamp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/28 00:53:52 by valentin          #+#    #+#             */
/*   Updated: 2018/11/29 13:08:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_type.h"

t_f32	clamp_f32(t_f32 f, t_f32 lmin, t_f32 lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}

t_f64	clamp_f64(t_f64 f, t_f64 lmin, t_f64 lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}

t_i32	clamp_i32(t_i32 f, t_i32 lmin, t_i32 lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}

t_i64	clamp_i64(t_i64 f, t_i64 lmin, t_i64 lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}

int		clamp_int(int f, int lmin, int lmax)
{
	if (f < lmin)
		return (lmin);
	else if (f > lmax)
		return (lmax);
	return (f);
}
