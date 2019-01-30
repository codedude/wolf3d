/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 12:51:02 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:51:51 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "entity.h"

void		klist_add_sort(t_klist **head, t_klist *entry,
					int (*compare)(t_entity *a, t_entity *b))
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

void		klist_append(t_klist **head, t_klist *entry)
{
	while (*head != NULL)
		head = &(*head)->next;
	*head = entry;
}

t_klist		*klist_find(t_klist **head, int id)
{
	while (*head && (*head)->value->id != id)
		head = &(*head)->next;
	return (*head);
}
