/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbulant <jbulant@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 17:07:37 by jbulant           #+#    #+#             */
/*   Updated: 2018/12/16 22:09:32 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "libft.h"
#include "parser.h"

static int		get_is_solid(t_parser *parser)
{
	int is_solid;

	if (skipword(parser, "True") != ERROR)
		is_solid = 1;
	else if (skipword(parser, "False") != ERROR)
		is_solid = 0;
	else
		is_solid = -1;
	return (is_solid);
}

static int		set_parse_error(t_parser *parser, int err_no)
{
	parser->err_no = err_no;
	return (Parse_error);

}

static void		print_bits(unsigned char c)
{
	size_t		i;

	i = 0;
	while (i < 8)
	{
		if (c & (1 << (7 - i)))
			ft_putchar('1');
		else
			ft_putchar('0');
		i++;
	}
}

static void		print_memory(void *p, size_t s)
{
	size_t			i;
	unsigned char	*pd;

	pd = (unsigned char *)p;
	i = 0;
	while (i < s)
	{
		print_bits(pd[(s - 1) - i]);
		i++;
		ft_putchar(' ');
		if (!(i % 8))
			ft_putchar('\n');
	}
}

static int		load_objects(t_env *env, t_parser *parser)
{
	int			i;
	t_object	*obj;
	int			sp_i;

	// unsigned short	mask;
	// short	mask;
	// mask = 1 << 14;
	// print_memory(env, sizeof(*env));
	// while (mask)
	// while (mask < -1 || mask > 0)
	// {
	// 	print_memory(&mask, sizeof(mask));
	// 	ft_putchar('\n');
	// 	mask >>= 1;
	// }
	// int ret = 0;
	// for (unsigned int i = 0; i < sizeof(ret); i++)
	// {
	// 	ret |= ((c & 0xff) << (8 * i));
	// }
	i = 0;
	while (i < env->objects_nb)
	{
		obj = env->objects + i;
		ft_bzero(obj, sizeof(*obj));
		if ((obj->solid = get_is_solid(parser)) == -1
		|| skipchar(parser, ':') == ERROR
		|| get_and_skipdigit(parser, &sp_i) == ERROR
		|| sp_i < 0 || sp_i >= env->sprites_nb
		|| skipchar(parser, ':') == ERROR
		|| get_and_skipvec2(parser, &obj->pos) == ERROR)
			return (set_parse_error(parser, EOGET));
//		printf("Object[%d]:\n  is_solid      == %s\n  sprite index  == %d\n  position      == {%f , %f}\n",
//			i, (obj->solid == 1 ? "True" : "False"), sp_i, obj->pos.x, obj->pos.y);
		obj->sprite = env->sprites + sp_i;
		obj->z = 0.0;
		i++;
	}
	return (SUCCESS);
}

int				object_content_analyze(t_env *env, t_parser *parser)
{
	env->objects =
		(t_object *)ft_memalloc((size_t)env->objects_nb * sizeof(t_object));
	if (env->objects == NULL)
		return (set_parse_error(parser, EOGET));
	if (load_objects(env, parser) == ERROR
	|| get_next_clbracket(parser) == ERROR)
		return (Parse_error);
	ft_putstr("Objects: loaded\n");
	return (Name_entity);
}
