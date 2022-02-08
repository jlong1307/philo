# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jlong <jlong@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/25 17:51:44 by jlong             #+#    #+#              #
#    Updated: 2022/02/08 15:59:10 by jlong            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC			= philo \
			ft_atoi \
			philo_untils \
			init \
			check_untils \
			routine \
			time \

SRCS		= $(addsuffix .c, ${SRC})

OBJS		= ${SRCS:.c=.o}
				
NAME		= philo

CC			= gcc
RM			= rm -f
RN			= ranlib

CFLAGS		= -Wall -Wextra -Werror -fsanitize=thread

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
