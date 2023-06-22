# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sources_parsing.mk                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cllovio <cllovio@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/14 09:55:41 by lciullo           #+#    #+#              #
#    Updated: 2023/06/22 11:25:46 by cllovio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC	+= 	src/main.c\
		src/parsing/expand/expand.c\
		src/parsing/expand/is_there_a_dollar.c\
		src/parsing/expand/should_we_expand.c\
		src/parsing/expand/utils_expand.c\
		src/parsing/list/change_list/change_list.c\
		src/parsing/list/change_list/change_order.c\
		src/parsing/list/change_list/change_tab.c\
		src/parsing/list/change_list/del_delimiteur.c\
		src/parsing/list/change_list/delete_quote.c\
		src/parsing/list/change_list/add_space.c\
		src/parsing/list/create_list.c\
		src/parsing/list/prepare_list_creation.c\
		src/parsing/utils_parsing/ft_split_parsing.c\
		src/parsing/utils_parsing/ft_strjoin_parsing.c\
		src/parsing/utils_parsing/skip.c\
		src/parsing/utils_parsing/utils_parsing.c\
		src/parsing/check_error.c\
		src/parsing/parsing.c\
		src/parsing/print.c