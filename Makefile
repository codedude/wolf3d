# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/11/27 17:34:05 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
LIBTPOOLD	=	libtpool
SDLD		=	sdl

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	SDLLIBD		=	$(HOME)/.brew/lib
	SDLINCD		=	$(HOME)/.brew/include/SDL2
else
	SDLLIBD		=	/usr/lib/x86_64-linux-gnu
	SDLINCD		=	/usr/include/SDL2
endif

FILES		=	main.c env.c raycast.c raycast_2.c raycast_3.c map_parser.c \
				manage_binds.c
FILES		+=	$(SDLD)/sdl1.c $(SDLD)/sdl2.c $(SDLD)/sdl3.c $(SDLD)/sdl4.c

SRCS		=	$(addprefix $(SRCD)/, $(FILES))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(SDLINCD) -I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes \
				-I$(INCD)
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result -g -O2
LDLIBS		+=	-L$(LIBFTD) -L$(SDLLIBD) -L$(LIBTPOOLD) \
				-lft -ltpool -lSDL2 -lSDL2_image -lm -lft

HEADER		= 	$(INCD)/env.h $(INCD)/sdl_m.h $(INCD)/raycast.h

.PHONY: clean fclean re rer

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(LIBTPOOLD)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(NAME) # -fsanitize=address
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
