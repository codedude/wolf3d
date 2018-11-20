/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tpool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/27 18:54:21 by valentin          #+#    #+#             */
/*   Updated: 2018/11/20 18:29:32 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTPOOL_H
# define LIBTPOOL_H

# include <pthread.h>
# include <unistd.h>
# include "libft.h"
# include "ft_list.h"

# define TP_AUTO_THREADS	0
# define TP_MASK_ON			0x0F
# define TP_ON_START		0x00
# define TP_ON_EXEC			0x01
# define TP_MIN_THREADS		0
# define TP_MAX_THREADS		128
# define TH_READY			0
# define TH_BUSY			1

typedef struct		s_tp_data {
	int				(*f)(void *);
	void			*param;
}					t_tp_data;

typedef struct		s_tp_queue {
	size_t			size;
	t_list			*tail;
	t_list			*head;
}					t_tp_queue;

struct s_tpool;

typedef struct		s_thread {
	pthread_t		thread;
	pthread_cond_t	cond;
	pthread_mutex_t	mutex;
	int				state;
	int				id;
	t_tp_data		*data;
	struct s_tpool	*tp;
}					t_thread;

typedef struct		s_tpool {
	int				size;
	int				working_threads;
	pthread_cond_t	cond;
	pthread_mutex_t	mutex;
	int				flag;
	t_thread		*threads;
	t_tp_queue		*queue;
}					t_tpool;

/*
** tp_pool.c & tp_pool2.c
*/

t_tpool				*tp_create(int n, int flag);
void				tp_destroy(t_tpool **tp);
int					tp_add_task(t_tpool *tp, int (*f)(void *), void *data);
int					tp_wait_for_queue(t_tpool *tp);

/*
** tp_thread.c
*/

int					th_start(t_tpool *tp, int i, void *(*f)(void *));
void				*th_fun_start(void *param);
int					th_getnbr_proc(void);

/*
** tp_queue.c
*/

t_tp_queue			*tp_queue_new(void);
void				*tp_queue_shift(t_tp_queue *queue);
int					tp_queue_add(t_tp_queue *queue, void *data, size_t size);
void				tp_queue_del(t_tp_queue **queue);

#endif
