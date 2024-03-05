# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alfofern <alfofern@student.42malaga.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/23 12:21:53 by alfofern          #+#    #+#              #
#    Updated: 2024/01/22 12:42:45 by alfofern         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	src/main/main.c						\
		src/initvar/init_var.c		 		\
		src/readprompt/read_prompt.c 		\
		src/parser/parser.c					\
		src/parser/parser_utils.c			\
		src/parser/parser_utils2.c			\
		src/parser/split_pipes.c 			\
		src/parser/parser_cmd.c    			\
		src/parser/parser_infile.c			\
		src/parser/parser_outfile.c			\
		src/utils/utils.c					\
		src/parser/ft_split_pipex.c			\
		src/parser/parser_var.c  			\
		src/executer/executer.c				\
		src/executer/get_path.c				\
		src/parser/check_syntax.c			\
		src/parser/parser_heredoc.c			\
		src/parser/parser_hd_del.c			\
		src/free/free.c						\
		src/redirections/fd_handler.c		\
		src/redirections/pipes.c			\
		src/builtins/env.c					\
		src/builtins/echo.c					\
		src/builtins/cd.c					\
		src/initvar/charge_env_00.c			\
		src/initvar/charge_env_01.c			\
		src/initvar/charge_env_02.c			\
		src/print/env.c        				\
		src/print/print_export.c        	\
		src/utils/ft_mtrxlen.c				\
		src/utils/ft_strcmp.c				\
		src/utils/ft_lstlen.c				\
		src/free/ft_free_env_lst.c			\
		src/free/ft_free_matrix.c			\
		src/builtins/export.c				\
		src/builtins/pwd.c					\
		src/builtins/unset.c				\
		src/builtins/exit.c					\
		src/signals/signals.c				\
		src/redirections/red_utils.c		\
		src/executer/executer_utils.c		\
		src/parser/parser_inout_utils.c		\
		src/parser/ft_sp_px_utils.c			\
		src/builtins/cd_utils.c				\
		src/print/title.c
		
OBJ_DIR = obj

OBJ = $(addprefix $(OBJ_DIR)/, $(patsubst %.c, %.o, $(SRC)))

LIBFT = libft/libft.a

CC = gcc -g 

MAKEFLAGS += --quiet

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C ./libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	$(MAKE) clean -C ./libft

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
