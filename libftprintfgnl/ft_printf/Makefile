# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdosso-d <pdosso-d@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/15 11:16:18 by pdosso-d          #+#    #+#              #
#    Updated: 2023/01/25 16:58:27 by pdosso-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_pftools.c \
		ft_printf.c \

OBJS = ${SRCS:.c=.o}


NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: ${NAME}

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJS)
			ar rcs ${NAME} $(OBJS)

clean:
			${RM} ${OBJS}

fclean: clean
			${RM} ${NAME}

re: fclean all


.PHONY:		all clean fclean re
