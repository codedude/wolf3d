/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/11 23:43:56 by vparis            #+#    #+#             */
/*   Updated: 2019/01/11 23:45:32 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "anim.h"

t_list_anim		*alist_new(t_anim *value)
{
	t_list_anim	*tmp;

	tmp = (t_list_anim *)malloc(sizeof(t_list_anim));
	if (tmp == NULL)
		return (NULL);
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

int				alist_push(t_list_anim **head, t_anim *entry)
{
	t_list_anim	*tmp;

	if ((tmp = alist_new(entry)) == NULL)
		return (ERROR);
	tmp->next = *head;
	*head = tmp;
	return (SUCCESS);
}

void			alist_del_elem(t_list_anim **head)
{
	t_list_anim *next;

	next = (*head)->next;
	anim_destroy((*head)->value);
	free(*head);
	*head = next;
}

void			alist_del(t_list_anim **head, t_list_anim *entry)
{
	while (*head != entry)
		head = &(*head)->next;
	*head = entry->next;
	anim_destroy(entry->value);
	free(entry);
}

void			alist_clear(t_list_anim **head)
{
	while (*head)
		alist_del(head, *head);
}
