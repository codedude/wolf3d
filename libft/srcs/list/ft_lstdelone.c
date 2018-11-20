/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valentin <valentin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/08 17:25:12 by vparis            #+#    #+#             */
/*   Updated: 2017/12/24 19:27:52 by valentin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "ft_list.h"

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (del != NULL)
		(*del)((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
