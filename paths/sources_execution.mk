# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_execution.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 09:55:39 by lciullo           #+#    #+#              #
#    Updated: 2023/05/02 15:47:53 by lciullo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=																	\
		src/execution/loop_exec.c 										\
		src/execution/struct.c											\
		src/execution/files/infiles.c									\
		src/execution/files/outfiles.c									\
		src/execution/files/heredoc.c									\
		src/execution/paths/get_path_env.c 								\
		src/execution/process/dup.c 									\
		src/execution/process/exec_cmd.c								\
		src/execution/process/free_and_close.c							\
		src/execution/process/process.c									\
		src/execution/process/struct.c									\
		src/builtin/builtin.c 											\
		src/builtin/echo.c												\
		src/builtin/cd.c												\
		src/builtin/env.c												\
		src/builtin/pwd.c												\
		src/builtin/exit.c 												