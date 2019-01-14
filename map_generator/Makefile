# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2019/01/14 16:38:11 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	w3d_generator
CC			=	clang

SRCD		=	srcs
INCD		=	includes
PARENT_INCD	=	../includes
LIBFTD		=	../libft
LIBTPOOLD	=	../libtpool
PARENT_SD	=	../srcs
SDLD		=	$(PARENT_SD)/sdl
PARSERD		=	$(PARENT_SD)/parser

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

FILES		=	env_destroy.c main.c manage_binds.c map.c \
				save_file.c algo.c
FILES		+=	env_tools.c tools.c mouse_tools.c mouse_track.c
FILES		+=	panel.c panel_tex.c panel_draw.c panel_tools.c
FILES		+=	buttons.c
FILES		+=	slider.c checkbox.c
FILES		+=	env_init.c inspector_init.c map_props_init.c \
				obj_prevbox_init.c wall_prevbox_init.c
FILES		+=	texdata_draw.c
FILES		+=	draw_grid_lines.c draw_grid.c draw_node.c \
				draw_line.c draw_player_radar.c draw_map.c
FILES		+=	paint_bucket_tools.c brushes.c objects.c \
				toolset.c editor.c doors.c

PARENT_FILES	=	$(SDLD)/sdl1.c $(SDLD)/sdl2.c $(SDLD)/sdl3.c \
					$(SDLD)/sdl_load_image.c $(SDLD)/sdl_sprites.c \
					$(SDLD)/sdl_textures.c
PARENT_FILES	+=	$(PARSERD)/stack.c $(PARSERD)/reader.c
PARENT_FILES	+=	$(PARENT_SD)/types.c

MGEN_FILES	=	$(MGEND)/main.c

SRCS		=	$(addprefix $(SRCD)/, $(FILES))
SRCS		+=	$(PARENT_FILES)

OBJS		=	$(patsubst %.c, %.o, $(SRCS))

CFLAGS		+=	-I$(SDLINCD) -I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes \
				-I$(INCD) -I$(PARENT_INCD) -g3 -Wextra -Wall \
				-Wno-unused-result -Wconversion -O3 -flto \
				# -fsanitize=address

LDFLAGS		+=	-flto -O3 #-fsanitize=address

HEADER			=	$(INCD)/gen_env.h $(INCD)/algo.h $(PARENT_HEADER)

PARENT_HEADER	= 	$(PARENT_INCD)/env.h $(PARENT_INCD)/sdl_m.h \
					$(PARENT_INCD)/types.h

.PHONY: clean fclean re rer valg

all: $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFTD)
	make -C $(LIBTPOOLD)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $(NAME)
	@echo "$(NAME) - compiled"

%.o: %.c $(HEADER)
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
	valgrind --show-leak-kinds=all --leak-resolution=high --track-origins=yes ./$(NAME) map.w3d

bench:
	valgrind --tool=callgrind ./$(NAME) map.w3d
