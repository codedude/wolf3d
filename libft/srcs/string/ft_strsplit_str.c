/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/06 20:48:43 by vparis            #+#    #+#             */
/*   Updated: 2017/11/08 20:51:35 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Start at i = current word, and return i = next word
*/

static int		get_next_word(char const *str, int i, char const *charset)
{
	if (i != -1)
	{
		while (str[i] != 0 && !ft_ischarset(str[i], charset))
			i++;
	}
	else
		i = 0;
	while (ft_ischarset(str[i], charset))
		i++;
	return (str[i] == 0 ? -1 : i);
}

/*
** Count the number of words in str => malloc
*/

static size_t	count_strs(char const *str, char const *charset)
{
	size_t	n;
	int		i;

	n = 0;
	i = -1;
	while ((i = get_next_word(str, i, charset)) != -1)
		n++;
	return (n);
}

static int		split(char **p, char const *str, int i, char const *charset)
{
	size_t	n;
	size_t	j;

	j = (size_t)i;
	n = 0;
	while (str[i] != 0 && !ft_ischarset(str[i], charset))
	{
		i++;
		n++;
	}
	if (n == 0)
		return (1);
	*p = ft_strsub(str, (unsigned int)j, n);
	if (*p == 0)
		return (0);
	return (1);
}

char			**ft_strsplit_str(char const *s, char const *charset)
{
	char	**tmp;
	size_t	n_str;
	size_t	n;
	int		i;

	if (s == NULL)
		return (NULL);
	n_str = count_strs(s, charset);
	tmp = (char **)malloc(sizeof(char *) * (n_str + 1));
	if (tmp == NULL)
		return (NULL);
	tmp[n_str] = 0;
	n = 0;
	i = -1;
	while ((i = get_next_word(s, i, charset)) != -1)
		if (split(&tmp[n++], s, i, charset) == 0)
			return (NULL);
	return (tmp);
}
