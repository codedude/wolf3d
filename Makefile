# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2019/02/04 13:51:57 by vparis           ###   ########.fr        #
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
PLAYERD		=	player
RENDERD		=	render
UTILSD		=	utils

LDLIBS		+=	-L$(LIBFTD) -L$(SDLLIBD) -L$(LIBTPOOLD) \
				-lm -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf \
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

DEBUG			?=	1
FLAGS_OPT		=
ifeq ($(DEBUG),0)
	FLAGS_OPT	=	-O3 -flto
else ifeq ($(DEBUG),1)
	FLAGS_OPT	=	-g -O2
else ifeq ($(DEBUG),2)
	FLAGS_OPT	=	-g -fsanitize=address
else ifeq ($(DEBUG),3)
	FLAGS_OPT	=	-g
endif

CFLAGS		+=	-I$(SDLINCD) -I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes \
				-I$(INCD) -Wextra -Wall -Wno-unused-result \
				-Wconversion $(FLAGS_OPT)
LDFLAGS		+=	$(FLAGS_OPT)

SRCS_F		=	main env_1 env_2
SRCS_F		+=	$(RENDERD)/render $(RENDERD)/raycast_1 $(RENDERD)/raycast_2 \
				$(RENDERD)/raycast_color $(RENDERD)/raycast_draw \
				$(RENDERD)/raycast_door_1 $(RENDERD)/raycast_door_2 \
				$(RENDERD)/raycast_sprite_1 $(RENDERD)/raycast_sprite_2 \
				$(RENDERD)/raycast_sprite_3 \
				$(RENDERD)/entity $(RENDERD)/entity_new \
				$(RENDERD)/depth_filters $(RENDERD)/color_filters \
				$(RENDERD)/list_1 $(RENDERD)/list_2 $(RENDERD)/anim \
				$(RENDERD)/anim_spec $(RENDERD)/anim_list
SRCS_F		+=	$(SDLD)/sdl1 $(SDLD)/sdl2 $(SDLD)/sdl3 $(SDLD)/sdl_load_image \
				$(SDLD)/export_bmp_1 $(SDLD)/export_bmp_2 \
				$(SDLD)/texture_1 $(SDLD)/texture_2 $(SDLD)/sound \
				$(SDLD)/music $(SDLD)/audio_1 $(SDLD)/audio_2 $(SDLD)/text_1 \
				$(SDLD)/text_2
SRCS_F		+=	$(EVENTD)/event_1 $(EVENTD)/event_2 $(EVENTD)/event_3 \
				$(EVENTD)/event $(EVENTD)/event_4
SRCS_F		+=	$(PLAYERD)/move_1 $(PLAYERD)/move_2 $(PLAYERD)/move_3 \
				$(PLAYERD)/move_4
SRCS_F		+=	$(UTILSD)/vector $(UTILSD)/types
SRCS_F		+=	$(PARSERD)/stack $(PARSERD)/reader \
				$(PARSERD)/ent_analyze $(PARSERD)/ent_analyze_2 \
				$(PARSERD)/load_map $(PARSERD)/parse_map \
				$(PARSERD)/parse_map_2 $(PARSERD)/parse_map_3 \
				$(PARSERD)/tools/tools $(PARSERD)/tools/tools_2 \
				$(PARSERD)/tools/tools_3 $(PARSERD)/tools/tools_4 \
				$(PARSERD)/tools/tools_5 $(PARSERD)/content/map_content \
				$(PARSERD)/content/world_content \
				$(PARSERD)/content/object_content \
				$(PARSERD)/content/spawn_content

HEADERS_F	= 	env sdl_m raycast types list entity anim event \
				export_bmp parser camera player audio

SRCS		=	$(addprefix $(SRCD)/, $(addsuffix .c, $(SRCS_F)))
HEADERS		=	$(addprefix $(INCD)/, $(addsuffix .h, $(HEADERS_F)))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))

.PHONY: all clean fclean re rer valg

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD) DEBUG=$(DEBUG)
	make -C $(LIBTPOOLD) DEBUG=$(DEBUG)
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
	./$(NAME) data/map/demo.w3d

bench:
	valgrind --tool=callgrind ./$(NAME) data/map/demo.w3d
