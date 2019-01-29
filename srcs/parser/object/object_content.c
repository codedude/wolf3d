/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:07:37 by jbulant           #+#    #+#             */
/*   Updated: 2019/01/29 17:53:57 by vparis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "parser.h"
#include "entity.h"

static int		get_is_solid(t_parser *parser)
{
	int is_solid;

	if (skipword(parser, "True") != ERROR)
		is_solid = 0;
	else if (skipword(parser, "False") != ERROR)
		is_solid = 1;
	else
		is_solid = -1;
	return (is_solid);
}

static int		set_parse_error(t_parser *parser, int err_no)
{
	parser->err_no = err_no;
	return (Parse_error);

}

static int		load_objects(t_parser *parser, t_parser_obj *p_obj)
{
	int			i;
	t_entity	*ent;
	t_object	*obj;
	int			sp_i;

	i = 0;
	while (i < p_obj->objects_nb)
	{
		ent = p_obj->objects + i;
		if ((obj = entity_new_object(VEC2_ZERO, VEC2_ZERO, VEC2_INIT(1.0, 0.0),
				0)) == NULL)
			return (set_parse_error(parser, EOGET));
		entity_merge(ent, (void *)obj, ENTITY_OBJECT);
		if ((ent->crossable = get_is_solid(parser)) == -1
		|| skipchar(parser, ':') == ERROR
		|| get_and_skipdigit(parser, &sp_i) == ERROR
		|| sp_i < 0 || sp_i >= parser->sdl->tex_sprite_nb
		|| skipchar(parser, ':') == ERROR
		|| get_and_skipvec2(parser, &obj->pos) == ERROR
		|| skipchar(parser, ':') == ERROR
		|| get_and_skipfdigit(parser, &obj->z) == ERROR
		|| skipchar(parser, ':') == ERROR
		|| get_and_skipfdigit(parser, &obj->scale) == ERROR)
			return (set_parse_error(parser, EOGET));
		ent->tex_id = sp_i;
		i++;
	}
	return (SUCCESS);
}

int				object_content_analyze(t_parser *parser)
{
	t_parser_obj	*obj;

	obj = &parser->obj;
	if (obj->objects_nb > 0)
	{
		obj->objects =
			(t_entity *)ft_memalloc((size_t)obj->objects_nb * sizeof(t_entity));
		if (obj->objects == NULL)
			return (set_parse_error(parser, EOGET));
		if (load_objects(parser, obj) == ERROR)
			return (Parse_error);
	}
	if (get_next_clbracket(parser) == ERROR)
		return (Parse_error);
	ft_putstr("Objects: loaded\n");
	return (Name_entity);
}
