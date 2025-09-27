# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/05 14:21:08 by ahwang            #+#    #+#              #
#    Updated: 2025/09/27 06:25:23 by ahwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f

LIBFT = ft_atoi \
		ft_bzero \
		ft_calloc \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_itoa \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_putchar_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putstr_fd \
		ft_split \
		ft_strchr \
		ft_strdup \
		ft_striteri \
		ft_strjoin \
		ft_strlcat \
		ft_strlcpy \
		ft_strlen \
		ft_strmapi \
		ft_strncmp \
		ft_strnstr \
		ft_strrchr \
		ft_strtrim \
		ft_substr \
		ft_tolower \
		ft_toupper

GNL = get_next_line \
      		get_next_line_utils

FT_PRINTF = ft_putchar \
		ft_putstr \
		ft_putnbr \
		ft_unsigned_int \
		ft_hexa \
		ft_pointer \
		check_args \
		ft_printf

INCS_DIR = ./incs

LIBFT_DIR = ./srcs/libft
FT_PRINTF_DIR = ./srcs/ft_printf
GNL_DIR = ./srcs/get_next_line

LIBFT_SRCS = $(addprefix $(LIBFT_DIR)/, $(addsuffix .c, $(LIBFT)))
FT_PRINTF_SRCS = $(addprefix $(FT_PRINTF_DIR)/, $(addsuffix .c, $(FT_PRINTF)))
GNL_SRCS = $(addprefix $(GNL_DIR)/, $(addsuffix .c, $(GNL)))

LIBFT_OBJS = $(addprefix $(LIBFT_DIR)/, $(addsuffix .o, $(LIBFT)))
FT_PRINTF_OBJS = $(addprefix $(FT_PRINTF_DIR)/, $(addsuffix .o, $(FT_PRINTF)))
GNL_OBJS = $(addprefix $(GNL_DIR)/, $(addsuffix .o, $(GNL)))

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< -I$(INCS_DIR)

$(NAME): $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)
	$(AR) $@ $^
	@echo "$(BLUE)Libft compiled ✅$(RESET)"

all: $(NAME)

clean:
	$(RM) $(LIBFT_OBJS) $(FT_PRINTF_OBJS) $(GNL_OBJS)
	@echo "$(BLUE)Deleted object files for libft ✅$(RESET)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(BLUE)Deleted libft executable ✅$(RESET)"

re: clean all

.PHONY: all clean fclean re
