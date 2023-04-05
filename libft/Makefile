  # **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/19 15:00:58 by lciullo           #+#    #+#              #
#    Updated: 2023/02/21 17:14:57 by lciullo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ====================== VARIABLES ====================== #

# ---- Final Executable --- #

NAME			=	libft.a

# ---- Directories and path files ---- #

INCLUDES		=	headers/

DIR_OBJS		=	.objs/

SRCS			=	${addprefix src/, ${C_FILES}}

C_FILES 		=	print/ft_dprintf_nb.c \
					print/ft_dprintf_str.c\
					print/ft_dprintf.c \
\
					string/ft_libft_utils.c \
					string/ft_split.c \
					string/ft_free_array.c \
					string/ft_itoa.c \
					string/ft_strncmp.c \
					string/ft_strchr.c \
					string/ft_calloc.c \
					string/ft_bzero.c \
					string/ft_strnstr.c \
					string/ft_strjoin.c 

HEADERS 		=	${INCLUDES}libft.h	


OBJS			=	${addprefix ${DIR_OBJS},${SRCS:.c=.o}}

# ---- Variables ---- #


# ---- Compilation ---- #

CC				= cc

CFLAGS 			= -Wall -Wextra -Werror 

# ---- Commands ---- #

RMF				=	rm -rf

# ====================== RULES ====================== #

# ---- Compiled rules ---- #

all:			${NAME}

${NAME}:		${OBJS}
				ar rcs ${NAME} ${OBJS}

${DIR_OBJS}%.o: %.c ${HEADERS}
	@ mkdir -p ${dir $@}
	${CC} ${CFLAGS} -I ${INCLUDES} -c $< -o $@

# ---- Clean rules ---- #

clean:
	${RMF} ${OBJS} ${DIR_OBJS}

fclean:	clean
	${RMF} ${NAME}

re:	fclean
	${MAKE} all

.PHONY:	all clean fclean re 