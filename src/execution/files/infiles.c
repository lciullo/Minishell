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

void	loop_for_infile(t_list **list, t_exec *data)
{
	int		i;
	t_list	*copy;

	i = 0;
	copy = *list;
	while (copy != NULL)
	{
		//print_array(copy->data);
		i = 0;
		while (copy->data[i] != NULL)
		{
			if (ft_strcmp(copy->data[i], "<") == 0)
			{
				i++;
				manage_infile(copy->data[i], data);
				break ;
			}
			else
				i++;
		}
		copy = copy->next;
	}
}



