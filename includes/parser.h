/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vparis <vparis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 14:48:58 by vparis            #+#    #+#             */
/*   Updated: 2018/12/06 13:04:47 by jbulant          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "env.h"

typedef struct		s_stack {
	struct s_stack	*previous;
	char			*str;
}					t_stack;

char				*ft_stackpop(t_stack **stack);
int					ft_stackpush(t_stack **stack, char *str);
void				ft_stackclear(t_stack **stack);

int					read_file(char *filename, t_stack **stack);
int					load_map(t_env *env, t_map *map, char *mapfile);
void				map_destroy(t_map *map);

#endif
