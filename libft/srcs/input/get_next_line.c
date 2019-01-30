/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/09 18:33:59 by vparis            #+#    #+#             */
/*   Updated: 2019/01/30 12:05:04 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"
#include "ft_input.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;

	if (!s1)
	{
		if (s2)
			return (ft_strdup(s2));
		else
			return (NULL);
	}
	else if (!s2)
		return (ft_strdup(s1));
	else if (!(ret = ft_strnew(ft_strlen(s1) + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(ret, s1);
	ft_strcat(ret, s2);
	return (ret);
}

char	*ft_strjoin_proper(char **s1, char *s2)
{
	char	*tmp;
	char	*dummy;

	dummy = *s1;
	tmp = ft_strjoin(dummy, s2);
	if (dummy)
		free(dummy);
	*s1 = tmp;
	return (tmp);
}

char	*ft_strndup(const char *src, size_t n)
{
	char *dup;

	if (!(dup = ft_strnew(n)))
		return (NULL);
	return (ft_strncpy(dup, src, n));
}

int		create_newline(char **save, char **line)
{
	char	*tmp;
	size_t	len;

	if (!*save)
		return (0);
	if (!(tmp = ft_strchr(*save, '\n')))
		len = ft_strlen(*save);
	else
		len = (tmp) - (*save);
	if (!(*line = ft_strndup(*save, len)))
		return (-1);
	if ((*save)[len])
		tmp = (*save)[len] ? ft_strdup((*save) + len + 1) : NULL;
	ft_strdel(save);
	*save = tmp;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char		*save;
	char			buff[BUFF_GNL + 1];
	int				read_ret;

	if (fd < 0)
		return (-1);
	if (!(save && ft_strchr(save, '\n')))
	{
		while ((read_ret = read(fd, buff, BUFF_GNL)) > 0)
		{
			buff[read_ret] = '\0';
			ft_strjoin_proper(&save, buff);
			if (ft_strchr(buff, '\n'))
				break ;
		}
	}
	return (create_newline(&save, line));
}
