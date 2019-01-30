# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2019/01/30 13:13:06 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	w3d_generator
CC			=	clang

INCD		=	includes

PARENT_INCD	=	../includes
LIBFTD		=	../libft
LIBTPOOLD	=	../libtpool

SRCD		=	srcs
PALETTE_D	=	palette
UI_D		=	UI
UTILS_D		=	utils
DRAW_D		=	draw_tools
MAP_EDIT_D	=	map_edit
OBJ_EDIT_D	=	obj_edit
EDITOR_D	=	editor
ENV_D		=	env
INSPECT_D	=	inspector
MTRACK_D	=	mouse_tracker
TOOLSET_D	=	toolset
SAVE_D		=	save
BINDS_D		=	bindings

PARENT_SD	=	../srcs
SDLD		=	sdl
PARSERD		=	parser
RENDERD		=	render

LDLIBS		+=	-L$(LIBFTD) -L$(SDLLIBD) -L$(LIBTPOOLD) \
				-lm -lSDL2 -lSDL2_image -lSDL2_mixer \
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

CFLAGS		+=	-I$(SDLINCD) -I$(LIBFTD)/includes -I$(LIBTPOOLD)/includes \
				-I$(INCD) -I$(PARENT_INCD) -Wextra -Wall -Wno-unused-result \
				-Wconversion $(FLAGS_OPT)
LDFLAGS		+=	$(FLAGS_OPT)

LDFLAGS		+=	-flto -O3 #-fsanitize=address

SRCS_F		=	main
SRCS_F		+=	$(addprefix $(PALETTE_D)/, $(PALETTE_F))
SRCS_F		+=	$(addprefix $(UTILS_D)/, $(UTILS_F))
SRCS_F		+=	$(addprefix $(UI_D)/, $(UI_F))
SRCS_F		+=	$(addprefix $(DRAW_D)/, $(DRAW_F))
SRCS_F		+=	$(addprefix $(MAP_EDIT_D)/, $(MAP_EDIT_F))
SRCS_F		+=	$(addprefix $(OBJ_EDIT_D)/, $(OBJ_EDIT_F))
SRCS_F		+=	$(addprefix $(EDITOR_D)/, $(EDITOR_F))
SRCS_F		+=	$(addprefix $(ENV_D)/, $(ENV_F))
SRCS_F		+=	$(addprefix $(INSPECT_D)/, $(INSPECT_F))
SRCS_F		+=	$(addprefix $(MTRACK_D)/, $(MTRACK_F))
SRCS_F		+=	$(addprefix $(TOOLSET_D)/, $(TOOLSET_F))
SRCS_F		+=	$(addprefix $(SAVE_D)/, $(SAVE_F))
SRCS_F		+=	$(addprefix $(BINDS_D)/, $(BINDS_F))

PALETTE_F	=	common			compute_brushes_1	compute_brushes_2
UTILS_F		=	algo			sdl_draw			draw_canvas \
				lft_plus		lft_plus_2 \
				sdl_plus_f1		sdl_plus_f2
UI_F		=	buttons			buttons_tools \
				checkbox		checkbox_tools \
				slider			slider_tools \
				panel			panel_draw \
				panel_tools		panel_tools_2		panel_tools_3 \
				new_texdata		texdata_draw

DRAW_F		=	lines			cpick_tools_1		cpick_tools_2 \
				paint_bucket	draw_tex
OBJ_EDIT_F	=	obj_tools		checkbox_is_solid	handle_objects
EDITOR_F	=	editor			editor_switch \
				draw_update		draw_ui
ENV_F		=	env_init		env_destroy			init_rpanels
SAVE_F		=	check			save_file			save_map
BINDS_F		=	binds_1			binds_2				binds_3

MAP_EDIT_F	=	map_info		load_map			doors \
				map_tools_1		map_tools_2			map_tools_3
MAP_EDIT_F		+=	$(addprefix draw/, $(MAP_DRAW_F))
MAP_EDIT_F		+=	$(addprefix properties/, $(MAP_PROPS_F))
MAP_DRAW_F		=	draw_map	draw_map_obj	draw_node
MAP_PROPS_F		=	init		props_f1		props_f2

INSPECT_F	=	inspector_init
INSPECT_F		+=	$(addprefix door/, $(INSPECT_D_F))
INSPECT_F		+=	$(addprefix obj_edit/, $(INSPECT_OE_F))
INSPECT_F		+=	$(addprefix painter/, $(INSPECT_P_F))
INSPECT_F		+=	$(addprefix world/, $(INSPECT_W_F))
INSPECT_D_F		=	create		buttons_f1		buttons_f2
INSPECT_OE_F	=	create		buttons_f1		buttons_f2
INSPECT_P_F		=	create		buttons_f		init_selectors
INSPECT_W_F		=	create		buttons_f		radar

TOOLSET_F	=	toolset

MTRACK_F	=	mouse_tools		init
MTRACK_F		+=	$(addprefix trigger/, $(MTRACK_TRIG_F))
MTRACK_F		+=	$(addprefix update/, $(MTRACK_UPD_F))
MTRACK_F		+=	$(addprefix get_area/, $(MTRACK_GETA_F))
MTRACK_TRIG_F	=	init		trig_map_window		mw_painter		trig_rpanels
MTRACK_UPD_F	=	init		upd_map_window
MTRACK_GETA_F	=	init		get_map_window

PARENT_F	=	$(SDLD)/sdl1 $(SDLD)/sdl2 $(SDLD)/sdl3 $(SDLD)/sdl_load_image \
				$(SDLD)/export_bmp_1 $(SDLD)/export_bmp_2 \
				$(SDLD)/texture_1 $(SDLD)/texture_2 $(SDLD)/sound \
				$(SDLD)/music $(SDLD)/audio_1 $(SDLD)/audio_2
PARENT_F	+=	$(RENDERD)/entity $(RENDERD)/entity_new
PARENT_F	+=	$(PARENT_SD)/utils/types
PARENT_F	+=	$(addprefix $(PARSERD)/, $(PARSER_F))

PARSER_F	=	map_parser		stack 			reader				\
				ent_analyze		parse_map
PARSER_F	+=	$(addprefix tools/, $(PTOOLS_F))
PARSER_F	+=	$(addprefix map/, $(PMAP_F))
PARSER_F	+=	$(addprefix object/, $(POBJ_F))
PARSER_F	+=	$(addprefix spawn/, $(PSPAWN_F))
PARSER_F	+=	$(addprefix world/, $(PWORLD_F))
PTOOLS_F	=	tools			tools_2			tools_3				\
				tools_4
PMAP_F		=	map_content
POBJ_F		=	object_content
PSPAWN_F	=	spawn_content
PWORLD_F	=	world_content

HEADERS_F	=	mouse_tracker	editor		sdl_plus	inspector	\
				objects_edit	map_edit	painter		ui_positions \
				lft_plus		ui 			algo		gen_env

PARENT_HEADER	= 	env sdl_m types

SRCS		=	$(addprefix $(SRCD)/, $(addsuffix .c, $(SRCS_F)))
SRCS		+=	$(addprefix $(PARENT_SD)/, $(addsuffix .c, $(PARENT_F)))

HEADERS		=	$(addprefix $(INCD)/, $(addsuffix .h, $(HEADERS_F)))
HEADERS		+=	$(addprefix $(PARENT_INCD)/, $(addsuffix .h, $(PARENT_HEADER)))

OBJS		=	$(patsubst %.c, %.o, $(SRCS))


.PHONY: clean fclean re rer valg

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
	valgrind --show-leak-kinds=all --leak-resolution=high --track-origins=yes ./$(NAME) map.w3d

bench:
	valgrind --tool=callgrind ./$(NAME) map.w3d
