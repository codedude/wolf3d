/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 17:25:00 by vparis            #+#    #+#             */
/*   Updated: 2017/12/24 19:27:41 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_list.h"

void	ft_lstadd(t_list **alst, t_list *new)
{
	if (new != NULL)
		new->next = *alst;
	*alst = new;
}
