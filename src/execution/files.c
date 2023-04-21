/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:57:20 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/21 16:21:17 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	manage_infile(char *infile)
{
	t_exec	files;

	files.infile = open(infile, O_RDONLY, 0644);
	if (files.infile == -1)
		perror("open infile");
	close(files.infile);
}

void	loop_for_infile(t_list **lst)
{
	int		i;
	t_list	*head;

	i = 0;
	head = *lst;
	while (head != NULL)
	{
		while (head->data[i] != NULL)
		{
			if (ft_strcmp(head->data[i], "<") == 0)
			{
				i++;
				manage_infile(head->data[i]);
				break ;
			}
			else
				i++;
		}
		head = head->next;
	}
}



