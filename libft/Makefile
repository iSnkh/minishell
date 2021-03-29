# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amonteli <amonteli@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 14:02:26 by amonteli          #+#    #+#              #
#    Updated: 2021/03/29 18:14:45 by amonteli         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME 			= 	libft.a

INC_DIR			=	includes

HEADERS			=	includes/libft.h includes/ft_printf.h includes/get_next_line.h

SRCS			=	\
					$(addprefix io/ft_, putchar_fd.c putendl_fd.c putnbr_fd.c putstr_fd.c) \
					$(addprefix lists/ft_lst, add_back.c add_front.c clear.c delone.c iter.c last.c map.c new.c size.c _append.c _append_lists.c) \
					$(addprefix memory/ft_, bzero.c calloc.c memccpy.c memchr.c memcmp.c memcpy.c memmove.c memset.c) \
					$(addprefix numbers/ft_, atoi.c itoa.c numlen.c lentostr.c lentochr.c ltoa.c lltoa_base.c ulltoa_base.c utoa.c utoa_base.c) \
					$(addprefix strings/ft_, split.c strchr.c strdup.c strjoin.c strlcat.c strlcpy.c strlen.c strmapi.c strncmp.c strncpy.c strnstr.c strrchr.c strtrim.c substr.c strbaselen.c strchr_len.c strndup.c strcpy.c strreplace.c)	\
					$(addprefix types/ft_, isalnum.c isalpha.c isascii.c isdigit.c isprint.c tolower.c toupper.c) \
					$(addprefix tabs/ft_, clear_2d_tabs.c copy_2d_tabs.c) \
					\
					$(addprefix get_next_line/, get_next_line.c get_next_line_utils.c) \
					$(addprefix printf/, ft_printf.c pf_content_manager.c pf_converter.c pf_int_converter.c pf_parser.c pf_utils.c pf_bonus.c) \

OBJS			= 	$(addprefix srcs/, $(SRCS:.c=.o))

all				: 	$(NAME)

$(NAME)			:	$(OBJS)
				@ar -rcs $(NAME) $(OBJS)

%.o:%.c 		$(HEADERS)
				@gcc -Wall -Wextra -Werror -o $@ -c $< -I $(INC_DIR)
				@echo "\033[34m█\c\033[0m"

clean			:
				@/bin/rm -f $(OBJS)
				@echo "Cleaning objects"

fclean			:	clean
				@/bin/rm -f $(NAME)
				@echo "Cleaning binaries"

re				: 	fclean all
