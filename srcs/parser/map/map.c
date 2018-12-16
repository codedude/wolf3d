/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 22:53:54 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 02:36:32 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "env.h"
#include "parser.h"

static int		is_valid_filename(char *filename)
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

static int		get_next_opbracket(t_parser *parser)
{
	if (skipchar(parser, '{') == ERROR)
	{
		parser->err_no = ENOBR;
		return (ERROR);
	}
	return (SUCCESS);
}

static int		get_next_clbracket(t_parser *parser)
{
	if (skipchar(parser, '}') == ERROR)
	{
		parser->err_no = ENCBR;
		return (ERROR);
	}
	return (SUCCESS);
}

static int		map_ent_paramaters(t_env *env, t_parser *parser)
{
	if (parser->a_state & Parse_action_map)
	{
		parser->err_no = ETDEF;
		return (ERROR);
	}
	if (get_and_skipdigit(parser, &env->map.width) == ERROR
	|| get_and_skipdigit(parser, &env->map.height) == ERROR)
	{
		parser->err_no = EMPAR;
		return (ERROR);
	}
	return (SUCCESS);
}

static int		map_ent_analyze(t_env *env, t_parser *parser)
{
	if (map_ent_paramaters(env, parser) == ERROR
	|| get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_map;
	return (Map_parsing);
}

static int		get_map_content(t_map *map, t_parser *parser)
{
	t_ivec2		i;
	int			val;

	i.y = 0;
	while (i.y < map->height)
	{
		i.x = 0;
		while (i.x < map->width)
		{
			if (get_and_skipdigit(parser, &val) == ERROR)
				return (ERROR);
			map->data[i.y][i.x] = val;
			i.x++;
		}
		i.y++;
		if (i.y != map->height && skipchar(parser, ',') == ERROR)
			return (ERROR);
	}
	return (SUCCESS);
}

static int		map_content_analyze(t_env *env, t_parser *parser)
{
	t_map		*map;

	map = &env->map;
	if (!(map->data = int_new_2darray(map->width, map->height))
	|| get_map_content(map, parser) == ERROR)
	{
		parser->err_no = EMGET;
		return (Parse_error);
	}
	if (get_next_clbracket(parser))
		return (Parse_error);
	ft_putstr("Map: loaded\n");
	return (Name_entity);
}

static void		destroy_textures(t_env *env)
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

static int		texture_content_analyze(t_env *env, t_parser *parser)
{
	env->textures =
		(t_texture *)ft_memalloc((size_t)env->textures_nb * sizeof(t_texture));
	if (env->textures == NULL || load_textures(env, parser) == ERROR)
	{
		parser->err_no = ETGET;
		return (Parse_error);
	}
	if (get_next_clbracket(parser))
		return (Parse_error);
	ft_putstr("Textures: loaded\n");
	return (Name_entity);
}

static int		tex_ent_paramaters(t_env *env, t_parser *parser)
{
	if (parser->a_state & Parse_action_texture)
	{
		parser->err_no = ETDEF;
		return (ERROR);
	}
	if (get_and_skipdigit(parser, &env->textures_nb) == ERROR)
	{
		parser->err_no = ETPAR;
		return (ERROR);
	}
	return (SUCCESS);
}

static int		texture_ent_analyze(t_env *env, t_parser *parser)
{
	if (tex_ent_paramaters(env, parser) == ERROR
		|| get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_texture;
	return (Texture_parsing);
}

static int		spawn_get_pos(t_parser *parser, t_env *env)
{
	int		x;
	int		y;

	if (get_and_skipsdigit(parser, &x) == ERROR
	|| get_and_skipsdigit(parser, &y) == ERROR)
		return (Parse_error);
	env->map.spawn = IVEC2_INIT(x, y);
	return (SUCCESS);
}

static int		spawn_get_rotation(t_parser *parser, t_env *env)
{
	int		r;

	if (get_and_skipsdigit(parser, &r) == ERROR)
		return (Parse_error);
	env->map.spawn_rotation = (t_float)r;
	return (SUCCESS);
}

static int		spawn_content_getarg(t_env *env, t_parser *parser, char *word,
									int (*get)(t_parser *, t_env *))
{
	size_t	wlen;

	if ((wlen = get_next_word_len(parser, ft_isalpha)) == 0)
		return (Parse_error);
	if (!ft_strnequ(word, parser->line, wlen))
		return (Parse_error);
	parser->line += wlen;
	return (get(parser, env));
}

static int		spawn_content_analyze(t_env *env, t_parser *parser)
{
	if (spawn_content_getarg(env, parser, "pos", spawn_get_pos) == ERROR
	|| spawn_content_getarg(env, parser, "dir", spawn_get_rotation) == ERROR)
	{
		parser->err_no = ESGET;
		return (Parse_error);
	}
	if (get_next_clbracket(parser))
		return (Parse_error);
	ft_putstr("Spawn: loaded\n");
	return (Name_entity);
}

static int		spawn_ent_analyze(t_env *env, t_parser *parser)
{
	(void)env;
	if (parser->a_state & Parse_action_spawn)
	{
		parser->err_no = ESDEF;
		return (Parse_error);
	}
	if (get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_spawn;
	return (Spawn_parsing);
}

static int		get_obj_type_name(t_parser *parser, size_t wlen)
{
	static char		*name[P_ENT_COUNT] = {
		P_ENT_TOSTRING
	};
	int			i;

	i = 0;
	while (i < P_ENT_COUNT)
	{
		if (wlen == ft_strlen(name[i])
		&& ft_strnequ(name[i], parser->line, wlen))
		{
			parser->line += wlen;
			return (i);
		}
		i++;
	}
	return (-1);
}

static int		name_ent_analyze(t_env *env, t_parser *parser)
{
	static int		(*ent_funct[P_ENT_COUNT])(t_env *, t_parser *) = {
		P_ENT_FUNCT
	};
	size_t			wlen;
	int				i;

	if ((wlen = get_next_word_len(parser, ft_isalpha)) == 0
	|| (i = get_obj_type_name(parser, wlen)) == -1)
		return (Parse_end);
	return (ent_funct[i](env, parser));
}

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
		|| !(parser->a_state & Parse_action_spawn))
	{
		parser->err_no = EBTYPE;
		return (Parse_error);
	}
	if (check_spawn(&env->map, parser) == ERROR)
		return (Parse_error);
	return (SUCCESS);
}

static int		parse_map(t_env *env, int conf_fd)
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

int				load_map(t_env *env, t_map *map, char *mapfile)
{
	int		conf_fd;
	int		ret_value;

	if (is_valid_filename(mapfile) == ERROR)
		return (ERROR);
	ft_bzero(map, sizeof(*map));
	errno = 0;
	if ((conf_fd = open(mapfile, O_RDONLY | O_NOFOLLOW)) == -1)
	{
		perror("Wolf3d: ");
		return (ERROR);
	}
	ret_value = parse_map(env, conf_fd);
	close(conf_fd);
	return (ret_value);
}
