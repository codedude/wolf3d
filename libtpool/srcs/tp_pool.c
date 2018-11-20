/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_pool.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 22:19:36 by valentin          #+#    #+#             */
/*   Updated: 2018/11/20 18:29:46 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include "libft.h"
#include "libtpool.h"

int			tp_add_task(t_tpool *tp, int (*f)(void *), void *data)
{
	t_tp_data	tp_data;

	tp_data.f = f;
	tp_data.param = data;
	if (tp_queue_add(tp->queue, (void *)&tp_data, sizeof(t_tp_data))
		== ERROR)
		return (ERROR);
	return (SUCCESS);
}

static int	tp_start_all(t_tpool *tp, int flag)
{
	int		i;

	i = 0;
	while (i < tp->size)
	{
		tp->threads[i].tp = tp;
		tp->threads[i].id = i;
		pthread_mutex_init(&(tp->threads[i].mutex), NULL);
		pthread_cond_init(&(tp->threads[i].cond), NULL);
		if ((flag & TP_MASK_ON) == TP_ON_START)
		{
			if (th_start(tp, i, &th_fun_start) == ERROR)
				return (ERROR);
		}
		i++;
	}
	return (SUCCESS);
}

t_tpool		*tp_create(int nb_threads, int flag)
{
	t_tpool	*tmp;

	if (nb_threads < TP_MIN_THREADS || nb_threads > TP_MAX_THREADS)
		return (NULL);
	if ((tmp = (t_tpool *)malloc(sizeof(t_tpool))) == NULL)
		return (NULL);
	tmp->size = (nb_threads == 0) ? th_getnbr_proc() : nb_threads;
	tmp->flag = flag;
	tmp->working_threads = 0;
	pthread_mutex_init(&(tmp->mutex), NULL);
	pthread_cond_init(&(tmp->cond), NULL);
	tmp->threads = (t_thread *)ft_memalloc(sizeof(t_thread) * tmp->size);
	if (tmp->threads == NULL)
	{
		free(tmp);
		return (NULL);
	}
	if ((tmp->queue = tp_queue_new()) == NULL)
	{
		tp_destroy(&tmp);
		return (NULL);
	}
	if (tp_start_all(tmp, flag) == ERROR)
		tp_destroy(&tmp);
	return (tmp);
}

void		tp_destroy(t_tpool **tp)
{
	int			i;
	t_tpool		*tp_t;
	t_thread	*th_t;

	i = 0;
	tp_t = *tp;
	while (i < tp_t->size)
	{
		th_t = &(tp_t->threads[i]);
		pthread_cancel(th_t->thread);
		pthread_mutex_destroy(&(th_t->mutex));
		pthread_cond_destroy(&(th_t->cond));
		i++;
	}
	free(tp_t->threads);
	tp_t->threads = NULL;
	tp_queue_del(&(tp_t->queue));
	pthread_mutex_destroy(&(tp_t->mutex));
	pthread_cond_destroy(&(tp_t->cond));
	free(*tp);
	*tp = NULL;
}
