# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/12/17 13:15:40 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
LIBTPOOLD	=	libtpool
SDLD		=	sdl
PARSERD		=	parser

LDLIBS		+=	-L$(LIBFTD) -L$(SDLLIBD) -L$(LIBTPOOLD) \
				-lm -lSDL2 -lSDL2_image \
				libft/libft.a libtpool/libtpool.a libft/libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	SDLLIBD		=	$(HOME)/.brew/lib
	SDLINCD		=	$(HOME)/.brew/include/SDL2
else
	SDLLIBD		=	/usr/lib/x86_64-linux-gnu
	SDLINCD		=	/usr/include/SDL2
	LDLIBS		+=	-pthread
endif

FILES		=	main.c env.c raycast.c raycast_2.c raycast_3.c raycast_3.c \
				manage_binds.c types.c depth_filters.c vector.c \
				raycast_sprites.c list.c \
				color_filters.c move_1.c move_2.c move_3.c raycast_4.c
FILES		+=	$(SDLD)/sdl1.c $(SDLD)/sdl2.c $(SDLD)/sdl3.c \
				$(SDLD)/sdl_load_image.c  $(SDLD)/sdl_textures.c \
				$(SDLD)/sdl_sprites.c
FILES		+=	$(PARSERD)/map_parser.c $(PARSERD)/stack.c \
				$(PARSERD)/reader.c

SRCS		=	$(addprefix $(SRCD)/, $(FILES))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(SDLINCD) -I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes \
				-I$(INCD) -O3 -g3 #-fsanitize=address
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result -Wconversion


HEADER		= 	$(INCD)/env.h $(INCD)/sdl_m.h $(INCD)/raycast.h \
				$(INCD)/types.h $(INCD)/list.h

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
