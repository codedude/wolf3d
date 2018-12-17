/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:02:08 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 17:13:31 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parser.h"

static void		init_parser(t_parser *parser, int conf_fd)
{
	parser->p_state = Name_entity;
	parser->a_state = Parse_action_default;
	parser->conf_fd = conf_fd;
	parser->err_no = 0;
	parser->line_nb = 0;
	parser->line = NULL;
	parser->base_line = NULL;
	if (parser_gnl(parser) != 1)
		parser->p_state = Parse_error;
}

static void		print_parser_errno(t_parser *parser, char *header)
{
	static char	*err_msg[ERRMSG_CNT] = { ERRMSG_STR };

	if (header)
		ft_putstr_fd(header, 2);
	if (parser->line_nb > 0)
	{
		ft_putstr_fd("line ", 2);
		ft_putnbr_fd(parser->line_nb, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(err_msg[parser->err_no], 2);
}

static int		check_spawn(t_map *map, t_parser *parser)
{
	int		check;

	if (map->spawn.x < 0 || map->spawn.x >= map->width
	|| map->spawn.y < 0 || map->spawn.y >= map->height)
		check = 1;
	else if (map->data[map->spawn.y][map->spawn.x] != 0)
		check = 2;
	else
		return (SUCCESS);
	parser->line_nb = 0;
	parser->err_no = check == 1 ? ESOOR : ESONW;
	return (ERROR);
}

static int		clean_info(t_env *env, t_parser *parser)
{
	if (!(parser->a_state & Parse_action_map)
		|| !(parser->a_state & Parse_action_texture)
		|| !(parser->a_state & Parse_action_spawn)
		|| !(parser->a_state & Parse_action_sprite))
	{
		parser->err_no = EBTYPE;
		return (Parse_error);
	}
	if (check_spawn(&env->map, parser) == ERROR)
		return (Parse_error);
	return (SUCCESS);
}

int				parse_map(t_env *env, int conf_fd)
{
	static int	(*action_state[])(t_env *, t_parser *) = {
		P_CONTENT_FUNCT
	};
	t_parser	parser;

	ft_bzero(&parser, sizeof(parser));
	init_parser(&parser, conf_fd);
	while (parser.p_state != Parse_error && parser.p_state != Parse_end)
		parser.p_state = action_state[parser.p_state](env, &parser);
	if (parser.p_state == Parse_error
		|| clean_info(env, &parser) == Parse_error)
	{
		destroy_textures(env);
		map_destroy(&env->map);
		print_parser_errno(&parser, "Wolf3d: ");
		free(parser.base_line);
		return (ERROR);
	}
	return (SUCCESS);
}
