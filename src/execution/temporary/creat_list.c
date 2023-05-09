/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:54:55 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/09 18:00:15 by lciullo          ###   ########.fr       */
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
	char			**outfile;
	char			**cmd1;
	char			**pipe;
	char			**cmd3;
	char			**pipe1;
	char			**cmd4;

	infile = ft_split("< infile", ' ');
	cmd1 = ft_split("cat Makefile", ' ');
	pipe = ft_split("|", ' ');
	cmd3 = ft_split("rev", ' ');
	outfile = ft_split("> test", ' ');
	pipe1 = ft_split("|", ' ');
	cmd4 = ft_split("pwd", ' ');
	ft_lstadd_back(lst, ft_lstnew(infile, 0));
	ft_lstadd_back(lst, ft_lstnew(cmd1, 1));
	ft_lstadd_back(lst, ft_lstnew(pipe, 3));
	ft_lstadd_back(lst, ft_lstnew(cmd3, 1));
	ft_lstadd_back(lst, ft_lstnew(outfile, 2));
	ft_lstadd_back(lst, ft_lstnew(pipe1, 3));
	ft_lstadd_back(lst, ft_lstnew(cmd4, 1));
	return ;
}
