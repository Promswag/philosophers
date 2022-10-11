# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gbaumgar <gbaumgar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/30 14:35:47 by gbaumgar          #+#    #+#              #
#    Updated: 2022/10/11 14:26:50 by gbaumgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= philo

INCLUDE_DIR		= ./include/
SRC_DIR			= ./src/
OUT_DIR			= ./

SRC				= 	philosophers.c args.c utils.c
OBJS			= ${SRC:%.c=${OUT_DIR}%.o}

INCLUDE			= -I${INCLUDE_DIR}	

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -g -fsanitize=thread
RM				= rm -f

all: ${NAME}

${NAME}: ${OBJS}
	${CC} -o ${NAME} ${INCLUDE} ${OBJS} ${CFLAGS}

${OUT_DIR}%.o: ${SRC_DIR}%.c 
	${CC} ${CFLAGS} ${INCLUDE} $< -c -o $@

clean:
	${RM} ${OBJS}

fclean:	clean
	${RM} ${NAME}

re: fclean ${NAME}

bonus:	all

.PHONY:	all clean fclean re bonus
