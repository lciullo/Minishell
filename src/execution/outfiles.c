/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfiles.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 15:32:29 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 15:44:12 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	is_outfile_open(t_exec *files)
{
	if (files->outfile > 2)
		close(files->outfile);
}

static	void	manage_outfile(char *outfile, t_exec *files)
{

	is_outfile_open(files);
	files->outfile = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (files->outfile == -1)
		perror("open outfile");
}

/*static void	print_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		ft_dprintf(1, "array[i] %s\n", array[i]);
		i++;
	}
}*/

void	loop_for_outfile(t_list **lst, t_exec *files)
{
	int		i;
	t_list	*head;

	i = 0;
	head = *lst;
	while (head != NULL)
	{
		//print_array(head->data);
		while (head->data[i] != NULL)
		{
			if (ft_strcmp(head->data[i], ">") == 0)
			{
				i++;
				manage_outfile(head->data[i], files);
				break ;
			}
			else
				i++;
		}
		head = head->next;
	}
}
