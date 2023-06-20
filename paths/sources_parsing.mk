# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_parsing.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 09:55:41 by lciullo           #+#    #+#              #
#    Updated: 2023/06/20 14:19:32 by cllovio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	+= 	src/main.c\
		src/parsing/parsing.c\
		src/parsing/utils_parsing/utils_parsing.c\
		src/parsing/list.c\
		src/parsing/print.c\
		src/parsing/check_error.c\
		src/parsing/change_list.c\
		src/parsing/skip.c\
		src/parsing/expand/expand.c\
		src/parsing/utils_parsing/ft_split_parsing.c\
		src/parsing/change_line.c\
		src/parsing/change_order.c\
		src/parsing/add_space.c\
		src/parsing/expand/utils_expand.c\
		src/parsing/delete_quote.c\
		src/parsing/expand/should_we_expand.c\
		src/parsing/error.c\
		src/parsing/utils_parsing/ft_strjoin_parsing.c