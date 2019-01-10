/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:11:31 by vparis            #+#    #+#             */
/*   Updated: 2019/01/10 16:31:25 by vparis           ###   ########.fr       */
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

t_klist					*klist_new(KLIST_TYPE value);
void					klist_append(t_klist **head, t_klist *entry);
void					klist_clear(t_klist **head);
void					klist_del(t_klist **head, t_klist *entry);
void					klist_add_sort(t_klist **head, t_klist *entry,
							int (*compare)(KLIST_TYPE a, KLIST_TYPE b));

#endif
