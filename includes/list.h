/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:11:31 by vparis            #+#    #+#             */
/*   Updated: 2019/01/10 00:08:38 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include "env.h"

# define KLIST_TYPE		t_entity*
# define INIT_KLIST(l)	{(l), (l)}

typedef struct s_klist	t_klist;

struct					s_klist {
	KLIST_TYPE			value;
	t_klist				*next;
};

t_klist					*list_new(KLIST_TYPE value);
void					list_append(t_klist **head, t_klist *entry);
void					list_clear(t_klist **head);
void					list_del(t_klist **head, t_klist *entry);
void					list_add_sort(t_klist **head, t_klist *entry,
							int (*compare)(KLIST_TYPE a, KLIST_TYPE b));

#endif
