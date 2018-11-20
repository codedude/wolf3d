# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/11/02 18:25:40 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	snake
CC			=	clang

SRCD		=	srcs
INCD		=	includes
LIBFTD		=	libft
SDLD		=	sdl

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	SDLLIBD		=	$(HOME)/.brew/lib
	SDLINCD		=	$(HOME)/.brew/include/SDL2
else
	SDLLIBD		=	/usr/lib/x86_64-linux-gnu
	SDLINCD		=	/usr/include/SDL2
endif

FILES		=	main.c sprite.c raycast.c
FILES		+=	$(SDLD)/sdl1.c $(SDLD)/sdl2.c $(SDLD)/sdl3.c

SRCS		=	$(addprefix $(SRCD)/, $(FILES))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(SDLINCD) -I$(LIBFTD)/includes -I$(INCD)
LDFLAGS		+=	-Wextra -Wall -Wno-unused-result
LDLIBS		+=	-L$(LIBFTD) -lft -L$(SDLLIBD) -lSDL2 -lSDL2_image -lm

.PHONY: clean fclean re rer

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	$(CC) $(CFLAGS) $^ $(LDLIBS) -o $(NAME)
	@echo "$(NAME) - compiled"

%.o: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	make -C $(LIBFTD) clean
	@rm -f $(OBJS)
	@echo "$(NAME) - cleaned"

fclean: clean
	make -C $(LIBFTD) __fclean
	@rm -f $(NAME)
	@echo "$(NAME) - lib cleaned"

re: fclean all

rer:
	@rm -f $(NAME)
	@rm -f $(OBJS)
	make $(NAME)
