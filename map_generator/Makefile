# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/12/04 00:59:06 by jbulant          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	w3d_generator
CC			=	clang

SRCD		=	srcs
INCD		=	includes
PARENT_INCD	=	../includes
LIBFTD		=	../libft
LIBTPOOLD	=	../libtpool
SDLD		=	../srcs/sdl

LDLIBS		+=	-L$(LIBFTD) -L$(SDLLIBD) -L$(LIBTPOOLD) \
				-lm -lSDL2 -lSDL2_image \
				../libft/libft.a ../libtpool/libtpool.a ../libft/libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	SDLLIBD		=	$(HOME)/.brew/lib
	SDLINCD		=	$(HOME)/.brew/include/SDL2
else
	SDLLIBD		=	/usr/lib/x86_64-linux-gnu
	SDLINCD		=	/usr/include/SDL2
	LDLIBS		+=	-pthread
endif

FILES		=	main.c tex_previewbox.c

PARENT_FILES	=	$(SDLD)/sdl1.c $(SDLD)/sdl2.c $(SDLD)/sdl3.c $(SDLD)/sdl4.c


MGEN_FILES	=	$(MGEND)/main.c

SRCS		=	$(addprefix $(SRCD)/, $(FILES))
SRCS		+=	$(PARENT_FILES)

OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(SDLINCD) -I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes \
				-I$(INCD) -I$(PARENT_INCD) -O3 -g3 #-fsanitize=address
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result -Wconversion

HEADER			=	$(INCD)/gen_env.h $(PARENT_HEADER)

PARENT_HEADER	= 	$(PARENT_INCD)/env.h $(PARENT_INCD)/sdl_m.h \
					$(PARENT_INCD)/types.h

.PHONY: clean fclean re rer valg

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(LIBTPOOLD)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(NAME)
	@echo "$(NAME) - compiled"

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBFTD) clean
	make -C $(LIBTPOOLD) clean
	@rm -f $(OBJS)
	@echo "$(NAME) - cleaned"

fclean: clean
	make -C $(LIBFTD) __fclean
	make -C $(LIBTPOOLD) __fclean
	@rm -f $(NAME)
	@echo "$(NAME) - lib cleaned"

re: fclean all

rer:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	make $(NAME)

valg:
	valgrind --show-leak-kinds=all --leak-resolution=high --track-origins=yes ./$(NAME) map.w3d

bench:
	valgrind --tool=callgrind ./$(NAME) map.w3d
