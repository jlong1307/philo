# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlong <jlong@student.s19.be>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 17:51:44 by jlong             #+#    #+#              #
#    Updated: 2022/01/26 10:33:21 by jlong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= philo \
			ft_atoi \
			philo_untils \
			init \

SRCS		= $(addsuffix .c, ${SRC})

OBJS		= ${SRCS:.c=.o}
				
NAME		= philo

CC			= gcc
RM			= rm -f
RN			= ranlib

CFLAGS		= -Wall -Wextra -Werror

.c.o:
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
			${CC} ${CFLAGS} ${OBJS} -o ${NAME}
			
all:		$(NAME)

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
