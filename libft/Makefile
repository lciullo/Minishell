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

# ---- Directories and path data ---- #

INCLUDES		=	headers/

DIR_OBJS		=	.objs/

SRCS			=	${addprefix src/, ${C_data}}

C_data 		=	gnl/get_next_line.c \
					gnl/get_next_line_utils.c \
					\
					print/ft_dprintf_nb.c \
					print/ft_dprintf_str.c\
					print/ft_dprintf.c\
					print/ft_putendl_fd.c\
					\
					library/ft_isalpha.c\
					library/ft_isdigit.c\
					library/ft_isalnum.c\
					library/ft_isascii.c\
					library/ft_isprint.c\
					library/ft_strlen.c\
					library/ft_memset.c\
					library/ft_bzero.c\
					library/ft_memcpy.c\
					library/ft_memmove.c\
					library/ft_strlcpy.c\
					library/ft_strlcat.c\
					library/ft_toupper.c\
					library/ft_tolower.c\
					library/ft_strchr.c\
					library/ft_strcmp.c \
					library/ft_strrchr.c\
					library/ft_strncmp.c\
					library/ft_memchr.c\
					library/ft_memcmp.c\
					library/ft_strnstr.c\
					library/ft_atoi.c \
					library/ft_atoi_long.c \
					library/ft_calloc.c\
					library/ft_strdup.c\
					library/ft_substr.c\
					library/ft_strjoin.c\
					library/ft_join_heredoc.c \
					library/ft_strtrim.c\
					library/ft_split.c\
					library/ft_itoa.c\
					library/ft_strmapi.c\
					library/ft_strndup.c \
					library/ft_striteri.c\
					\
					list/ft_lstadd_back.c\
					list/ft_lstadd_front.c\
					list/ft_lstclear.c\
					list/ft_lstdelone.c\
					list/ft_lstiter.c\
					list/ft_lstlast.c\
					list/ft_lstnew.c \
					list/ft_lstsize.c \
					list/list_print.c 
#list/ft_lstmap.c

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