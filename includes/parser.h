/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:48:58 by vparis            #+#    #+#             */
/*   Updated: 2019/01/15 03:37:04 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "env.h"
# include "entity.h"

enum parsing_states {
	Parse_error = -1,
	Name_entity,
	Map_parsing,
	Spawn_parsing,
	Object_parsing,
	Parse_end
};

enum parsing_actions {
	Parse_action_default = 0,
	Parse_action_map = (1 << 0),
	Parse_action_spawn = (1 << 1),
	Parse_action_object = (1 << 2)
};

# define TYPE_LIST_HELP	"types supported:\n" TYPE_NAMES_LIST
# define TYPE_NAMES_LIST	P_ENT_NAME_0_0 "\n" P_ENT_NAME_1_0

# define ENOBR			0
# define ENOBR_STR		"error encountered while looking for '{'"
# define EBTYPE			1
# define EBTYPE_STR		"error while looking for object type:\n" TYPE_LIST_HELP
# define EUNKST			2
# define EUNKST_STR		"internal problem: unknown state"
# define EMPAR			3
# define EMPAR_STR		"error: map parameters"
# define EMGET			4
# define EMGET_STR		"error: map content"
# define ETPAR			5
# define ETPAR_STR		"error: textures parameters"
# define ETGET			6
# define ETGET_STR		"error: textures content"
# define EMDEF			7
# define EMDEF_STR		"error: map already definded"
# define ETDEF			8
# define ETDEF_STR		"error: textures already definded"
# define ESPAR			9
# define ESPAR_STR		"error: spawn parameters"
# define ESGET			10
# define ESGET_STR		"error: spawn content"
# define ESDEF			11
# define ESDEF_STR		"error: spawn already definded"
# define ESOOR			12
# define ESOOR_STR		"error: spawn position out of range"
# define ESONW			13
# define ESONW_STR		"error: spawn position inside wall"
# define ENCBR			14
# define ENCBR_STR		"error encountered while looking for '}'"
# define ESPRPAR		15
# define ESPRPAR_STR	"error: sprites parameters"
# define ESPRGET		16
# define ESPRGET_STR	"error: sprites content"
# define ESPRDEF		17
# define ESPRDEF_STR	"error: sprites already definded"
# define EOPAR			18
# define EOPAR_STR		"error: object parameters"
# define EOGET			19
# define EOGET_STR		"error: object content"
# define EODEF			20
# define EODEF_STR		"error: object already definded"
# define EBTEX			21
# define EBTEX_STR		"error: bad texture ID"
# define EDBOR			22
# define EDBOR_STR		"error: map: door on map border"
# define EDWALL			23
# define EDWALL_STR		"error: door: not enough or too many wall neighbours"

# define ERRMSG_CNT		24
# define ERRMSG_STR1	ENOBR_STR, EBTYPE_STR, EUNKST_STR, EMPAR_STR, EMGET_STR
# define ERRMSG_STR2	ETPAR_STR, ETGET_STR, EMDEF_STR, ETDEF_STR, ESPAR_STR
# define ERRMSG_STR3	ESGET_STR, ESDEF_STR, ESOOR_STR, ESONW_STR, ENCBR_STR
# define ERRMSG_STR4	ESPRPAR_STR, ESPRGET_STR, ESPRDEF_STR, EOPAR_STR
# define ERRMSG_STR5	EOGET_STR, EODEF_STR, EBTEX_STR, EDBOR_STR, EDWALL_STR
# define ERRMSG_STR1_1	ERRMSG_STR1, ERRMSG_STR2, ERRMSG_STR3, ERRMSG_STR4
# define ERRMSG_STR1_2	ERRMSG_STR5
# define ERRMSG_STR		ERRMSG_STR1_1, ERRMSG_STR1_2

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

# define P_ENT_NAME_1_0		"Spawn"
# define P_ENT_NAME_1_1		spawn_ent_analyze
# define P_ENT_NAME_1_2		spawn_content_analyze

# define P_ENT_NAME_2_0		"Object"
# define P_ENT_NAME_2_1		object_ent_analyze
# define P_ENT_NAME_2_2		object_content_analyze

# define P_ENT_TOSTRING1	P_ENT_NAME_0_0, P_ENT_NAME_1_0, P_ENT_NAME_2_0
# define P_ENT_TOSTRING2
# define P_ENT_TOSTRING		P_ENT_TOSTRING1, P_ENT_TOSTRING2

# define P_ENT_FUNCT1		P_ENT_NAME_0_1, P_ENT_NAME_1_1, P_ENT_NAME_2_1
# define P_ENT_FUNCT2
# define P_ENT_FUNCT		P_ENT_FUNCT1, P_ENT_FUNCT2

# define P_CONTENT_FUNCT1	name_ent_analyze, P_ENT_NAME_0_2, P_ENT_NAME_1_2
# define P_CONTENT_FUNCT2	P_ENT_NAME_2_2
# define P_CONTENT_FUNCT	P_CONTENT_FUNCT1, P_CONTENT_FUNCT2

# define P_ENT_COUNT		3

char				*ft_stackpop(t_stack **stack);
int					ft_stackpush(t_stack **stack, char *str);
void				ft_stackclear(t_stack **stack);

int					read_file(char *filename, t_stack **stack);
int					load_map(t_env *env, t_map *map, char *mapfile);
int					parse_map(t_env *env, int conf_fd);
void				map_destroy(t_map *map);

/*
**		content_analyze
*/

int					load_textures(t_env *env, t_parser *parser);
int					texture_content_analyze(t_env *env, t_parser *parser);
int					map_content_analyze(t_env *env, t_parser *parser);
int					spawn_content_analyze(t_env *env, t_parser *parser);
int					sprite_content_analyze(t_env *env, t_parser *parser);
int					object_content_analyze(t_env *env, t_parser *parser);


/*
**	ent_analyze.c
*/

int					map_ent_analyze(t_env *env, t_parser *parser);
int					texture_ent_analyze(t_env *env, t_parser *parser);
int					name_ent_analyze(t_env *env, t_parser *parser);
int					spawn_ent_analyze(t_env *env, t_parser *parser);
int					sprite_ent_analyze(t_env *env, t_parser *parser);
int					object_ent_analyze(t_env *env, t_parser *parser);

/*
**	tools.c
*/

int					ft_iswhitespace(int c);
char				*skip_whitespace(char *str);
void				destroy_map_data(t_map *map);
int					new_map_data(t_map *map);
int					is_filechar(int c);

/*
**	tools_2.c
*/

int					get_and_skipivec2(t_parser *parser, t_ivec2 *get);
int					get_and_skipdigit(t_parser *parser, int *get);
int					get_and_skipsdigit(t_parser *parser, int *get);
int					get_and_skipvec2(t_parser *parser, t_vec2 *get);
int					get_and_skipfdigit(t_parser *parser, t_float *get);

/*
**	tools_3.c
*/

int					parser_gnl(t_parser *parser);
char				*get_next_word(t_parser *parser, int (*cmp)(int));
int					get_next_char(t_parser *parser, int c);
int					skipchar(t_parser *parser, char c);
int					skipword(t_parser *parser, char *word);
size_t				get_next_word_len(t_parser *parser, int (*cmp)(int));

/*
**	tools_4.c
*/

void				destroy_textures(t_env *env);
int					is_valid_filename(char *filename);
int					get_next_opbracket(t_parser *parser);
int					get_next_clbracket(t_parser *parser);
#endif
