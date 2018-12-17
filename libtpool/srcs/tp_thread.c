/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_thread.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:19:36 by valentin          #+#    #+#             */
/*   Updated: 2018/12/17 12:56:39 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include "libft.h"
#include "libtpool.h"

static void	wait_signal(t_thread *th)
{
	pthread_mutex_lock(&(th->mutex));
	while (th->state == TH_READY)
		pthread_cond_wait(&(th->cond), &(th->mutex));
	pthread_mutex_unlock(&(th->mutex));
}

void		*th_fun_start(void *param)
{
	t_tpool		*tp;
	t_thread	*th;

	th = (t_thread *)param;
	tp = th->tp;
	while (1)
	{
		wait_signal(th);
		pthread_mutex_lock(&(tp->mutex));
		tp->working_threads += 1;
		pthread_mutex_unlock(&(tp->mutex));
		(*th->data->f)(th->data->param);
		pthread_mutex_lock(&(th->mutex));
		if ((tp->flag & TP_MASK_MODE) != TP_FPS_MODE)
			free(th->data);
		th->state = TH_READY;
		pthread_mutex_unlock(&(th->mutex));
		pthread_mutex_lock(&(tp->mutex));
		tp->working_threads -= 1;
		pthread_cond_signal(&(tp->cond));
		pthread_mutex_unlock(&(tp->mutex));
	}
	return (param);
}

int			th_start(t_tpool *tp, int i, void *(*f)(void *))
{
	if (pthread_create(&(tp->threads[i].thread), NULL, f,
		(void *)&(tp->threads[i])) != 0)
		return (ERROR);
	pthread_detach(tp->threads[i].thread);
	return (SUCCESS);
}
