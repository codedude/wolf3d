# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 23:02:03 by vparis            #+#    #+#              #
#    Updated: 2018/12/02 23:02:07 by vparis           ###   ########.fr        #
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

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	../libft

SRCS		=	$(SRCD)/tp_queue.c $(SRCD)/tp_thread.c \
				$(SRCD)/tp_pool.c $(SRCD)/tp_pool2.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(LIBFTD)/includes -I$(INCD) -pthread -O3
LDFLAGS		+=	-Wall -Wextra -Werror -Wno-unused-result -ansi -pedantic
LDLIBS		+=

HEADER		=	$(INCD)/libtpool.h

.PHONY: clean fclean re showlib

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) rs $@ $(OBJS)
	@echo "libtpool - compiled"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $< $(LDLIBS)

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
