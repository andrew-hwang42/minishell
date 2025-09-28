# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahwang <ahwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/24 15:50:04 by yhwang            #+#    #+#              #
#    Updated: 2025/09/28 03:28:11 by ahwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RESET		:= $(shell tput -Txterm sgr0)
BLUE		:= $(shell tput -Txterm setaf 6)

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
RM = rm -f

LIBFT_DIR = ./libft
LIBFT_NAME = libft.a
LIBFT = $(addprefix $(LIBFT_DIR)/, $(LIBFT_NAME))

PARSE = ./parse/
EXECUTE = ./execute/

FILES =	main \
		set_env \
		detect_signal \
		utils \
		$(PARSE)parse \
		$(PARSE)check_parse_err \
		$(PARSE)check_token \
		$(PARSE)check_token_pos \
		$(PARSE)apply_env_var \
		$(PARSE)remove_dollar_quote \
		$(PARSE)replace_env_key_to_val \
		$(PARSE)save_data \
		$(PARSE)save_option \
		$(PARSE)save_redir \
		$(PARSE)parse_utils \

INCS_DIR = ./incs

SRCS_DIR = ./srcs

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))
OBJS = $(addprefix $(SRCS_DIR)/, $(addsuffix .o, $(FILES)))

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCS_DIR)

all: $(LIBFT_NAME) $(NAME)

$(LIBFT_NAME):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ -I$(INCS_DIR) -lreadline
	@echo "$(BLUE)Minishell compiled ✅$(RESET)"

clean:
	@make clean -C $(LIBFT_DIR)
	$(RM) $(OBJS)
	@echo "$(BLUE)Deleted object files for minishell ✅$(RESET)"

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	@echo "$(BLUE)Deleted minishell executable ✅$(RESET)"

re: fclean all

.PHONY : all clean fclean re
