/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ent_analyze.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 16:55:19 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 18:03:06 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parser.h"

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

int				map_ent_analyze(t_env *env, t_parser *parser)
{
	if (map_ent_paramaters(env, parser) == ERROR
	|| get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_map;
	return (Map_parsing);
}

static int		sprite_ent_paramaters(t_env *env, t_parser *parser)
{
	if (parser->a_state & Parse_action_sprite)
	{
		parser->err_no = ESPRDEF;
		return (ERROR);
	}
	if (get_and_skipdigit(parser, &env->sprites_nb) == ERROR)
	{
		parser->err_no = ESPRPAR;
		return (ERROR);
	}
	return (SUCCESS);
}

int				sprite_ent_analyze(t_env *env, t_parser *parser)
{
	if (sprite_ent_paramaters(env, parser) == ERROR
	|| get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_sprite;
	return (Sprite_parsing);
}

static int		object_ent_paramaters(t_env *env, t_parser *parser)
{
	if (parser->a_state & Parse_action_object)
	{
		parser->err_no = EODEF;
		return (ERROR);
	}
	if (get_and_skipdigit(parser, &env->objects_nb) == ERROR)
	{
		parser->err_no = EOPAR;
		return (ERROR);
	}
	return (SUCCESS);
}

int				object_ent_analyze(t_env *env, t_parser *parser)
{
	if (object_ent_paramaters(env, parser) == ERROR
	|| get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_object;
	return (Object_parsing);
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

int				texture_ent_analyze(t_env *env, t_parser *parser)
{
	if (tex_ent_paramaters(env, parser) == ERROR
		|| get_next_opbracket(parser) == ERROR)
		return (Parse_error);
	parser->a_state |= Parse_action_texture;
	return (Texture_parsing);
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

int				name_ent_analyze(t_env *env, t_parser *parser)
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

int				spawn_ent_analyze(t_env *env, t_parser *parser)
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
