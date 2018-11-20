/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gnl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 18:33:59 by vparis            #+#    #+#             */
/*   Updated: 2018/01/12 13:51:47 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_input.h"

static t_fd_list	*find_fd(t_fd_list **lst, int fd)
{
	t_fd_list	*iter;

	iter = *lst;
	while (iter != NULL)
	{
		if (fd == iter->fd)
			return (iter);
		iter = iter->next;
	}
	if ((iter = (t_fd_list *)malloc(sizeof(t_fd_list))) == NULL)
		return (NULL);
	iter->fd = fd;
	iter->data = NULL;
	iter->pos = 0;
	iter->previous = NULL;
	if (*lst != NULL)
		(*lst)->previous = iter;
	iter->next = *lst;
	*lst = iter;
	return (*lst);
}

static ssize_t		read_entry(int fd, t_list **lst)
{
	ssize_t		n;
	char		*buff;
	t_list		*tmp;

	if ((buff = ft_strnew_fast(BUFF_GNL)) == NULL)
		return (-1);
	if ((n = read(fd, (void *)buff, BUFF_GNL)) <= 0)
	{
		ft_strdel(&buff);
		return (n);
	}
	buff[n] = 0;
	if ((tmp = ft_lstnew((void *)buff, sizeof(char) * ((size_t)n + 1))) == NULL)
	{
		ft_strdel(&buff);
		return (-1);
	}
	tmp->content_size -= 1;
	ft_lstadd(lst, tmp);
	ft_strdel(&buff);
	return (n);
}

static ssize_t		read_line(t_fd_list *fd)
{
	t_list		**it;
	ssize_t		r;
	char		*tmp;
	ssize_t		n;

	n = 0;
	it = &fd->data;
	while (1)
	{
		while (*it != NULL)
		{
			if ((tmp = ft_memchr((char *)(*it)->content + ((it == &fd->data) \
				? fd->pos : 0), '\n', (*it)->content_size)) == NULL)
				n += (ssize_t)(*it)->content_size;
			else
				return (n + (ssize_t)(tmp - ((char *)(*it)->content \
				+ ((it == &fd->data) ? fd->pos : 0))));
					it = &((*it)->next);
		}
		if ((r = read_entry(fd->fd, it)) < 0)
			return (-1);
		else if (r == 0)
			break ;
	}
	return ((n == 0 && r == 0) ? -2 : n);
}

static void			cut_string(char *buff, t_fd_list *lst, size_t n)
{
	t_list	*iter;
	size_t	ns;

	iter = lst->data;
	ns = n;
	while (iter != NULL)
	{
		if (n > 0 && iter->content_size > 0)
			ft_strncat(buff, (char *)iter->content + lst->pos, n);
		if (n >= iter->content_size)
		{
			n -= iter->content_size;
			ft_lstshift(&(lst->data), &ft_lstdel_raw);
			lst->pos = 0;
			iter = lst->data;
			ns = n;
		}
		else if (n < iter->content_size || n == 0)
			break ;
	}
	if (iter != NULL)
	{
		lst->pos += (ssize_t)ns + 1;
		iter->content_size -= (ns + 1);
	}
}

int					ft_gnl(int const fd, char **line)
{
	static t_fd_list	*lst = NULL;
	t_fd_list			*fd_data;
	ssize_t				n;

	if (BUFF_GNL < 1)
		return (-1);
	if ((fd_data = find_fd(&lst, fd)) == NULL)
		return (-1);
	if ((n = read_line(fd_data)) < 0)
	{
		ft_lstdel(&(fd_data->data), &ft_lstdel_raw);
		if (fd_data->previous != NULL)
			fd_data->previous->next = fd_data->next;
		else
			lst = fd_data->next;
		if (fd_data->next != NULL)
			fd_data->next->previous = fd_data->previous;
		free(fd_data);
		return ((n == -2) ? 0 : -1);
	}
	if ((*line = ft_strnew_fast((size_t)n + 1)) == NULL)
		return (-1);
	(*line)[0] = 0;
	cut_string(*line, fd_data, (size_t)n);
	return (1);
}
