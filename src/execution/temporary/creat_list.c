/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 10:54:55 by lciullo           #+#    #+#             */
/*   Updated: 2023/05/09 14:37:47 by lciullo          ###   ########.fr       */
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
	//char			**outfile;
	char			**cmd1;
	char			**cmd2;
	char			**cmd3;

	infile = ft_split("< infile", ' ');
	//outfile = ft_split("> test", ' ');*/
	cmd1 = ft_split("cat Makefile", ' ');
	cmd2 = ft_split("|", ' ');
	cmd3 = ft_split("rev", ' ');
	ft_lstadd_back(lst, ft_lstnew(infile, 0));
	ft_lstadd_back(lst, ft_lstnew(cmd1, 1));
	ft_lstadd_back(lst, ft_lstnew(cmd2, 3));
	ft_lstadd_back(lst, ft_lstnew(cmd3, 1));
	/*ft_lstadd_back(lst, ft_lstnew(outfile, 2));*/
	return ;
}
