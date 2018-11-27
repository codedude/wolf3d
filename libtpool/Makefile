# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/11/27 22:45:46 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libtpool.a
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	../libft

SRCS		=	$(SRCD)/tp_queue.c $(SRCD)/tp_thread.c \
				$(SRCD)/tp_pool.c $(SRCD)/tp_pool2.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(LIBFTD)/includes -I$(INCD) -pthread -g3 #-O2
LDFLAGS		+=	-Wall -Wextra -Werror -Wno-unused-result
LDLIBS		+=

HEADER		=	$(INCD)/libtpool.h

.PHONY: clean fclean re showlib

all: $(NAME)

$(NAME): $(OBJS)
	@ar rs $@ $(OBJS)
	@echo "libtpool - compiled"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $< $(LDLIBS)

showlib: $(NAME)
	@ar -t $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "libtpool - objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "libtpool - lib cleaned"

__fclean:
	@rm -f $(NAME)
	@echo "libtpool - lib cleaned"

re: fclean all
