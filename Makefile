# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/15 11:03:28 by lciullo           #+#    #+#              #
#    Updated: 2023/03/20 10:38:18 by lciullo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# ====================== VARIABLES ====================== #

# ---- Final executable ---- #

NAME 		= pipex

LIBRARY 	= libft/libft.a 

# ---- Directories and path files ---- #

HEAD 		= 	headers/pipex.h \

SRC			= 	src/process/pipex.c \
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

CFLAGS 		= -Wall -Werror -Wextra -I headers/ 

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