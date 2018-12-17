/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:15:01 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 17:15:01 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parser.h"

int			is_valid_filename(char *filename)
{
	char		*point;

	if (!(point = ft_strrchr(filename, '.')) || !ft_strequ(point, ".w3d"))
	{
		ft_putstr_fd("Wolf3d: ", 2);
		ft_putstr_fd(filename, 2);
		ft_putstr_fd(": map file must be ended by .w3d extension\n", 2);
		return (ERROR);
	}
	return (SUCCESS);
}

int			get_next_opbracket(t_parser *parser)
{
	if (skipchar(parser, '{') == ERROR)
	{
		parser->err_no = ENOBR;
		return (ERROR);
	}
	return (SUCCESS);
}

int			get_next_clbracket(t_parser *parser)
{
	if (skipchar(parser, '}') == ERROR)
	{
		parser->err_no = ENCBR;
		return (ERROR);
	}
	return (SUCCESS);
}

void		destroy_textures(t_env *env)
{
	int			i;

	if (!env->textures)
		return ;
	i = 0;
	while (i < env->textures_nb)
	{
		free(env->textures[i].data);
		free(env->textures[i].name);
		i++;
	}
	free(env->textures);
}
