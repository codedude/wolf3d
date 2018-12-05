/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:04:53 by vparis            #+#    #+#             */
/*   Updated: 2018/12/05 22:15:31 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 23:44:28 by valentin          #+#    #+#             */
/*   Updated: 2018/10/24 23:47:07 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"

t_klist			*list_new(KLIST_TYPE value)
{
	t_klist	*tmp;

	tmp = (t_klist *)malloc(sizeof(t_klist));
	if (tmp == NULL)
		return (NULL);
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

void			list_append(t_klist **head, t_klist *entry)
{
	while (*head != NULL)
		head = &(*head)->next;
	*head = entry;
}

void			list_prepend(t_klist **head, t_klist *entry)
{
	if (*head != NULL)
		entry->next = (*head)->next;
	*head = entry;
}

void			list_del(t_klist **head, t_klist *entry)
{
	while (*head != entry)
		head = &(*head)->next;
	*head = entry->next;
}

void			list_clear(t_klist **head)
{
	while (*head)
		list_del(head, *head);
}

void			list_add_sort(t_klist **head, t_klist *entry,
					int (*compare)(KLIST_TYPE a, KLIST_TYPE b))
{
	t_klist	*last;

	if (*head == NULL)
	{
		*head = entry; //append empty list
		return ;
	}
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
