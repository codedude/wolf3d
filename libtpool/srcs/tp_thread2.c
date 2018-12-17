/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_thread2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:19:36 by valentin          #+#    #+#             */
/*   Updated: 2018/12/17 12:55:13 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef __APPLE__
# include <sys/sysctl.h>
#elif __linux
# include <sys/sysinfo.h>
#endif

#include <stdlib.h>
#include <unistd.h>
#include "libtpool.h"

int			tp_getnbr_proc(t_tpool *tp)
{
	return (tp->size);
}

#ifdef __APPLE__

int			th_getnbr_proc(void)
{
	int		mib[2];
	int		maxproc;
	size_t	len;

	mib[0] = CTL_HW;
	mib[1] = HW_NCPU;
	len = sizeof(maxproc);
	sysctl(mib, 2, &maxproc, &len, NULL, 0);
	return (maxproc);
}

#elif __linux

int			th_getnbr_proc(void)
{
	return (get_nprocs());
}

#endif
