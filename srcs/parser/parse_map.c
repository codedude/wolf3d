/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:02:08 by jbulant           #+#    #+#             */
/*   Updated: 2019/02/05 15:32:20 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "entity.h"
#include "env.h"

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

static void		init_parser(t_parser *parser, t_sdl *sdl, int conf_fd)
{
	parser->p_state = Name_entity;
	parser->a_state = Parse_action_default;
	parser->conf_fd = conf_fd;
	parser->err_no = 0;
	parser->line_nb = 0;
	parser->line = NULL;
	parser->base_line = NULL;
	parser->sdl = sdl;
	if (parser_gnl(parser) != 1)
		parser->p_state = Parse_error;
}

static void		destroy_objects(t_parser *parser)
{
	int			i;
	t_entity	*ent;

	i = 0;
	while (i < parser->obj.objects_nb)
	{
		ent = &parser->obj.objects[i];
		free(ent->e.object);
		i++;
	}
	free(parser->obj.objects);
}

int				parse_map(t_sdl *sdl, t_parser *parser, int conf_fd)
{
	static int	(*action_state[])(t_parser *) = {
		P_CONTENT_FUNCT
	};

	ft_bzero(parser, sizeof(*parser));
	init_parser(parser, sdl, conf_fd);
	while (parser->p_state != Parse_error && parser->p_state != Parse_end)
		parser->p_state = action_state[parser->p_state](parser);
	if (parser->p_state == Parse_error
		|| clean_info(parser) == Parse_error)
	{
		destroy_map_data(&parser->map.data,
			parser->map.width, parser->map.height);
		destroy_objects(parser);
		print_parser_errno(parser, "Wolf3d: ");
		free(parser->base_line);
		return (ERROR);
	}
	return (SUCCESS);
}

void			map_destroy(t_map *map)
{
	if (map->skybox)
		entity_destroy(map->skybox, False);
	destroy_map_data(&map->data, map->width, map->height);
}
