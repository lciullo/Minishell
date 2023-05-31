# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_execution.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 09:55:39 by lciullo           #+#    #+#              #
#    Updated: 2023/05/31 13:55:10 by lciullo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=																	\
		src/execution/execution.c 										\
		src/execution/struct.c											\
		src/execution/temporary/print_debug.c							\
		src/execution/no_pipe/one_builtin_exec.c						\
		src/execution/with_pipe/loop_list.c								\
		src/execution/files/infiles.c									\
		src/execution/files/outfiles.c									\
		src/execution/files/heredoc.c									\
		src/execution/files/clear_heredoc.c								\
		src/execution/files/heredoc_utils.c								\
		src/execution/with_pipe/paths/get_path_env.c 					\
		src/execution/with_pipe/dup_files.c 							\
		src/execution/with_pipe/clear_exec/close_files.c 				\
		src/execution/with_pipe/exec_cmd.c								\
		src/execution/with_pipe/clear_exec/free_exec.c					\
		src/execution/with_pipe/launch_exec.c							\
		src/builtin/builtin.c 											\
		src/builtin/echo.c												\
		src/builtin/cd.c												\
		src/builtin/env.c												\
		src/builtin/pwd.c												\
		src/builtin/exit.c 												\
		src/builtin/export.c