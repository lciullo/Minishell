# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:03:28 by lciullo           #+#    #+#              #
#    Updated: 2023/04/14 09:30:46 by cllovio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ====================== VARIABLES ====================== #

# ---- Final executable ---- #

NAME 		= minishell

LIBRARY 	= libft/libft.a 

# ---- Directories and path files ---- #

HEAD 		= 	headers/pipex.h \

SRC			= 	src/main.c \
				src/process/pipex.c \
				src/process/exec_cmd.c \
				src/process/struct.c \
				src/parsing/check_files.c \
				src/parsing/get_path_env.c \
				src/process/free_and_close.c


DIR_OBJS 	= .objs/

OBJS 		= ${SRC:%.c=${DIR_OBJS}%.o}

DEBUG		= no

# ---- Compilation flags ---- #

CC 			= cc

CFLAGS 		= -Wall -Werror -Wextra -lreadline -I headers/ 

# ---- Debug Compilation flags ---- #

DFLAGS		= -g3 -fsanitize=address

ifeq (${DEBUG}, yes)
CFLAGS		+= ${DFLAGS}
endif

# ---- Commands ---- #

RMF			=	rm -rf

# ====================== RULES ====================== #

# ---- Compilation rules ---- #

all : 
	${MAKE} lib
	${MAKE} ${NAME}

${NAME}: ${OBJS}
	${CC} $^ ${CFLAGS} ${LIBRARY} -o $@

${DIR_OBJS}%.o : %.c ${HEAD} ${LIBRARY}
	@ mkdir -p ${dir $@}
	${CC} ${CFLAGS} -c $< -o $@

# ---- Library ---- #

lib :
	${MAKE} -C ./libft
	
# ---- Debug rules ---- #

debug:
	$(MAKE) re DEBUG=yes

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