# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: slevaslo <slevaslo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/06 15:46:35 by pdosso-d          #+#    #+#              #
#    Updated: 2023/03/10 19:11:32 by slevaslo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	pipex_utils.c\
					pipex.c\
					here_doc.c\

OBJS			=	$(SRCS:.c=.o)

CC              =   gcc
RM              =   rm -f
CFLAGS          =   -Wall -Wextra -Werror

NAME            =    pipex

LIBRARIES		=	-L libftprintfgnl -lftprintfgnl
INCLUDES		=	-Ilibftprintfgnl

all:            $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror $(INCLUDES) -g3 -c $< -o $@

$(NAME):		$(OBJS)
				make -C libftprintfgnl
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBRARIES)

clean:
				make -C libftprintfgnl clean
				$(RM) $(OBJS) $(OBJS_BONUS)


fclean:         clean
				make -C libftprintfgnl fclean
				$(RM) $(NAME) $(NAME_BONUS)


re:             fclean $(NAME) $(NAME_BONUS)

.PHONY:			all clean fclean re bonus norme
