/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 18:04:31 by vparis            #+#    #+#             */
/*   Updated: 2018/12/04 15:56:08 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"

char	*ft_stackpop(t_stack **stack)
{
	char		*str;
	t_stack		*tmp;

	tmp = *stack;
	if (tmp != NULL)
	{
		str = tmp->str;
		*stack = tmp->previous;
		ft_memdel((void *)&tmp);
	}
	else
		str = NULL;
	return (str);
}

int		ft_stackpush(t_stack **stack, char *str)
{
	t_stack	*tmp;

	tmp = (t_stack *)ft_memalloc_fast(sizeof(t_stack));
	if (tmp == NULL)
		return (ERROR);
	tmp->previous = *stack;
	tmp->str = str;
	*stack = tmp;
	return (SUCCESS);
}

void	ft_stackclear(t_stack **stack)
{
	t_stack	*tmp;

	while (*stack != NULL)
	{
		tmp = (*stack)->previous;
		ft_memdel((void **)stack);
		*stack = tmp;
	}
}
