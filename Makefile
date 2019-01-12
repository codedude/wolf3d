# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2019/01/12 18:22:34 by vparis           ###   ########.fr        #
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
EVENTD		=	event
RENDERD		=	render
UTILSD		=	utils

LDLIBS		+=	-L$(LIBFTD) -L$(SDLLIBD) -L$(LIBTPOOLD) \
				-lm -lSDL2 -lSDL2_image \
				$(LIBFTD)/libft.a $(LIBTPOOLD)/libtpool.a $(LIBFTD)/libft.a

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	SDLLIBD		=	$(HOME)/.brew/lib
	SDLINCD		=	$(HOME)/.brew/include/SDL2
else
	SDLLIBD		=	/usr/lib/x86_64-linux-gnu
	SDLINCD		=	/usr/include/SDL2
	LDLIBS		+=	-pthread
endif

CFLAGS		+=	-I$(SDLINCD) -I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes \
				-I$(INCD) -g3 -Wextra -Wall -Wno-unused-result \
				-Wconversion -O2 #-fsanitize=address
LDFLAGS		+=	-O2 #-fsanitize=address

SRCS_F		=	main env
SRCS_F		+=	$(RENDERD)/raycast $(RENDERD)/raycast_2 $(RENDERD)/raycast_3 \
				$(RENDERD)/raycast_4 $(RENDERD)/entity $(RENDERD)/entity_new \
				$(RENDERD)/list \
				$(RENDERD)/depth_filters $(RENDERD)/color_filters \
				$(RENDERD)/raycast_sprites $(RENDERD)/list $(RENDERD)/anim \
				$(RENDERD)/anim_spec $(RENDERD)/anim_list
SRCS_F		+=	$(SDLD)/sdl1 $(SDLD)/sdl2 $(SDLD)/sdl3 $(SDLD)/sdl_load_image \
				$(SDLD)/export_bmp_1 $(SDLD)/export_bmp_2 \
				$(SDLD)/texture_1 $(SDLD)/texture_2
SRCS_F		+=	$(PARSERD)/map_parser $(PARSERD)/stack $(PARSERD)/reader
SRCS_F		+=	$(EVENTD)/move_1 $(EVENTD)/move_2 $(EVENTD)/move_3 \
				$(EVENTD)/event_1 $(EVENTD)/event_2 $(EVENTD)/event_3 \
				$(EVENTD)/event
SRCS_F		+=	$(UTILSD)/vector $(UTILSD)/types

HEADERS_F	= 	env sdl_m raycast types list texture entity anim event \
				export_bmp

SRCS		=	$(addprefix $(SRCD)/, $(addsuffix .c, $(SRCS_F)))
HEADERS		=	$(addprefix $(INCD)/, $(addsuffix .h, $(HEADERS_F)))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

.PHONY: all clean fclean re rer valg

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(LIBTPOOLD)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@
	@echo "$(NAME) - compiled"

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -o $@ -c $<

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
	valgrind --show-leak-kinds=all --leak-resolution=high --track-origins=yes \
	./$(NAME) map.w3d

bench:
	valgrind --tool=callgrind ./$(NAME) map.w3d
