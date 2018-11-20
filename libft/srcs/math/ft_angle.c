/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_angle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 13:48:10 by vparis            #+#    #+#             */
/*   Updated: 2018/02/26 12:02:18 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "ft_type.h"
#include "ft_math.h"

t_f64		deg_to_rad(t_f64 x)
{
	return (x * DEG_TO_RAD);
}

t_f64		rad_to_deg(t_f64 x)
{
	return (x * RAD_TO_DEG);
}

t_f64		ft_cos(t_f64 x)
{
	return (cos(deg_to_rad(x)));
}

t_f64		ft_sin(t_f64 x)
{
	return (sin(deg_to_rad(x)));
}

t_f64		ft_tan(t_f64 x)
{
	return (tan(deg_to_rad(x)));
}
