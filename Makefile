# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/08 14:26:55 by amonteli          #+#    #+#              #
#    Updated: 2021/04/17 00:52:01 by amonteli         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME			=		minishell

INC_DIR			=		includes

HEADERS			=		includes/minishell.h

CC				=		clang

CFLAGS 			= 		-Wall -Wextra -g3 -fsanitize=address

SRCS			=		\
						main.c \
						$(addprefix checker/, input_checker.c) \
						$(addprefix lexer/, lexer.c) \
						$(addprefix splitter/, separator.c) \
						$(addprefix utilities/, struct.c ui.c) \

OBJS			= 		$(addprefix srcs/, $(SRCS:.c=.o))

LIB 			= 		libft/libft.a

all				: 		$(NAME)

$(NAME)		: $(OBJS)
		@make -C libft
		@$(CC) $(CFLAGS) $(OBJS) -I $(HEADERS) $(LIB) -o $(NAME)

%.o: %.c $(HEADERS)
		@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

bonus		:		$(NAME)

clean		:
		@/bin/rm -f $(OBJS)
		@make clean -C libft

fclean		:		clean
		@/bin/rm -f $(NAME)
		@make fclean -C libft

re			:		fclean all
