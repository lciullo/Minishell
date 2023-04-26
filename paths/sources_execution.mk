# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_execution.mk                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 09:55:39 by lciullo           #+#    #+#              #
#    Updated: 2023/04/26 15:48:55 by lciullo          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	=																	\
		src/execution/heredoc.c											\
		src/execution/loop_exec.c 										\
		src/execution/struct.c											\
		src/execution/infiles.c											\
		src/execution/outfiles.c										\
		src/builtin/builtin.c 											\
		src/builtin/echo.c												\
		src/builtin/cd.c												\
		src/builtin/pwd.c												\
		src/builtin/exit.c 