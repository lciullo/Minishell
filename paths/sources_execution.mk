# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_execution.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 09:55:39 by lciullo           #+#    #+#              #
#    Updated: 2023/05/10 11:34:24 by lciullo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=																	\
		src/execution/loop_exec.c 										\
		src/execution/struct.c											\
		src/execution/process/one_builtin_exec.c						\
		src/execution/process/loop_many_pipe.c							\
		src/execution/files/infiles.c									\
		src/execution/files/outfiles.c									\
		src/execution/files/heredoc.c									\
		src/execution/paths/get_path_env.c 								\
		src/execution/process/dup.c 									\
		src/execution/process/exec_cmd.c								\
		src/execution/process/free_and_close.c							\
		src/builtin/builtin.c 											\
		src/builtin/echo.c												\
		src/builtin/cd.c												\
		src/builtin/env.c												\
		src/builtin/pwd.c												\
		src/builtin/exit.c 												