/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:04:53 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:51:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "list.h"
#include "entity.h"

t_klist		*klist_new(t_entity *value)
{
	t_klist	*tmp;

	tmp = (t_klist *)malloc(sizeof(t_klist));
	if (tmp == NULL)
		return (NULL);
	tmp->value = value;
	tmp->next = NULL;
	return (tmp);
}

void		klist_del(t_klist **head, t_klist *entry)
{
	while (*head != entry)
		head = &(*head)->next;
	*head = entry->next;
	free(entry);
}

void		klist_clear(t_klist **head)
{
	while (*head)
		klist_del(head, *head);
}
