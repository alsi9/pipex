# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ephantom <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/01 17:43:42 by ephantom          #+#    #+#              #
#   Updated: 2021/11/30 21:20:15 by                  ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

SRCS_L	=	utils.c		path.c		ft_split.c

SRCS_A	=	pipex.c

SRCS_B	=	ft_here_doc.c	get_next_line.c  pipex_bonus.c	ft_open_file.c

HEADER	=	pipex.h

OBJS_L	=	${SRCS_L:%.c=%.o}

OBJS_A	=	${SRCS_A:%.c=%.o}

OBJS_B	=	${SRCS_B:%.c=%.o}

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -I${HEADER}

RM		=	 rm -f

.PHONY:		all clean fclean re bonus

all:		${NAME}

%.o: 		%.c ${HEADER}
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS_A} ${OBJS_L} ${HEADER}
			${CC} ${CFLAGS} -o ${NAME} ${OBJS_A} ${OBJS_L}

bonus:
			@make OBJS_A="$(OBJS_B)" all

clean:		
			${RM} ${OBJS_A} ${OBJS_L} ${OBJS_B}

fclean:		clean
			${RM} ${NAME}

re:			fclean all
