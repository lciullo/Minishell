/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lciullo <lciullo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 14:57:20 by lciullo           #+#    #+#             */
/*   Updated: 2023/04/26 15:27:49 by lciullo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	is_infile_open(t_exec *data)
{
	if (data->infile > 2)
		close(data->infile);
}

static	void	manage_infile(char *infile, t_exec *data)
{

	is_infile_open(data);
	data->infile = open(infile, O_RDONLY, 0644);
	if (data->infile == -1)
		perror("open infile");
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

void	loop_for_infile(t_list **lst, t_exec *data)
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
			if (ft_strcmp(head->data[i], "<") == 0)
			{
				i++;
				manage_infile(head->data[i], data);
				break ;
			}
			else
				i++;
		}
		head = head->next;
	}
}



