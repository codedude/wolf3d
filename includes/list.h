/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:11:31 by vparis            #+#    #+#             */
/*   Updated: 2019/01/11 23:11:11 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "entity.h"

typedef struct s_klist	t_klist;

struct					s_klist {
	t_entity			*value;
	t_klist				*next;
};

t_klist					*klist_new(t_entity *value);
void					klist_append(t_klist **head, t_klist *entry);
void					klist_clear(t_klist **head);
void					klist_del(t_klist **head, t_klist *entry);
void					klist_add_sort(t_klist **head, t_klist *entry,
							int (*compare)(t_entity *a, t_entity *b));

#endif
