# ====================== VARIABLES ====================== #

# ---- Final executable ---- #

NAME 			= 	minishell

HEAD			=	header/minishell.h

SRC	=																	\
		src/execution/execution.c 										\
		src/execution/struct.c											\
		src/execution/files/infiles.c									\
		src/execution/files/outfiles.c									\
		src/execution/files/heredoc.c									\
		src/execution/files/heredoc_utils.c								\
		src/execution/files/heredoc_child_process.c						\
		src/execution/no_pipe/one_builtin_exec.c						\
		src/execution/with_pipe/loop_list.c								\
		src/execution/with_pipe/launch_exec.c							\
		src/execution/with_pipe/begin_exec.c							\
		src/execution/with_pipe/paths/check_access.c					\
		src/execution/with_pipe/paths/is_executable.c					\
		src/execution/with_pipe/paths/get_cmd_with_path.c				\
		src/execution/with_pipe/execute_token.c							\
		src/execution/with_pipe/dup_files.c 							\
		src/execution/clear_exec/close_files.c 							\
		src/execution/clear_exec/close_heredoc.c						\
		src/execution/clear_exec/clear_cmds.c							\
		src/execution/clear_exec/clear_heredoc.c						\
		src/execution/clear_exec/clear_files.c							\
		src/execution/clear_exec/clear_one_builtin_exec.c				\
		src/builtin/builtin.c 											\
		src/builtin/echo.c												\
		src/builtin/cd/cd.c												\
		src/builtin/cd/utils_cd.c										\
		src/builtin/env/env.c											\
		src/builtin/env/create_env_array.c								\
		src/builtin/env/create_env_list.c								\
		src/builtin/pwd.c												\
		src/builtin/exit.c 												\
		src/builtin/unset.c												\
		src/builtin/export/export.c										\
		src/builtin/export/check_is_valid.c								\
		src/builtin/export/print_export.c								\
		src/builtin/export/export_utils.c								\
		src/builtin/export/parse_export.c								\
		src/builtin/export/name_with_equal.c							\
		src/builtin/export/check_name_by_name.c							\
		src/builtin/export/clear_export.c								\
		src/main.c														\
		src/utils_main.c												\
		src/parsing/expand/expand.c										\
		src/parsing/expand/is_there_a_dollar.c							\
		src/parsing/expand/should_we_expand.c							\
		src/parsing/expand/utils_expand.c								\
		src/parsing/expand/different_case_expand.c						\
		src/parsing/list/change_list/change_list.c						\
		src/parsing/list/change_list/change_order.c						\
		src/parsing/list/change_list/change_tab.c						\
		src/parsing/list/change_list/del_delimiteur.c					\
		src/parsing/list/change_list/delete_quote.c						\
		src/parsing/list/change_list/add_space.c						\
		src/parsing/list/create_list.c									\
		src/parsing/list/prepare_list_creation.c						\
		src/parsing/utils_parsing/ft_split_parsing.c					\
		src/parsing/utils_parsing/ft_strjoin_parsing.c					\
		src/parsing/utils_parsing/skip.c								\
		src/parsing/utils_parsing/utils_parsing.c						\
		src/parsing/check_error.c										\
		src/parsing/parsing.c

# ---- Directories ---- #

DIR_LIB 		= libft

DIR_HEAD 		= 	header/

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

CFLAGS 			= -Wall  -Wextra -Werror -I ${DIR_HEAD} -I ${DIR_LIB} 

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

${NAME}: ${OBJS} ${LIBRARY}
	${CC} ${CFLAGS} $^ ${LIBRARY} -o $@ -lreadline

${DIR_OBJS}/%.o: %.c ${HEAD}
	@mkdir -p ${dir $@}
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