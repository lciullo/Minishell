/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:54:55 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/10 10:17:08 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
===============
Type
===============
Infile = 0
Token = 1
Outfile = 2
Pipe = 3
*/


#include "minishell.h"

void	tmp_lst(t_list **lst)
{
	char			**infile;

	infile = ft_split("< infile", ' ');
	ft_lstadd_back(lst, ft_lstnew(infile, 0));
	return ;
}
