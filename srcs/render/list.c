/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:04:53 by vparis            #+#    #+#             */
/*   Updated: 2019/01/10 16:32:34 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_klist			*klist_new(KLIST_TYPE value)
{
	t_klist	*tmp;

	tmp = (t_klist *)malloc(sizeof(t_klist));
	if (tmp == NULL)
		return (NULL);
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

void			klist_del(t_klist **head, t_klist *entry)
{
	while (*head != entry)
		head = &(*head)->next;
	*head = entry->next;
	free(entry);
}

void			klist_clear(t_klist **head)
{
	while (*head)
		klist_del(head, *head);
}

void			klist_add_sort(t_klist **head, t_klist *entry,
					int (*compare)(KLIST_TYPE a, KLIST_TYPE b))
{
	t_klist	*last;

	last = NULL;
	while (*head != NULL)
	{
		if (compare((*head)->value, entry->value) < 0)
		{
			entry->next = *head;
			break ;
		}
		last = *head;
		head = &(*head)->next;
	}
	if (last != NULL)
		last->next = entry;
	*head = entry;
}

void			klist_append(t_klist **head, t_klist *entry)
{
	while (*head != NULL)
		head = &(*head)->next;
	*head = entry;
}
