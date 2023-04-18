# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:03:28 by lciullo           #+#    #+#              #
#    Updated: 2023/04/18 13:00:37 by cllovio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include paths/headers_execution.mk
include paths/headers_parsing.mk
include paths/sources_execution.mk
include paths/sources_parsing.mk

# ====================== VARIABLES ====================== #

# ---- Final executable ---- #

NAME 			= minishell

# ---- Directories ---- #

DIR_LIB 		= libft

DIR_HEAD 		= 	head/

DIR_OBJS 		=	.objs

# ---- Paths ---- #

LIBRARY 		= ${DIR_LIB}/libft.a 

OBJS 			=	${addprefix ${DIR_OBJS}/, ${SRC:.c=.o}}

# ---- Variables ---- #

DEBUG			=	no

VALGRIND		= 	no

# ---- Commands ---- #

RMF				=	rm -rf

# ====================== FLAGS AND COMPILATION ====================== #

# ---- Compilation flags ---- #

CC 				= cc

CFLAGS 			= -Wall -Werror -Wextra -I ${DIR_HEAD} -I ${DIR_LIB}

# ---- Debug Compilation flags ---- #

DFLAGS			= -g3 -fsanitize=address

ifeq (${DEBUG}, yes)
CFLAGS		+= ${DFLAGS}
endif

# ---- Leaks Compilation flags ---- #

LEAKS			=	valgrind --suppressions=ignore_readline_reachable.txt --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes

# ====================== RULES ====================== #

# ---- Compilation rules ---- #

all :
	${MAKE} lib
	${MAKE} ${NAME}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} $^ ${LIBRARY} -o $@ -lreadline

${DIR_OBJS}/%.o: %.c ${HEAD} ${LIBRARY}
	mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

# ---- Library ---- #

lib :
	${MAKE} -C ./libft
	
# ---- Debug rules ---- #

debug:
	${MAKE} re DEBUG=yes
	

# ---- Leaks rules ---- #
	
leaks:
	clear
	${MAKE} re VALGRIND=yes
	${LEAKS} ./minishell

# ---- Clean rules --- #

clean :
	${MAKE} -C libft clean
	${RMF} ${DIR_OBJS}

fclean : clean 
	${MAKE} -C libft fclean
	${RMF}  ${NAME}

re : fclean
	${MAKE} all

.PHONY: all lib clean fclean re