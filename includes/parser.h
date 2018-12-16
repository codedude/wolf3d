/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:48:58 by vparis            #+#    #+#             */
/*   Updated: 2018/12/15 22:43:06 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "env.h"

enum parsing_states {
	Parse_error = -1,
	Name_entity = 0,
	Map_parsing = 1,
	Texture_parsing = 2,
	Spawn_parsing = 3,
	Parse_end
};

enum parsing_actions {
	Parse_action_default = 0,
	Parse_action_map = (1 << 0),
	Parse_action_texture = (1 << 1),
	Parse_action_spawn = (1 << 2)
};

# define TYPE_LIST_HELP	"types supported:\n" TYPE_NAMES_LIST
# define TYPE_NAMES_LIST	P_ENT_NAME_0_0 "\n" P_ENT_NAME_1_0

# define ENOBR		0
# define ENOBR_STR	"error encountered while looking for '{'"
# define EBTYPE		1
# define EBTYPE_STR	"error while looking for object type:\n" TYPE_LIST_HELP
# define EUNKST		2
# define EUNKST_STR	"internal problem: unknown state"
# define EMPAR		3
# define EMPAR_STR	"error: map parameters"
# define EMGET		4
# define EMGET_STR	"error: map content"
# define ETPAR		5
# define ETPAR_STR	"error: textures parameters"
# define ETGET		6
# define ETGET_STR	"error: textures content"
# define EMDEF		7
# define EMDEF_STR	"error: map already definded"
# define ETDEF		8
# define ETDEF_STR	"error: textures already definded"
# define ESPAR		9
# define ESPAR_STR	"error: spawn parameters"
# define ESGET		10
# define ESGET_STR	"error: spawn content"
# define ESDEF		11
# define ESDEF_STR	"error: spawn already definded"
# define ESOOR		12
# define ESOOR_STR	"error: spawn position out of range"
# define ESONW		13
# define ESONW_STR	"error: spawn position inside wall"
# define ENCBR		14
# define ENCBR_STR	"error encountered while looking for '}'"

# define ERRMSG_CNT	15
# define ERRMSG_STR1	ENOBR_STR, EBTYPE_STR, EUNKST_STR, EMPAR_STR, EMGET_STR
# define ERRMSG_STR2	ETPAR_STR, ETGET_STR, EMDEF_STR, ETDEF_STR, ESPAR_STR
# define ERRMSG_STR3	ESGET_STR, ESDEF_STR, ESOOR_STR, ESONW_STR
# define ERRMSG_STR		ERRMSG_STR1, ERRMSG_STR2, ERRMSG_STR3

typedef struct		s_stack {
	struct s_stack	*previous;
	char			*str;
}					t_stack;

typedef struct		s_parser {
	int				p_state;
	int				a_state;
	char			*line;
	char			*base_line;
	int				conf_fd;
	int				err_no;
	int				line_nb;
}					t_parser;

/*
**	P_ENT		aka Parser_Entity
**	fields:
**		0	=	toString value
**		1	=	header analyze : associated function pointer
**		2	=	content analyze : associated function pointer
*/

# define P_ENT_NAME_0_0		"Map"
# define P_ENT_NAME_0_1		map_ent_analyze
# define P_ENT_NAME_0_2		map_content_analyze

# define P_ENT_NAME_1_0		"Texture"
# define P_ENT_NAME_1_1		texture_ent_analyze
# define P_ENT_NAME_1_2		texture_content_analyze

# define P_ENT_NAME_2_0		"Spawn"
# define P_ENT_NAME_2_1		spawn_ent_analyze
# define P_ENT_NAME_2_2		spawn_content_analyze

# define P_ENT_TOSTRING		P_ENT_NAME_0_0, P_ENT_NAME_1_0, P_ENT_NAME_2_0
# define P_ENT_FUNCT		P_ENT_NAME_0_1, P_ENT_NAME_1_1, P_ENT_NAME_2_1
# define P_CONTENT_FUNCT	name_ent_analyze, P_ENT_NAME_0_2, P_ENT_NAME_1_2, P_ENT_NAME_2_2
# define P_ENT_COUNT		3

char				*ft_stackpop(t_stack **stack);
int					ft_stackpush(t_stack **stack, char *str);
void				ft_stackclear(t_stack **stack);

int					read_file(char *filename, t_stack **stack);
int					load_map(t_env *env, t_map *map, char *mapfile);
void				map_destroy(t_map *map);

int					load_textures(t_env *env, t_parser *parser);

/*
**	tools.c
*/

int					ft_iswhitespace(int c);
char				*skip_whitespace(char *str);
void				del_int_2d_array(int **ar, int h);
int					**int_new_2darray(int x, int y);
int					is_filechar(int c);

/*
**	tools_2.c
*/

int					get_and_skipdigit(t_parser *parser, int *get);
int					get_and_skipsdigit(t_parser *parser, int *get);

/*
**	tools_3.c
*/

int					parser_gnl(t_parser *parser);
char				*get_next_word(t_parser *parser, int (*cmp)(int));
int					skipchar(t_parser *parser, char c);
size_t				get_next_word_len(t_parser *parser, int (*cmp)(int));

#endif
