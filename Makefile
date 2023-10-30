# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jugingas <jugingas@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 11:08:46 by jugingas          #+#    #+#              #
#    Updated: 2023/10/30 15:06:55 by jugingas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		=		src/main.c						\
				src/main_functions.c			\
				src/main_functions2.c			\
				src/utils.c						\
				src/utils2.c					\
				src/utils3.c					\
				src/utils4.c					\
				src/utils5.c					\
				src/utils6.c					\
				src/badline.c					\
				src/ft_memset.c					\
				src/ft_calloc.c					\
				src/builtins.c					\
				src/builtins2.c					\
				src/builtins3.c					\
				src/ft_split.c					\
				src/export.c					\
				src/env.c						\
				src/env2.c						\
				src/ft_strdup.c					\
				src/single_double_quote.c		\
				src/single_double_quote2.c		\
				src/single_double_quote3.c		\
				src/signals.c					\
				src/dlx.c						\
				src/pipe.c						\
				src/pipe2.c						\
				src/pipe3.c						\
				src/pipe4.c						\
				src/redirections.c				\
				src/get_heredoc.c				\
				src/init_struct.c				\
				src/str_eg_cpy.c				\
				src/get_next_line.c				\
				src/get_next_line_utils.c		\
				src/itoa.c						\
				src/ft_atoi.c					\

NAME		=	minishell
OBJS		=	$(SRC:.c=.o)
LIBS		=	-lreadline
CC			=	cc
FLAGS		=	-g -Werror -Wextra -Wall -I include

#------------------------------------------------------------------

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS) $(DEPS)

fclean: clean
	@rm -rf $(NAME)

re:
	@$(MAKE) fclean
	@$(MAKE) all

#------------------------------------------------------------------

.PHONY: clean fclean re
