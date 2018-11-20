/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tp_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/02 15:36:45 by vparis            #+#    #+#             */
/*   Updated: 2018/11/20 18:29:54 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_list.h"
#include "libtpool.h"

t_tp_queue		*tp_queue_new(void)
{
	t_tp_queue	*tmp;

	tmp = (t_tp_queue *)malloc(sizeof(t_tp_queue));
	if (tmp == NULL)
		return (NULL);
	tmp->size = 0;
	tmp->head = NULL;
	tmp->tail = NULL;
	return (tmp);
}

void			*tp_queue_shift(t_tp_queue *queue)
{
	void	*data;
	t_list	*tmp;

	tmp = queue->head;
	if (tmp != NULL)
	{
		data = tmp->content;
		tmp = tmp->next;
		ft_lstdelone(&(queue->head), NULL);
		queue->size -= 1;
		queue->head = tmp;
		if (tmp == NULL)
			queue->tail = NULL;
	}
	else
		data = NULL;
	return (data);
}

int				tp_queue_add(t_tp_queue *queue, void *data, size_t size)
{
	t_list		*tmp;

	tmp = ft_lstnew(data, size);
	if (tmp == NULL)
		return (ERROR);
	if (queue->tail == NULL)
	{
		ft_lstadd(&(queue->tail), tmp);
		queue->head = queue->tail;
	}
	else
	{
		ft_lstadd(&(queue->tail->next), tmp);
		queue->tail = tmp;
	}
	queue->size += 1;
	return (SUCCESS);
}

void			tp_queue_del(t_tp_queue **queue)
{
	if (*queue == NULL)
		return ;
	ft_lstdel(&((*queue)->head), &ft_lstdel_raw);
	free(*queue);
	*queue = NULL;
}
