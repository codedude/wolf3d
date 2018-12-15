/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/10 22:53:54 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/15 21:20:06 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_input.h"
#include "env.h"
#include "parser.h"

static int		ft_iswhitespace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

static int		isopbracket(int c)
{
	return (c == '{');
}

static int		isclbracket(int c)
{
	return (c == '{');
}

static char		*skip_whitespace(char *str)
{
	while (ft_iswhitespace(*str))
		str++;
	return (str);
}

static char		*skip_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (str);
}

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

static int		parser_gnl(t_parser *parser)
{
	int		gnl_ret;

	free(parser->base_line);
	parser->line = NULL;
	gnl_ret = get_next_line(parser->conf_fd, &parser->base_line);
	if (gnl_ret == 1)
	{
		parser->line_nb++;
		parser->line = parser->base_line;
		if (!*parser->line)
			return (parser_gnl(parser));
	}
	else
		parser->base_line = NULL;
	return (gnl_ret);
}

static char		*get_next_word(t_parser *parser, int (*cmp)(int))
{
	while (!cmp(*parser->line))
	{
		if (ft_iswhitespace(*parser->line))
			parser->line = skip_whitespace(parser->line);
		else if (!*parser->line)
		{
			if (parser_gnl(parser) != 1)
				return (0);
		}
		else
			return (NULL);
	}
	return (parser->line);
}

static size_t	get_next_word_len(t_parser *parser, int (*cmp)(int))
{
	char		*line;
	size_t		len;

	len = 0;
	if ((line = get_next_word(parser, cmp)) == NULL)
		return (0);
	while (line[len] && cmp(line[len]))
		len++;
	parser->line = line;
	return (len);
}

static int		get_next_opbracket(t_parser *parser)
{
	char	*line;

	if (!((line = get_next_word(parser, isopbracket))))
	{
		parser->err_no = ENOBR;
		return (ERROR);
	}
	parser->line = line + 1;
	return (SUCCESS);
}

static int		is_sdigit(int c)
{
	return (c == '+' || c == '-' || ft_isdigit(c));
}

static int		get_and_skipdigit(t_parser *parser, int *get)
{
	char	*line;

	if (!(line = get_next_word(parser, is_sdigit))
	|| (*get = ft_atoi(line)) < 0)
		return (ERROR);
	parser->line = skip_digit(line);
	return (SUCCESS);
}

static int		get_and_skipsdigit(t_parser *parser, int *get)
{
	char	*line;

	if (!(line = get_next_word(parser, ft_isdigit))
	|| ((*line == '+' || *line == '-') && ft_isdigit(line[1]))
	|| (*get = ft_atoi(line)) < 0)
		return (ERROR);
	parser->line = skip_digit(line);
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

void			del_int_2d_array(int **ar, int h)
{
	int		i;

	if (!ar)
		return ;
	i = 0;
	while (i < h)
	{
		free(ar[i]);
		i++;
	}
	free(ar);
}

static int		**int_new_2darray(int x, int y)
{
	int		**ar;
	int		i;

	if (!(ar = (int**)ft_memalloc(sizeof(int *) * (unsigned int) y)))
		return (NULL);
	i = 0;
	while (i < y)
	{
		if (!(ar[i] = (int *)malloc(sizeof(int) * (unsigned int) x)))
		{
			del_int_2d_array(ar, y);
			return (NULL);
		}
		i++;
	}
	return (ar);
}

static int		skipchar(t_parser *parser, char c)
{
	while (*parser->line != c)
	{
		if (ft_iswhitespace(*parser->line))
			parser->line = skip_whitespace(parser->line);
		else if (!*parser->line)
		{
			if (parser_gnl(parser) != 1)
				return (ERROR);
		}
		else
			return (ERROR);
	}
	parser->line++;
	return (SUCCESS);
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
			{
				parser->err_no = EMGET;
				return (Parse_error);
			}
			map->data[i.y][i.x] = val;
			i.x++;
		}
		i.y++;
		if (skipchar(parser, (i.y !=  map->height ? ',' : '}')) == ERROR)
		{
			parser->err_no = EMGET;
			return (Parse_error);
		}
	}
	return (Name_entity);
}

static int		map_content_analyze(t_env *env, t_parser *parser)
{
	t_map		*map;
	int			ret;

	map = &env->map;
	if (!(map->data = int_new_2darray(map->width, map->height)))
	{
		parser->err_no = EMGET;
		ret = Parse_error;
	}
	else if ((ret = get_map_content(map, parser)) != Parse_error)
		ft_putstr("Map: loaded\n");
	return (ret);
}

static int		is_filechar(int c)
{
	return (c == '/' || c == '_' || ft_isalnum(c) || c == '.');
}

static int		fill_buffer(char *buff, t_parser *parser)
{
	size_t		wlen;

	if ((wlen = get_next_word_len(parser, is_filechar)) == 0
		|| wlen >= PATH_MAX)
		return (ERROR);
	ft_strncpy(buff, parser->line, wlen);
	buff[wlen] = '\0';
	parser->line += wlen;
	return (SUCCESS);
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
		i++;
	}
	free(env->textures);
}

static int		load_textures(t_env *env, t_parser *parser)
{
	char		buff[PATH_MAX + 1];
	int			i;

	i = 0;
	while (i < env->textures_nb)
	{
		if ((fill_buffer(buff, parser)) == ERROR
		|| sdl_load_texture(env->textures + i, buff) == ERROR)
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

static int		texture_content_analyze(t_env *env, t_parser *parser)
{
	env->textures =
		(t_texture *)ft_memalloc((size_t)env->textures_nb * sizeof(t_texture));
	if (env->textures == NULL
		|| load_textures(env, parser) == ERROR
		|| skipchar(parser, '}') == ERROR)
	{
		parser->err_no = ETGET;
		return (Parse_error);
	}
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

static int		spawn_content_getarg(t_parser *parser, char *word,
									t_ivec2 *fill)
{
	int		x;
	int		y;
	size_t	wlen;

	if ((wlen = get_next_word_len(parser, ft_isalpha)) == 0)
		return (Parse_error);
	if (!ft_strnequ(word, parser->line, wlen))
		return (Parse_error);
	parser->line += wlen;
	if (get_and_skipsdigit(parser, &x) == ERROR
	|| get_and_skipsdigit(parser, &y) == ERROR)
		return (Parse_error);
	*fill = IVEC2_INIT(x, y);
	return (SUCCESS);
}

static int		spawn_content_analyze(t_env *env, t_parser *parser)
{
	if (spawn_content_getarg(parser, "pos", &env->map.spawn) == ERROR
	|| spawn_content_getarg(parser, "dir", &env->map.spawn_dir) == ERROR)
	{
		parser->err_no = ESGET;
		return (Parse_error);
	}
	if (skipchar(parser, '}') == ERROR)
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
