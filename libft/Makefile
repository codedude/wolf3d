# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vparis <vparis@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/02 17:37:24 by vparis            #+#    #+#              #
#    Updated: 2018/12/27 13:10:03 by vparis           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a
CC			= clang

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	AR		= ar
else
	AR		= llvm-ar
endif

SRCD		= srcs
INCD		= includes
OUTPUTD		= $(SRCD)/output
MATHD		= $(SRCD)/math
MEMORYD		= $(SRCD)/memory
STRINGD		= $(SRCD)/string
ASCIID		= $(SRCD)/ascii
CONVERTD	= $(SRCD)/convert
LISTD		= $(SRCD)/list
INPUTD		= $(SRCD)/input

LIBFT_SRCS	= $(OUTPUTD)/ft_putchar_fd.c $(OUTPUTD)/ft_putrevendl_fd.c \
			$(OUTPUTD)/ft_putchar_nonprint.c $(OUTPUTD)/ft_putendl_fd.c \
			$(OUTPUTD)/ft_putchar.c $(OUTPUTD)/ft_putrevendl.c \
			$(OUTPUTD)/ft_putnbr_fd.c $(OUTPUTD)/ft_putnbr.c \
			$(OUTPUTD)/ft_putendl.c $(OUTPUTD)/ft_putstr_nonprint_fd.c \
			$(OUTPUTD)/ft_putrevstr.c $(OUTPUTD)/ft_putstr_fd.c \
			$(OUTPUTD)/ft_putstr_nonprint.c $(OUTPUTD)/ft_putrevstr_fd.c \
			$(OUTPUTD)/ft_putchar_nonprint_fd.c $(OUTPUTD)/ft_putstr.c
LIBFT_SRCS	+= $(STRINGD)/ft_strncpy.c $(STRINGD)/ft_strsub.c \
			$(STRINGD)/ft_strsplit.c $(STRINGD)/ft_strnequ.c \
			$(STRINGD)/ft_striter.c $(STRINGD)/ft_strstr.c \
			$(STRINGD)/ft_strsplit_str.c $(STRINGD)/ft_strmap.c \
			$(STRINGD)/ft_strlen.c $(STRINGD)/ft_striteri.c \
			$(STRINGD)/ft_strnstr.c $(STRINGD)/ft_strcat.c \
			$(STRINGD)/ft_strclr.c $(STRINGD)/ft_strmapi.c \
			$(STRINGD)/ft_strlcat.c $(STRINGD)/ft_strcat2.c \
			$(STRINGD)/ft_strchr.c $(STRINGD)/ft_strsplit_whitespaces.c \
			$(STRINGD)/ft_strequ.c $(STRINGD)/ft_strncat.c \
			$(STRINGD)/ft_strrev.c $(STRINGD)/ft_strdup.c \
			$(STRINGD)/ft_strnew_fast.c $(STRINGD)/ft_strjoin.c \
			$(STRINGD)/ft_strcmp.c $(STRINGD)/ft_strrchr.c \
			$(STRINGD)/ft_strcpy.c $(STRINGD)/ft_strsplit_free.c \
			$(STRINGD)/ft_strdel.c $(STRINGD)/ft_strtrim.c \
			$(STRINGD)/ft_strnew.c $(STRINGD)/ft_strncmp.c \
			$(STRINGD)/ft_strtoupper.c $(STRINGD)/ft_strtolower.c
LIBFT_SRCS	+= $(MEMORYD)/ft_memccpy_fast.c $(MEMORYD)/ft_memset.c \
			$(MEMORYD)/ft_memalloc_fast.c $(MEMORYD)/ft_memchr.c \
			$(MEMORYD)/ft_memmove.c $(MEMORYD)/ft_memccpy.c \
			$(MEMORYD)/ft_memcmp.c $(MEMORYD)/ft_memalloc.c \
			$(MEMORYD)/ft_memdel.c $(MEMORYD)/ft_memchr_fast.c \
			$(MEMORYD)/ft_memrealloc.c $(MEMORYD)/ft_memrealloc_fast.c \
			$(MEMORYD)/ft_memcpy.c $(MEMORYD)/ft_bzero.c
LIBFT_SRCS	+= $(MATHD)/ft_sqrt.c $(MATHD)/ft_find_next_prime.c \
			$(MATHD)/ft_isprime.c $(MATHD)/ft_max3.c \
			$(MATHD)/ft_abs.c $(MATHD)/ft_min.c $(MATHD)/ft_min3.c \
			$(MATHD)/ft_fibonacci.c $(MATHD)/ft_max.c $(MATHD)/ft_angle.c \
			$(MATHD)/ft_power.c $(MATHD)/ft_factorial.c
LIBFT_SRCS	+= $(CONVERTD)/ft_atoi_base.c $(CONVERTD)/ft_atoi_s.c \
			$(CONVERTD)/ft_itoa.c $(CONVERTD)/ft_atoi.c $(CONVERTD)/ft_clamp.c \
			$(CONVERTD)/ft_atof_s.c
LIBFT_SRCS	+= $(ASCIID)/ft_toupper.c $(ASCIID)/ft_islower.c \
			$(ASCIID)/ft_isgraph.c $(ASCIID)/ft_isupper.c \
			$(ASCIID)/ft_isspace.c $(ASCIID)/ft_isdigit.c \
			$(ASCIID)/ft_iscntrl.c $(ASCIID)/ft_ischarset.c \
			$(ASCIID)/ft_isalnum.c $(ASCIID)/ft_isblank.c \
			$(ASCIID)/ft_isalpha.c $(ASCIID)/ft_ispunct.c \
			$(ASCIID)/ft_tolower.c $(ASCIID)/ft_isprint.c \
			$(ASCIID)/ft_isxdigit.c $(ASCIID)/ft_isascii.c
LIBFT_SRCS	+= $(LISTD)/ft_lstnew.c $(LISTD)/ft_lstdelone.c \
			$(LISTD)/ft_lstdel.c $(LISTD)/ft_lstadd.c \
			$(LISTD)/ft_lstiter.c $(LISTD)/ft_lstmap.c $(LISTD)/ft_lstshift.c \
			$(LISTD)/ft_lstdel_raw.c
LIBFT_SRCS	+= $(INPUTD)/ft_gnl.c

OBJS		= $(patsubst %.c, %.o, $(LIBFT_SRCS))
LDFLAGS		+= -Werror -Wall -Wextra -Wno-unused-result -ansi -pedantic
CFLAGS		+= -I$(INCD) -O3 -flto

HEADER		=	$(INCD)/libft.h $(INCD)/ft_type.h $(INCD)/ft_list.h \
				$(INCD)/ft_input.h $(INCD)/ft_math.h

.PHONY: clean fclean re showlib

all: $(NAME)

$(NAME): $(OBJS)
	@$(AR) rs $@ $(OBJS)
	@echo "libft - compiled"

%.o: %.c $(HEADER)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

showlib: $(NAME)
	@$(AR) -t $(NAME)

clean:
	@rm -f $(OBJS)
	@echo "libft - objects cleaned"

fclean: clean
	@rm -f $(NAME)
	@echo "libft - lib cleaned"

__fclean:
	@rm -f $(NAME)
	@echo "libft - lib cleaned"

re: fclean all
