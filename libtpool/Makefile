# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/02 23:02:03 by vparis            #+#    #+#              #
<<<<<<< HEAD
#    Updated: 2019/01/02 12:57:04 by vparis           ###   ########.fr        #
=======
#    Updated: 2018/12/15 20:31:47 by jbulant          ###   ########.fr        #
>>>>>>> 935f2ef52abe6a61f552b7f3beb1fecb27471c00
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

SRCS		=	$(SRCD)/tp_queue.c $(SRCD)/tp_thread.c $(SRCD)/tp_thread2.c \
				$(SRCD)/tp_pool.c $(SRCD)/tp_pool2.c
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

<<<<<<< HEAD
CFLAGS		+=	-I$(LIBFTD)/includes -I$(INCD) -pthread -O3 -flto
=======
CFLAGS		+=	-I$(LIBFTD)/includes -I$(INCD) -pthread -O3 #-g -fsanitize=address

>>>>>>> 935f2ef52abe6a61f552b7f3beb1fecb27471c00
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
