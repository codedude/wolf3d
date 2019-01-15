# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 23:02:03 by vparis            #+#    #+#              #
#    Updated: 2019/01/15 11:12:25 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libtpool.a
CC			=	clang

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	AR		= ar
else
	AR		= llvm-ar
endif

DEBUG			?=	1
FLAGS_OPT		=
ifeq ($(DEBUG),0)
	FLAGS_OPT	=	-O3 -flto
else ifeq ($(DEBUG),1)
	FLAGS_OPT	=	-g3 -O2
else ifeq ($(DEBUG),2)
	FLAGS_OPT	=	-g3 -fsanitize=address
else ifeq ($(DEBUG),3)
	FLAGS_OPT	=	-g3
endif

CFLAGS		+=	-I$(LIBFTD)/includes -I$(INCD) -pthread -Wall -Wextra -Werror \
				 -Wno-unused-result -ansi -pedantic $(FLAGS_OPT)

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	../libft

SRCS		=	$(SRCD)/tp_queue.c $(SRCD)/tp_thread.c $(SRCD)/tp_thread2.c \
				$(SRCD)/tp_pool.c $(SRCD)/tp_pool2.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

HEADERS		=	$(INCD)/libtpool.h

.PHONY: all clean fclean __fclean re showlib

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) rs $@ $(OBJS)
	@echo "libtpool - compiled"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -o $@ -c $< $(LDLIBS)

showlib: $(NAME)
	@$(AR) -t $(NAME)

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
